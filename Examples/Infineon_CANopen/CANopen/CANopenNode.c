/**
  ******************************************************************************
  * @file           : CANopenNode.c
  * @author         : Muhammed YILDIRIM
  * @brief          : CANopenNode driver file
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "CANopenNode.h"
#include "CANopen.h"
#include "OD.h"
#include "storage/CO_storageEeprom.h"
#include "CANopenHardware.h"
#include "log.h"


/* Defines -------------------------------------------------------------------*/
#define AUTO_STORAGE_ENABLE		 ( 0 )

/* default values for CO_CANopenInit() */
#define NMT_CONTROL \
            CO_NMT_STARTUP_TO_OPERATIONAL \
          | CO_NMT_ERR_ON_ERR_REG \
          | CO_ERR_REG_GENERIC_ERR \
          | CO_ERR_REG_COMMUNICATION
#define FIRST_HB_TIME             500
#define SDO_SRV_TIMEOUT_TIME      1000
#define SDO_CLI_TIMEOUT_TIME      500
#define SDO_CLI_BLOCK             false
#define OD_STATUS_BITS            NULL


/* Enum definitions ----------------------------------------------------------*/

/* Structure definitions -----------------------------------------------------*/

/* External variables --------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static CO_t *CO = NULL;         /* CANopen object */
static CO_NMT_reset_cmd_t reset = CO_RESET_NOT;

#if (CO_CONFIG_STORAGE) & CO_CONFIG_STORAGE_ENABLE
CO_storage_t storage;

CO_storage_entry_t storageEntries[] = {
    {
        .addr = &OD_RAM,
        .len = sizeof(OD_RAM),
        .subIndexOD = 2,
        .attr = CO_storage_cmd | CO_storage_restore
    },
};

/* Data block for mainline data, which can be stored to non-volatile memory */
typedef struct {
    /* Pending CAN bit rate, can be set by switch or LSS slave. */
    uint16_t pendingBitRate;
    /* Pending CANopen NodeId, can be set by switch or LSS slave. */
    uint8_t pendingNodeId;
} mainlineStorage_t;

static mainlineStorage_t mlStorage = {0};
#endif


/* Private function prototypes -----------------------------------------------*/

/* Functions -----------------------------------------------------------------*/
/**
 * @brief CAN Open stack initialize
 * 
 * @return CANopenNode_StatusTypeDef 
 */
CANopenNodeStatusTypeDef_t xCANopenNodeInit (void)
{
    CO_ReturnError_t err;
    uint32_t heapMemoryUsed;
    void *CANptr = NULL;                                    /* CAN module address */
    uint8_t activeNodeId;                                   /* Copied from CO_pendingNodeId in the communication reset section */
    uint8_t pendingNodeId = CAN_OPEN_NODE_ID;               /* read from dip switches or nonvolatile memory, configurable by LSS slave */
    uint16_t pendingBitRate = CAN_OPEN_NODE_BAUDRATE;       /* read from dip switches or nonvolatile memory, configurable by LSS slave */


#if (CO_CONFIG_STORAGE) & CO_CONFIG_STORAGE_ENABLE
    uint8_t storageEntriesCount = sizeof(storageEntries) / sizeof(storageEntries[0]);
    uint32_t storageInitError = 0;
#endif

    /* Configure CAN hardware */
    if (xCANopenHardwareInit() == CAN_OPEN_HARDWARE_ERROR)
    {
      LOG_INFO("Failed: CANopen hardware initialize\n");
      return CAN_OPEN_NODE_ERROR;
    }


    /* Allocate memory */
    CO_config_t *config_ptr = NULL;
#ifdef CO_MULTIPLE_OD
    /* example usage of CO_MULTIPLE_OD (but still single OD here) */
    CO_config_t co_config = {0};
    OD_INIT_CONFIG(co_config); /* helper macro from OD.h */
    co_config.CNT_LEDS = 1;
    co_config.CNT_LSS_SLV = 1;
    config_ptr = &co_config;
#endif /* CO_MULTIPLE_OD */
    CO = CO_new(config_ptr, &heapMemoryUsed);
    if (CO == NULL) 
    {
        LOG_INFO("Error: Can't allocate memory\n");
        return CAN_OPEN_NODE_ERROR;
    }
    else 
    {
        LOG_INFO("Allocated %u bytes for CANopen objects\n", heapMemoryUsed);
    }


#if (CO_CONFIG_STORAGE) & CO_CONFIG_STORAGE_ENABLE
    err = CO_storageEeprom_init(&storage,
                               CO->CANmodule,
							   NULL,
                               OD_ENTRY_H1010_storeParameters,
                               OD_ENTRY_H1011_restoreParameters,
                               storageEntries,
                               storageEntriesCount,
                               &storageInitError);

    if (err != CO_ERROR_NO && err != CO_ERROR_DATA_CORRUPT) {
    	LOG_INFO("Error: Storage %d\n", storageInitError);
        return 0;
    }
#endif

    /* CANopen communication reset - initialize CANopen objects */
    if(reset != CO_RESET_APP) {

        LOG_INFO("CANopenNode - Reset communication\n");

        /* Wait rt_thread. */
        CO->CANmodule->CANnormal = false;

        /* Enter CAN configuration. */
        CO_CANsetConfigurationMode((void *)&CANptr);
        CO_CANmodule_disable(CO->CANmodule);

        /* initialize CANopen */
        err = CO_CANinit(CO, CANptr, pendingBitRate);
        if (err != CO_ERROR_NO) {
            LOG_INFO("Error: CAN initialization failed: %d\n", err);
            return CAN_OPEN_NODE_ERROR;
        }

        CO_LSS_address_t lssAddress = {.identity = {
            .vendorID = OD_RAM.x1018_identityObject.vendorID,
            .productCode = OD_RAM.x1018_identityObject.productCode,
            .revisionNumber = OD_RAM.x1018_identityObject.revisionNumber
        }};

        err = CO_LSSinit(CO, &lssAddress, &pendingNodeId, &pendingBitRate);
        if(err != CO_ERROR_NO) {
            LOG_INFO("Error: LSS slave initialization failed: %d\n", err);
            return CAN_OPEN_NODE_ERROR;
        }

        activeNodeId = pendingNodeId;
        uint32_t errInfo = 0;

        err = CO_CANopenInit(CO,                    /* CANopen object */
                             NULL,                  /* alternate NMT */
                             NULL,                  /* alternate em */
                             OD,                    /* Object dictionary */
                             OD_STATUS_BITS,        /* Optional OD_statusBits */
                             NMT_CONTROL,           /* CO_NMT_control_t */
                             FIRST_HB_TIME,         /* firstHBTime_ms */
                             SDO_SRV_TIMEOUT_TIME,  /* SDOserverTimeoutTime_ms */
                             SDO_CLI_TIMEOUT_TIME,  /* SDOclientTimeoutTime_ms */
                             SDO_CLI_BLOCK,         /* SDOclientBlockTransfer */
                             activeNodeId,
                             &errInfo);

        if(err != CO_ERROR_NO && err != CO_ERROR_NODE_ID_UNCONFIGURED_LSS) {

            if (err == CO_ERROR_OD_PARAMETERS) {
                LOG_INFO("Error: Object Dictionary entry 0x%X\n", errInfo);
            }
            else {
                LOG_INFO("Error: CANopen initialization failed: %d\n", err);
            }

            return CAN_OPEN_NODE_ERROR;
        }

        err = CO_CANopenInitPDO(CO, CO->em, OD, activeNodeId, &errInfo);
        if(err != CO_ERROR_NO) {
            if (err == CO_ERROR_OD_PARAMETERS) {
                LOG_INFO("Error: Object Dictionary entry 0x%X\n", errInfo);
            }
            else {
                LOG_INFO("Error: PDO initialization failed: %d\n", err);
            }
            return CAN_OPEN_NODE_ERROR;
        }

        /* Configure CANopen callbacks, etc */
        if(!CO->nodeIdUnconfigured) 
        {

#if (CO_CONFIG_STORAGE) & CO_CONFIG_STORAGE_ENABLE
            if(storageInitError != 0) {
                CO_errorReport(CO->em, CO_EM_NON_VOLATILE_MEMORY,
                               CO_EMC_HARDWARE, storageInitError);
            }
#endif
        }
        else 
        {
            LOG_INFO("CANopenNode - Node-id not initialized\n");
        }

      /* start CAN */
      CO_CANsetNormalMode(CO->CANmodule);

      LOG_INFO("CANopenNode - Running\n");
    }

    reset = CO_RESET_NOT;

    return CAN_OPEN_NODE_OK;
}


/**
 * @brief CANopen Node pediodic function
 *        This function must be call periodically
 */
void vCANopenNodeProcess (void)
{

    if (reset == CO_RESET_NOT)
    {
        /* get time difference since last function call */
        uint32_t timeDifference_us = 1000;

        /* CANopen process */
        reset = CO_process(CO, false, timeDifference_us, NULL);

        /* LED_red = CO_LED_RED(CO->LEDs, CO_LED_CANopen);     */
        /* LED_green = CO_LED_GREEN(CO->LEDs, CO_LED_CANopen); */

        /* optional sleep for short time */
#if (CO_CONFIG_STORAGE) & CO_CONFIG_STORAGE_ENABLE
#if AUTO_STORAGE_ENABLE
      CO_storageEeprom_auto_process(&storage, false);
#endif
#endif
    }

    else if (reset == CO_RESET_APP || reset == CO_RESET_COMM)
    {
    	//CO_storageEeprom_auto_process(&storage, true);
        vResetModule();
    }
}


/**
 * @brief CANopen function in timer
 *        This function must be call in 1 ms Timer Interrupt
 */
void vCANopenNodeTimerInterrupt (void)
{

    CO_LOCK_OD(CO->CANmodule);

    if (!CO->nodeIdUnconfigured && CO->CANmodule->CANnormal) 
    {
        bool_t syncWas = false;
        /* get time difference since last function call */
        uint32_t timeDifference_us = 1000;

#if (CO_CONFIG_SYNC) & CO_CONFIG_SYNC_ENABLE
        syncWas = CO_process_SYNC(CO, timeDifference_us, NULL);
#endif
#if (CO_CONFIG_PDO) & CO_CONFIG_RPDO_ENABLE
        CO_process_RPDO(CO, syncWas, timeDifference_us, NULL);
#endif
#if (CO_CONFIG_PDO) & CO_CONFIG_TPDO_ENABLE
        CO_process_TPDO(CO, syncWas, timeDifference_us, NULL);
#endif

    }
    
    CO_UNLOCK_OD(CO->CANmodule);
}

/**
 * @brief CANopen receive interrupt function
 */
void vCANopenNodeReceiveInterrupt (void)
{
    CO_CANinterrupt(CO->CANmodule);
}


/**
 * @brief  CANopen get NMT State
 * @return State
 */
CANopenNodeNMTStatusTypeDef_t xCANopenNodeGetNMTState ( void )
{
    return CO->NMT->operatingState;
}


/**
 * @brief  CANopen set NMT State
 * @return State
 */
void vCANopenNodeSetNMTState ( CANopenNodeNMTStatusTypeDef_t xState )
{
	if ( ( xState == NMT_INITIALIZING ) || ( xState == NMT_PRE_OPERATIONAL ) || ( xState == NMT_OPERATIONAL )  || ( xState == NMT_STOPPED ) )
		CO->NMT->operatingState = xState;
}

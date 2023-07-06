<?xml version="1.0" encoding="ASCII"?>
<ResourceModel:App xmi:version="2.0" xmlns:xmi="http://www.omg.org/XMI" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:ResourceModel="http://www.infineon.com/Davex/Resource.ecore" name="INTERRUPT" URI="http://resources/4.0.10/app/INTERRUPT/1" description="Allows to overwrite the provided interrupt service routine (ISR) in system file &#xA; and sets the interrupt priority" mode="NOTSHARABLE" version="4.0.10" minDaveVersion="4.0.0" instanceLabel="CAN_RECEIVE_INTERRUPT_1" appLabel="">
  <properties provideInit="true"/>
  <virtualSignals name="sr_irq" URI="http://resources/4.0.10/app/INTERRUPT/1/vs_nvic_signal_in" hwSignal="signal_in" hwResource="//@hwResources.0" visible="true">
    <upwardMapList xsi:type="ResourceModel:Connections" href="../../CAN_NODE/v4_1_24/CAN_NODE_0.app#//@connections.6"/>
  </virtualSignals>
  <requiredApps URI="http://resources/4.0.10/app/INTERRUPT/1/appres_cpu" requiredAppName="CPU_CTRL_XMC4" requiringMode="SHARABLE">
    <downwardMapList xsi:type="ResourceModel:App" href="../../CPU_CTRL_XMC4/v4_0_18/CPU_CTRL_XMC4_0.app#/"/>
  </requiredApps>
  <hwResources name="NVIC Node" URI="http://resources/4.0.10/app/INTERRUPT/1/hwres_nvicnode" resourceGroupUri="peripheral/cpu/0/nvic/interrupt/*" mResGrpUri="peripheral/cpu/0/nvic/interrupt/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/cpu/cpu_0.dd#//@provided.12"/>
  </hwResources>
</ResourceModel:App>

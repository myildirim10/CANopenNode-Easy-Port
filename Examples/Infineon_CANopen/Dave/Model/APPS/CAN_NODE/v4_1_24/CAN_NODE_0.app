<?xml version="1.0" encoding="ASCII"?>
<ResourceModel:App xmi:version="2.0" xmlns:xmi="http://www.omg.org/XMI" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:ResourceModel="http://www.infineon.com/Davex/Resource.ecore" name="CAN_NODE" URI="http://resources/4.1.24/app/CAN_NODE/0" description="The CAN_NODE APP configures a node and MO registers &#xA;of MultiCAN module. &#xA;It provides run-time functions to change the node baud rate &#xA;and to enable/disable node and MO events." mode="NOTSHARABLE" version="4.1.24" minDaveVersion="4.0.0" instanceLabel="CAN_NODE_0" appLabel="">
  <properties provideInit="true"/>
  <virtualSignals name="receive_pin" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_can_rxd" hwSignal="rxd" hwResource="//@hwResources.2"/>
  <virtualSignals name="transmit_pin" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_can_txd" hwSignal="txd" hwResource="//@hwResources.2"/>
  <virtualSignals name="receive_pad" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_can_rxpin" hwSignal="pad" hwResource="//@hwResources.0"/>
  <virtualSignals name="transmit_pad" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_can_txpin" hwSignal="pad" hwResource="//@hwResources.1"/>
  <virtualSignals name="event_node_alert" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_can_alinp" hwSignal="alinp" hwResource="//@hwResources.2" visible="true"/>
  <virtualSignals name="event_node_lec_error" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_can_lecinp" hwSignal="lecinp" hwResource="//@hwResources.2" required="false" visible="true"/>
  <virtualSignals name="event_node_transfer_ok" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_can_trinp" hwSignal="trinp" hwResource="//@hwResources.2" required="false" visible="true"/>
  <virtualSignals name="event_node_frame_count" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_can_cfcinp" hwSignal="cfcinp" hwResource="//@hwResources.2" required="false" visible="true"/>
  <virtualSignals name="event_lmo_01_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message1_txinp" hwSignal="txinp" hwResource="//@hwResources.3" required="false" visible="true"/>
  <virtualSignals name="event_lmo_01_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message1_rxinp" hwSignal="rxinp" hwResource="//@hwResources.3" required="false" visible="true"/>
  <virtualSignals name="event_lmo_02_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message2_txinp" hwSignal="txinp" hwResource="//@hwResources.4" required="false" visible="true"/>
  <virtualSignals name="event_lmo_02_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message2_rxinp" hwSignal="rxinp" hwResource="//@hwResources.4" visible="true"/>
  <virtualSignals name="event_lmo_03_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message3_txinp" hwSignal="txinp" hwResource="//@hwResources.5" required="false" visible="true"/>
  <virtualSignals name="event_lmo_03_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message3_rxinp" hwSignal="rxinp" hwResource="//@hwResources.5" required="false" visible="true"/>
  <virtualSignals name="event_lmo_04_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message4_txinp" hwSignal="txinp" hwResource="//@hwResources.6" required="false" visible="true"/>
  <virtualSignals name="event_lmo_04_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message4_rxinp" hwSignal="rxinp" hwResource="//@hwResources.6" required="false" visible="true"/>
  <virtualSignals name="event_lmo_05_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message5_txinp" hwSignal="txinp" hwResource="//@hwResources.7" required="false" visible="true"/>
  <virtualSignals name="event_lmo_05_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message5_rxinp" hwSignal="rxinp" hwResource="//@hwResources.7" required="false" visible="true"/>
  <virtualSignals name="event_lmo_06_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message6_txinp" hwSignal="txinp" hwResource="//@hwResources.8" required="false" visible="true"/>
  <virtualSignals name="event_lmo_06_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message6_rxinp" hwSignal="rxinp" hwResource="//@hwResources.8" required="false" visible="true"/>
  <virtualSignals name="event_lmo_07_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message7_txinp" hwSignal="txinp" hwResource="//@hwResources.9" required="false" visible="true"/>
  <virtualSignals name="event_lmo_07_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message7_rxinp" hwSignal="rxinp" hwResource="//@hwResources.9" required="false" visible="true"/>
  <virtualSignals name="event_lmo_08_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message8_txinp" hwSignal="txinp" hwResource="//@hwResources.10" required="false" visible="true"/>
  <virtualSignals name="event_lmo_08_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message8_rxinp" hwSignal="rxinp" hwResource="//@hwResources.10" required="false" visible="true"/>
  <virtualSignals name="event_lmo_09_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message9_txinp" hwSignal="txinp" hwResource="//@hwResources.11" required="false" visible="true"/>
  <virtualSignals name="event_lmo_09_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message9_rxinp" hwSignal="rxinp" hwResource="//@hwResources.11" required="false" visible="true"/>
  <virtualSignals name="event_lmo_10_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message10_txinp" hwSignal="txinp" hwResource="//@hwResources.12" required="false" visible="true"/>
  <virtualSignals name="event_lmo_10_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message10_rxinp" hwSignal="rxinp" hwResource="//@hwResources.12" required="false" visible="true"/>
  <virtualSignals name="event_lmo_11_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message11_txinp" hwSignal="txinp" hwResource="//@hwResources.13" required="false" visible="true"/>
  <virtualSignals name="event_lmo_11_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message11_rxinp" hwSignal="rxinp" hwResource="//@hwResources.13" required="false" visible="true"/>
  <virtualSignals name="event_lmo_12_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message12_txinp" hwSignal="txinp" hwResource="//@hwResources.14" required="false" visible="true"/>
  <virtualSignals name="event_lmo_12_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message12_rxinp" hwSignal="rxinp" hwResource="//@hwResources.14" required="false" visible="true"/>
  <virtualSignals name="event_lmo_13_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message13_txinp" hwSignal="txinp" hwResource="//@hwResources.15" required="false" visible="true"/>
  <virtualSignals name="event_lmo_13_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message13_rxinp" hwSignal="rxinp" hwResource="//@hwResources.15" required="false" visible="true"/>
  <virtualSignals name="event_lmo_14_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message14_txinp" hwSignal="txinp" hwResource="//@hwResources.16" required="false" visible="true"/>
  <virtualSignals name="event_lmo_14_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message14_rxinp" hwSignal="rxinp" hwResource="//@hwResources.16" required="false" visible="true"/>
  <virtualSignals name="event_lmo_15_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message15_txinp" hwSignal="txinp" hwResource="//@hwResources.17" required="false" visible="true"/>
  <virtualSignals name="event_lmo_15_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message15_rxinp" hwSignal="rxinp" hwResource="//@hwResources.17" required="false" visible="true"/>
  <virtualSignals name="event_lmo_16_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message16_txinp" hwSignal="txinp" hwResource="//@hwResources.18" required="false" visible="true"/>
  <virtualSignals name="event_lmo_16_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message16_rxinp" hwSignal="rxinp" hwResource="//@hwResources.18" required="false" visible="true"/>
  <virtualSignals name="event_lmo_17_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message17_txinp" hwSignal="txinp" hwResource="//@hwResources.19" required="false" visible="true"/>
  <virtualSignals name="event_lmo_17_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message17_rxinp" hwSignal="rxinp" hwResource="//@hwResources.19" required="false" visible="true"/>
  <virtualSignals name="event_lmo_18_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message18_txinp" hwSignal="txinp" hwResource="//@hwResources.20" required="false" visible="true"/>
  <virtualSignals name="event_lmo_18_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message18_rxinp" hwSignal="rxinp" hwResource="//@hwResources.20" required="false" visible="true"/>
  <virtualSignals name="event_lmo_19_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message19_txinp" hwSignal="txinp" hwResource="//@hwResources.21" required="false" visible="true"/>
  <virtualSignals name="event_lmo_19_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message19_rxinp" hwSignal="rxinp" hwResource="//@hwResources.21" required="false" visible="true"/>
  <virtualSignals name="event_lmo_20_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message20_txinp" hwSignal="txinp" hwResource="//@hwResources.22" required="false" visible="true"/>
  <virtualSignals name="event_lmo_20_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message20_rxinp" hwSignal="rxinp" hwResource="//@hwResources.22" required="false" visible="true"/>
  <virtualSignals name="event_lmo_21_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message21_txinp" hwSignal="txinp" hwResource="//@hwResources.23" required="false" visible="true"/>
  <virtualSignals name="event_lmo_21_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message21_rxinp" hwSignal="rxinp" hwResource="//@hwResources.23" required="false" visible="true"/>
  <virtualSignals name="event_lmo_22_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message22_txinp" hwSignal="txinp" hwResource="//@hwResources.24" required="false" visible="true"/>
  <virtualSignals name="event_lmo_22_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message22_rxinp" hwSignal="rxinp" hwResource="//@hwResources.24" required="false" visible="true"/>
  <virtualSignals name="event_lmo_23_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message23_txinp" hwSignal="txinp" hwResource="//@hwResources.25" required="false" visible="true"/>
  <virtualSignals name="event_lmo_23_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message23_rxinp" hwSignal="rxinp" hwResource="//@hwResources.25" required="false" visible="true"/>
  <virtualSignals name="event_lmo_24_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message24_txinp" hwSignal="txinp" hwResource="//@hwResources.26" required="false" visible="true"/>
  <virtualSignals name="event_lmo_24_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message24_rxinp" hwSignal="rxinp" hwResource="//@hwResources.26" required="false" visible="true"/>
  <virtualSignals name="event_lmo_25_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message25_txinp" hwSignal="txinp" hwResource="//@hwResources.27" required="false" visible="true"/>
  <virtualSignals name="event_lmo_25_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message25_rxinp" hwSignal="rxinp" hwResource="//@hwResources.27" required="false" visible="true"/>
  <virtualSignals name="event_lmo_26_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message26_txinp" hwSignal="txinp" hwResource="//@hwResources.28" required="false" visible="true"/>
  <virtualSignals name="event_lmo_26_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message26_rxinp" hwSignal="rxinp" hwResource="//@hwResources.28" required="false" visible="true"/>
  <virtualSignals name="event_lmo_27_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message27_txinp" hwSignal="txinp" hwResource="//@hwResources.29" required="false" visible="true"/>
  <virtualSignals name="event_lmo_27_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message27_rxinp" hwSignal="rxinp" hwResource="//@hwResources.29" required="false" visible="true"/>
  <virtualSignals name="event_lmo_28_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message28_txinp" hwSignal="txinp" hwResource="//@hwResources.30" required="false" visible="true"/>
  <virtualSignals name="event_lmo_28_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message28_rxinp" hwSignal="rxinp" hwResource="//@hwResources.30" required="false" visible="true"/>
  <virtualSignals name="event_lmo_29_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message29_txinp" hwSignal="txinp" hwResource="//@hwResources.31" required="false" visible="true"/>
  <virtualSignals name="event_lmo_29_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message29_rxinp" hwSignal="rxinp" hwResource="//@hwResources.31" required="false" visible="true"/>
  <virtualSignals name="event_lmo_30_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message30_txinp" hwSignal="txinp" hwResource="//@hwResources.32" required="false" visible="true"/>
  <virtualSignals name="event_lmo_30_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message30_rxinp" hwSignal="rxinp" hwResource="//@hwResources.32" required="false" visible="true"/>
  <virtualSignals name="event_lmo_31_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message31_txinp" hwSignal="txinp" hwResource="//@hwResources.33" required="false" visible="true"/>
  <virtualSignals name="event_lmo_31_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message31_rxinp" hwSignal="rxinp" hwResource="//@hwResources.33" required="false" visible="true"/>
  <virtualSignals name="event_lmo_32_txinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message32_txinp" hwSignal="txinp" hwResource="//@hwResources.34" required="false" visible="true"/>
  <virtualSignals name="event_lmo_32_rxinp" URI="http://resources/4.1.24/app/CAN_NODE/0/vs_message32_rxinp" hwSignal="rxinp" hwResource="//@hwResources.34" required="false" visible="true"/>
  <virtualSignals name="CAN Receive Pin_signal" URI="http://resources/4.1.24/app/CAN_NODE/0/__pin_vs_can_rxpin" hwSignal="pin" hwResource="//@hwResources.35"/>
  <virtualSignals name="CAN Transmit Pin_signal" URI="http://resources/4.1.24/app/CAN_NODE/0/__pin_vs_can_txpin" hwSignal="pin" hwResource="//@hwResources.36"/>
  <requiredApps URI="http://resources/4.1.24/app/CAN_NODE/0/can_global" requiredAppName="GLOBAL_CAN" requiringMode="SHARABLE">
    <downwardMapList xsi:type="ResourceModel:App" href="../../GLOBAL_CAN/v4_0_20/GLOBAL_CAN_0.app#/"/>
  </requiredApps>
  <hwResources name="CAN Receive Pin" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_port_pad_can_rx" resourceGroupUri="port/p/*/pad/*" mResGrpUri="port/p/*/pad/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/port3/port3_3.dd#//@provided.6"/>
  </hwResources>
  <hwResources name="CAN Transmit Pin" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_port_pad_can_tx" resourceGroupUri="port/p/*/pad/*" mResGrpUri="port/p/*/pad/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/port3/port3_3.dd#//@provided.0"/>
  </hwResources>
  <hwResources name="NODE" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_node" resourceGroupUri="peripheral/can/*/node/*" mResGrpUri="peripheral/can/*/node/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/can/can_0.dd#//@provided.17"/>
  </hwResources>
  <hwResources name="MO_1" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj1" resourceGroupUri="peripheral/can/*/mo/*" mResGrpUri="peripheral/can/*/mo/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/can/can_0.dd#//@provided.13"/>
  </hwResources>
  <hwResources name="MO_2" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj2" resourceGroupUri="peripheral/can/*/mo/*" mResGrpUri="peripheral/can/*/mo/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/can/can_0.dd#//@provided.0"/>
  </hwResources>
  <hwResources name="MO_3" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj3" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_4" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj4" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_5" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj5" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_6" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj6" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_7" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj7" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_8" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj8" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_9" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj9" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_10" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj10" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_11" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj11" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_12" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj12" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_13" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj13" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_14" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj14" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_15" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj15" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_16" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj16" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_17" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj17" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_18" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj18" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_19" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj19" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_20" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj20" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_21" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj21" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_22" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj22" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_23" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj23" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_24" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj24" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_25" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj25" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_26" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj26" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_27" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj27" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_28" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj28" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_29" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj29" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_30" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj30" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_31" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj31" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="MO_32" URI="http://resources/4.1.24/app/CAN_NODE/0/hwres_can_mobj32" resourceGroupUri="" required="false" mResGrpUri="peripheral/can/*/mo/*"/>
  <hwResources name="CAN Receive Pin" URI="http://resources/4.1.24/app/CAN_NODE/0/__pin_hwres_port_pad_can_rx" resourceGroupUri="devicepackage/0/f2" constraintType="GLOBAL_RESOURCE" mResGrpUri="devicepackage/0/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/DEVICEPACKAGE/DEVICEPACKAGE_0.dd#//@provided.3"/>
  </hwResources>
  <hwResources name="CAN Transmit Pin" URI="http://resources/4.1.24/app/CAN_NODE/0/__pin_hwres_port_pad_can_tx" resourceGroupUri="devicepackage/0/d3" constraintType="GLOBAL_RESOURCE" mResGrpUri="devicepackage/0/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/DEVICEPACKAGE/DEVICEPACKAGE_0.dd#//@provided.2"/>
  </hwResources>
  <connections URI="http://resources/4.1.24/app/CAN_NODE/0/http://resources/4.1.24/app/CAN_NODE/0/vs_can_rxpin/http://resources/4.1.24/app/CAN_NODE/0/vs_can_rxd" systemDefined="true" sourceSignal="receive_pad" targetSignal="receive_pin" srcVirtualSignal="//@virtualSignals.2" targetVirtualSignal="//@virtualSignals.0"/>
  <connections URI="http://resources/4.1.24/app/CAN_NODE/0/http://resources/4.1.24/app/CAN_NODE/0/vs_can_txd/http://resources/4.1.24/app/CAN_NODE/0/vs_can_txpin" systemDefined="true" sourceSignal="transmit_pin" targetSignal="transmit_pad" srcVirtualSignal="//@virtualSignals.1" targetVirtualSignal="//@virtualSignals.3"/>
  <connections URI="http://resources/4.1.24/app/CAN_NODE/0/http://resources/4.1.24/app/CAN_NODE/0/vs_can_rxpin/http://resources/4.1.24/app/CAN_NODE/0/__pin_vs_can_rxpin" systemDefined="true" sourceSignal="receive_pad" targetSignal="CAN Receive Pin_signal" srcVirtualSignal="//@virtualSignals.2" targetVirtualSignal="//@virtualSignals.72"/>
  <connections URI="http://resources/4.1.24/app/CAN_NODE/0/http://resources/4.1.24/app/CAN_NODE/0/__pin_vs_can_rxpin/http://resources/4.1.24/app/CAN_NODE/0/vs_can_rxpin" systemDefined="true" sourceSignal="CAN Receive Pin_signal" targetSignal="receive_pad" srcVirtualSignal="//@virtualSignals.72" targetVirtualSignal="//@virtualSignals.2"/>
  <connections URI="http://resources/4.1.24/app/CAN_NODE/0/http://resources/4.1.24/app/CAN_NODE/0/vs_can_txpin/http://resources/4.1.24/app/CAN_NODE/0/__pin_vs_can_txpin" systemDefined="true" sourceSignal="transmit_pad" targetSignal="CAN Transmit Pin_signal" srcVirtualSignal="//@virtualSignals.3" targetVirtualSignal="//@virtualSignals.73"/>
  <connections URI="http://resources/4.1.24/app/CAN_NODE/0/http://resources/4.1.24/app/CAN_NODE/0/__pin_vs_can_txpin/http://resources/4.1.24/app/CAN_NODE/0/vs_can_txpin" systemDefined="true" sourceSignal="CAN Transmit Pin_signal" targetSignal="transmit_pad" srcVirtualSignal="//@virtualSignals.73" targetVirtualSignal="//@virtualSignals.3"/>
  <connections URI="http://resources/4.1.24/app/CAN_NODE/0/http://resources/4.1.24/app/CAN_NODE/0/vs_message2_rxinp/http://resources/4.0.10/app/INTERRUPT/1/vs_nvic_signal_in" sourceSignal="event_lmo_02_rxinp" targetSignal="sr_irq" srcVirtualSignal="//@virtualSignals.11">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../INTERRUPT/v4_0_10/INTERRUPT_1.app#//@virtualSignals.0"/>
    <targetVirtualSignal href="../../INTERRUPT/v4_0_10/INTERRUPT_1.app#//@virtualSignals.0"/>
  </connections>
</ResourceModel:App>

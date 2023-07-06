<?xml version="1.0" encoding="ASCII"?>
<ResourceModel:App xmi:version="2.0" xmlns:xmi="http://www.omg.org/XMI" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:ResourceModel="http://www.infineon.com/Davex/Resource.ecore" name="GLOBAL_CAN" URI="http://resources/4.0.20/app/GLOBAL_CAN/0" description="GLOBAL_CAN APP configures global &#xA; resources of MultiCAN module." version="4.0.20" minDaveVersion="4.0.0" instanceLabel="GLOBAL_CAN_0" appLabel="">
  <upwardMapList xsi:type="ResourceModel:RequiredApp" href="../../CAN_NODE/v4_1_24/CAN_NODE_0.app#//@requiredApps.0"/>
  <properties singleton="true" provideInit="true" sharable="true"/>
  <requiredApps URI="http://resources/4.0.20/app/GLOBAL_CAN/0/clock_app" requiredAppName="CLOCK_XMC4" requiringMode="SHARABLE">
    <downwardMapList xsi:type="ResourceModel:App" href="../../CLOCK_XMC4/v4_0_24/CLOCK_XMC4_0.app#/"/>
  </requiredApps>
  <hwResources name=" GLOBAL_CAN" URI="http://resources/4.0.20/app/GLOBAL_CAN/0/hwres_can_global" resourceGroupUri="peripheral/can/*/global" mResGrpUri="peripheral/can/*/global">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/can/can_0.dd#//@provided.12"/>
  </hwResources>
</ResourceModel:App>

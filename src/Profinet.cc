//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Profinet.h"





//namespace inet {
//namespace profinet {
Define_Module(Profinet);
//Register_Class(Profinet);


void Profinet::initialize(int stage)
{

    LayeredProtocolBase::initialize(stage);
    if (stage == inet::INITSTAGE_LOCAL)
        interfaceTable = inet::getModuleFromPar<inet::IInterfaceTable>(par("interfaceTableModule"), this);
    else if (stage == inet::INITSTAGE_NETWORK_LAYER) {
        registerService(inet::Protocol::profinet, nullptr, gate("queueIn"));
        registerProtocol(inet::Protocol::profinet, gate("queueOut"), nullptr);
    }
    llcSocket.setOutputGate(gate("transportOut"));
}

void Profinet::handleStartOperation(inet::LifecycleOperation *operation){

}
void Profinet::handleStopOperation(inet::LifecycleOperation *operation){

}
void Profinet::handleCrashOperation(inet::LifecycleOperation *operation){

}
const inet::Protocol& Profinet::getProtocol() const{
    return inet::Protocol::profinet;
}


void Profinet::handleLowerPacket(inet::Packet *packet){
    EV_INFO << "Got Profinet packet" << packet->getName() << "'\n";

    llcSocket.open(-1, -1);

    inet::MacAddress destMacAddress;
    const char *destAddress = par("destAddress");
    if (destAddress[0]) {
        if (!destMacAddress.tryParse(destAddress))
            destMacAddress = inet::L3AddressResolver().resolve(destAddress, inet::L3AddressResolver::ADDR_MAC).toMac();
    }
    packet->addTagIfAbsent<inet::MacAddressReq>()->setDestAddress(destMacAddress);

    inet::Packet *datapacket = new inet::Packet("Profi", inet::IEEE802CTRL_DATA);
    datapacket->addTag<inet::MacAddressReq>()->setDestAddress(destMacAddress);

    datapacket->addTag<inet::PacketProtocolTag>()->setProtocol(&inet::Protocol::profinet);

    auto rawBytesData = inet::makeShared<inet::BytesChunk>(); // 10 raw bytes
    rawBytesData->setBytes({0xC0, 0x00, 0x88, 0x92, 0x80 ,0x00 ,0x80 ,0x80 ,0x80 ,0x80 ,0x80 ,0x16 ,0xf0 ,0x00 ,0x00 ,0x80 ,0x80 ,0x00 ,0x00 ,0x00, 0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00, 0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x55 ,0x00 ,0x35, 0x00});
    datapacket->insertAtBack(rawBytesData);


    emit(inet::packetSentSignal, datapacket);
    llcSocket.send(datapacket);

    //sendDown(packet);

}

void Profinet::sendDown(inet::cMessage *message, int interfaceId){
    send(message, "queueOut");
}


//}
//}
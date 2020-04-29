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
#include "ProfinetFrame_m.h"

//#include <cstringtokenizer.h>





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
    else if (stage == inet::INITSTAGE_LAST){
        if (par("bootstrap")){
            scheduleAt(inet::simTime(), new inet::cMessage);
        }

        /*Schedulazione del del self message per l'incremento del contatore*/
        timeout = (inet::simTime() + inet::SimTime(31250, inet::SIMTIME_NS));
        timer = timer = new inet::cMessage("timer");
        scheduleAt(timeout, timer);


        llcSocket.setOutputGate(gate("transportOut"));
        llcSocket.open(-1, 0xf0);
    }



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



    char msgname[30];
    sprintf(msgname, "req-%d-%ld", getId(), seqNum);

    EV_INFO << "Generating Profinet packet" << msgname << "'\n";

    inet::Packet *datapacket = new inet::Packet(msgname, inet::IEEE802CTRL_DATA);

    auto destMac = packet->getTag<inet::MacAddressInd>()->getSrcAddress();
    datapacket->addTag<inet::MacAddressReq>()->setDestAddress(destMac);

    datapacket->addTag<inet::PacketProtocolTag>()->setProtocol(&inet::Protocol::profinet);

    auto frame = inet::makeShared<ProfinetFrame>(); // 10 raw bytes
    frame->setVlan(0xC000);
    frame->setEtherType(0x8892);
    frame->setFrameId(0x8000);
    frame->setCycleCounter(seqNum);
    frame->setDataStatus(0x3500);
    frame->setChunkLength(inet::B(50));
    datapacket->insertAtBack(frame);


    emit(inet::packetSentSignal, datapacket);
    llcSocket.send(datapacket);

    //seqNum++;

    //sendDown(packet);
}

void Profinet::sendDown(inet::cMessage *message, int interfaceId){
    //send(message, "queueOut");
}

inet::MacAddress Profinet::resolveDestMacAddress(const char *destAddress)
{
    inet::MacAddress destMacAddress;
    //const char *destAddress = par("destAddress");
    if (destAddress[0]) {
        if (!destMacAddress.tryParse(destAddress))
            destMacAddress = inet::L3AddressResolver().resolve(destAddress, inet::L3AddressResolver::ADDR_MAC).toMac();
    }

    return destMacAddress;
}

void Profinet::handleSelfMessage(inet::cMessage *message){
    EV_INFO << "Got self message" << message->getName() << "'\n";

    if(message == timer){
        EV_INFO << "!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*!*Increment sequence number" << message->getName() << "'\n";
        seqNum++;
        timeout = (inet::simTime() + inet::SimTime(31250, inet::SIMTIME_NS));
        timer = timer = new inet::cMessage("timer");
        scheduleAt(timeout, timer);
        return;
    }

     inet::cStringTokenizer tokenizer(par("destAddress"));
     while (tokenizer.hasMoreTokens())
         genericSend(resolveDestMacAddress(par("srcAddress")), resolveDestMacAddress(tokenizer.nextToken()));
}

void Profinet::genericSend(inet::MacAddress src, inet::MacAddress dest){




    char msgname[30];
    sprintf(msgname, "req-%d-%ld", getId(), seqNum);

    EV_INFO << "Generating Profinet packet" << msgname << "'\n";

    inet::Packet *datapacket = new inet::Packet(msgname, inet::IEEE802CTRL_DATA);;

    datapacket->addTag<inet::MacAddressReq>()->setDestAddress(dest);
    datapacket->getTag<inet::MacAddressReq>()->setSrcAddress(src);

    datapacket->addTag<inet::PacketProtocolTag>()->setProtocol(&inet::Protocol::profinet);

    //ProfinetFrame frame = ProfinetFrame(msgname);




    auto frame = inet::makeShared<ProfinetFrame>(); // 10 raw bytes
    frame->setVlan(0xC000);
    frame->setEtherType(0x8892);
    frame->setFrameId(0x8000);
    frame->setCycleCounter(seqNum);
    frame->setDataStatus(0x3500);
    frame->setChunkLength(inet::B(50));
    //rawBytesData->setBytes({0xC0, 0x00, 0x88, 0x92, 0x80 ,0x00 ,0x80 ,0x80 ,0x80 ,0x80 ,0x80 ,0x16 ,0xf0 ,0x00 ,0x00 ,0x80 ,0x80 ,0x00 ,0x00 ,0x00, 0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00, 0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x55 ,0x00 ,0x35, 0x00});
    datapacket->insertAtBack(frame);


    //emit(inet::packetSentSignal, datapacket);
    EV_INFO << "Sending profinet frame\n";
    llcSocket.send(datapacket);

    //seqNum++;

}


//}
//}

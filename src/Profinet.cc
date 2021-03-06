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

        cycleCounter = par("cycleCounter"); // Inizializza il cycle counter

        if (par("bootstrap")){
            tokenizer = inet::cStringTokenizer(par("destAddress"));  //faccio il parse dei MAC degli slave
            bootstarpSelfMsg = new inet::cMessage("bootstarpSelfMsg");
            scheduleAt(inet::simTime(), bootstarpSelfMsg);
        }

        /*Schedulazione del del self message per l'incremento del contatore*/
        timeout = (inet::simTime() + inet::SimTime(31250, inet::SIMTIME_NS));
        basicTickTimer = new inet::cMessage("basicTickTimer");
        scheduleAt(timeout, basicTickTimer);

        scheduleAt(inet::simTime() + inet::SimTime(int(par("sendClockFactor"))*31.25*1000, inet::SIMTIME_NS) + inet::SimTime(normal(0,127000), inet::SIMTIME_NS), new inet::cMessage("sendProfiPacket"));


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
    sprintf(msgname, "req-%d-%ld", getId(), cycleCounter);

    EV_INFO << "Generating Profinet packet" << msgname << "'\n";

    inet::Packet *datapacket = new inet::Packet(msgname, inet::IEEE802CTRL_DATA);

    auto destMac = packet->getTag<inet::MacAddressInd>()->getSrcAddress();
    datapacket->addTag<inet::MacAddressReq>()->setDestAddress(destMac);

    datapacket->addTag<inet::PacketProtocolTag>()->setProtocol(&inet::Protocol::profinet);

    auto frame = inet::makeShared<ProfinetFrame>(); // 10 raw bytes
    frame->setVlan(0xC000);
    frame->setEtherType(0x8892);
    frame->setFrameId(0x8000);
    frame->setCycleCounter(normalizeCycleCounter(cycleCounter));
    frame->setDataStatus(0x35);
    frame->setTransferStatus(0x00);
    frame->setChunkLength(inet::B(50));
    datapacket->insertAtBack(frame);



    if((bool(par("isMaster")))){
        queue.insert(datapacket);
        // TODO: il *2 � il numero di device. serve per non far trasmettere pi� dispositivi nello stesso slot

        //scheduleAt(inet::simTime() + inet::SimTime(100, inet::SIMTIME_US), new inet::cMessage("sendProfiPacket"));
    }
    else{
        emit(inet::packetSentSignal, datapacket);
        llcSocket.send(datapacket);

    }




    //emit(inet::packetSentSignal, datapacket);
    //llcSocket.send(datapacket);

    //cycleCounter++;

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
    EV_INFO << "Got self message " << message->getName() << "'\n";

    if(message == basicTickTimer){
        EV_INFO << "Self Message: Increment cycle counter " << message->getName() << "'\n";
        timeout = (inet::simTime() + inet::SimTime(31250, inet::SIMTIME_NS));
        basicTickTimer = new inet::cMessage("basicTickTimer");
        scheduleAt(timeout, basicTickTimer);
        cycleCounter++;
    }

    std::string msg = message->getName();

    if (msg == "sendProfiPacket")
    {
        EV_INFO << "Self Message: send scheduled Profinet Frame  " << message->getName() << "'\n";
        long sendTime = int(par("sendClockFactor"))*31.25*1000;
        long jitter;
        do{
            jitter = normal(0,273000);
        } while(abs(jitter)>sendTime);
        sendTime += jitter;
        scheduleAt(inet::simTime() +
                   inet::SimTime(sendTime, inet::SIMTIME_NS) , new inet::cMessage("sendProfiPacket"));
        if(!queue.isEmpty()){
            inet::Packet *datapacket = (inet::Packet *)queue.pop();
            emit(inet::packetSentSignal, datapacket);
            llcSocket.send(datapacket);
        }
    }

   // + inet::SimTime(normal(0,273000), inet::SIMTIME_NS)


    if (message == bootstarpSelfMsg){

        EV_INFO << "----------------------- bootstrap " << message->getName() << "'\n";


        /*invio il messaggio se ci sono MAC disponibili*/
        if (tokenizer.hasMoreTokens()){
             genericSend(resolveDestMacAddress(par("srcAddress")), resolveDestMacAddress(tokenizer.nextToken()));
        }

        /*Ho inviato il messaggio: ora controllo se ne rimangono altri e in tal caso schedulo l'invio del messaggio successivo*/
        if (tokenizer.hasMoreTokens()){
            bootstarpSelfMsg = new inet::cMessage("bootstarpSelfMsg");
            //scheduleAt(inet::simTime() + inet::SimTime(int(par("sendTime"))*1000, inet::SIMTIME_NS), bootstarpSelfMsg);
            scheduleAt(inet::simTime() + inet::SimTime(500, inet::SIMTIME_NS), bootstarpSelfMsg);
        }
    }



 /*   if(bool(par("isMaster")) && isMasterSendScheduled()){
        EV_WARN << " Master send scheduled\n";
        if(!queue.isEmpty()){
            inet::Packet *datapacket = (inet::Packet *)queue.pop();
            emit(inet::packetSentSignal, datapacket);
            llcSocket.send(datapacket);
        }
    }*/



}

void Profinet::genericSend(inet::MacAddress src, inet::MacAddress dest){




    char msgname[30];
    sprintf(msgname, "req-%d-%ld", getId(), cycleCounter);

    EV_INFO << "Generating Profinet packet" << msgname << "'\n";

    inet::Packet *datapacket = new inet::Packet(msgname, inet::IEEE802CTRL_DATA);;

    datapacket->addTag<inet::MacAddressReq>()->setDestAddress(dest);
    datapacket->getTag<inet::MacAddressReq>()->setSrcAddress(src);

    datapacket->addTag<inet::PacketProtocolTag>()->setProtocol(&inet::Protocol::profinet);

    //ProfinetFrame frame = ProfinetFrame(msgname);




    auto frame = inet::makeShared<ProfinetFrame>();
    frame->setVlan(0xC000);
    frame->setEtherType(0x8892);
    frame->setFrameId(0x8000);
    frame->setCycleCounter(normalizeCycleCounter(cycleCounter));
    frame->setDataStatus(0x35);
    frame->setTransferStatus(0x00);
    frame->setChunkLength(inet::B(50));
    //rawBytesData->setBytes({0xC0, 0x00, 0x88, 0x92, 0x80 ,0x00 ,0x80 ,0x80 ,0x80 ,0x80 ,0x80 ,0x16 ,0xf0 ,0x00 ,0x00 ,0x80 ,0x80 ,0x00 ,0x00 ,0x00, 0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00, 0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x55 ,0x00 ,0x35, 0x00});
    datapacket->insertAtBack(frame);


    //emit(inet::packetSentSignal, datapacket);
    EV_INFO << "Sending profinet frame\n";
    llcSocket.send(datapacket);

    //cycleCounter++;

}

bool Profinet::isMasterSendScheduled(){
    // TODO: possibile bug con int
    int mult = int(par("sendTime"))/31.25;

    return ((cycleCounter % mult) == 0);
}

long Profinet::normalizeCycleCounter(long currentCycleCounter){
    return (currentCycleCounter/long(par("sendClockFactor")))*long(par("sendClockFactor"));
}

/*
void Profinet::handleSelfMessage(inet::cMessage *message){

    if(message == basicTickTimer){   // Increment the cycle counter
        timeout = (inet::simTime() + inet::SimTime(31250, inet::SIMTIME_NS));
        basicTickTimer = new inet::cMessage("basicTickTimer");
        scheduleAt(timeout, basicTickTimer);
        cycleCounter++;
    }

    std::string msg = message->getName();
    if (msg == "sendProfiPacket"){   // Send and schedule the next Profinet frame
        long sendTime = int(par("sendClockFactor"))*31.25*1000 + normal(0,273000);
        scheduleAt(inet::simTime() +
                   inet::SimTime(sendTime, inet::SIMTIME_NS),
                   new inet::cMessage("sendProfiPacket"));
        if(!queue.isEmpty()){
            inet::Packet *datapacket = (inet::Packet *)queue.pop();
            emit(inet::packetSentSignal, datapacket);
            llcSocket.send(datapacket);
        }
    }
}
*/
//}
//}

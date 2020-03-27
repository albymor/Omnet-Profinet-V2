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



#include <stdio.h>
#include <string.h>
#include <math.h>

#include "EthernetAppClient.h"

#include "inet/applications/ethernet/EtherApp_m.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/TimeTag_m.h"
#include "inet/common/packet/Packet.h"
#include "inet/linklayer/common/Ieee802Ctrl.h"
#include "inet/linklayer/common/Ieee802SapTag_m.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"

namespace inet {

Define_Module(EthernetAppClient);

EthernetAppClient::~EthernetAppClient()
{
    cancelAndDelete(timerMsg);
}

void EthernetAppClient::initialize(int stage)
{
    if (stage == INITSTAGE_APPLICATION_LAYER && isGenerator())
        timerMsg = new cMessage("generateNextPacket");

    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        reqLength = &par("reqLength");
        respLength = &par("respLength");
        sendInterval = &par("sendInterval");

        localSap = par("localSAP");
        remoteSap = par("remoteSAP");

        seqNum = 0;
        WATCH(seqNum);

        // statistics
        packetsSent = packetsReceived = 0;
        WATCH(packetsSent);
        WATCH(packetsReceived);

        startTime = par("startTime");
        stopTime = par("stopTime");
        if (stopTime >= SIMTIME_ZERO && stopTime < startTime)
            throw cRuntimeError("Invalid startTime/stopTime parameters");
        llcSocket.setOutputGate(gate("out"));
        llcSocket.setCallback(this);
    }
}

void EthernetAppClient::handleMessageWhenUp(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        if (msg->getKind() == START) {
            EV_DEBUG << getFullPath() << " registering DSAP " << localSap << "\n";
            llcSocket.open(-1, localSap);

            destMacAddress = resolveDestMacAddress();
            // if no dest address given, nothing to do
            if (destMacAddress.isUnspecified())
                return;
        }
        sendPacket();
        scheduleNextPacket(false);
    }
    else
        llcSocket.processMessage(msg);
}

void EthernetAppClient::handleStartOperation(LifecycleOperation *operation)
{
    if (isGenerator())
        scheduleNextPacket(true);
}

void EthernetAppClient::handleStopOperation(LifecycleOperation *operation)
{
    cancelNextPacket();
    llcSocket.close();
    delayActiveOperationFinish(par("stopOperationTimeout"));
}

void EthernetAppClient::handleCrashOperation(LifecycleOperation *operation)
{
    cancelNextPacket();
    if (operation->getRootModule() != getContainingNode(this))
        llcSocket.destroy();
}

void EthernetAppClient::socketClosed(inet::Ieee8022LlcSocket *socket)
{
    if (operationalState == State::STOPPING_OPERATION && !llcSocket.isOpen())
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

bool EthernetAppClient::isGenerator()
{
    return par("destAddress").stringValue()[0];
}

void EthernetAppClient::scheduleNextPacket(bool start)
{
    simtime_t cur = simTime();
    simtime_t next;
    if (start) {
        next = cur <= startTime ? startTime : cur;
        timerMsg->setKind(START);
    }
    else {
        next = cur + *sendInterval;
        timerMsg->setKind(NEXT);
    }
    if (stopTime < SIMTIME_ZERO || next < stopTime)
        scheduleAt(next, timerMsg);
}

void EthernetAppClient::cancelNextPacket()
{
    if (timerMsg)
        cancelEvent(timerMsg);
}

MacAddress EthernetAppClient::resolveDestMacAddress()
{
    MacAddress destMacAddress;
    const char *destAddress = par("destAddress");
    if (destAddress[0]) {
        if (!destMacAddress.tryParse(destAddress))
            destMacAddress = L3AddressResolver().resolve(destAddress, L3AddressResolver::ADDR_MAC).toMac();
    }
    return destMacAddress;
}

void EthernetAppClient::sendPacket()
{
    seqNum++;

    char msgname[30];
    sprintf(msgname, "req-%d-%ld", getId(), seqNum);
    EV_WARN << "Generating packet !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!`" << msgname << "'\n";

    Packet *datapacket = new Packet(msgname, IEEE802CTRL_DATA);
    const auto& data = makeShared<EtherAppReq>();

    long len = *reqLength;
    data->setChunkLength(B(len));
    data->setRequestId(seqNum);

    long respLen = *respLength;
    data->setResponseBytes(respLen);

    data->addTag<CreationTimeTag>()->setCreationTime(simTime());

    datapacket->insertAtBack(data);

    datapacket->addTag<MacAddressReq>()->setDestAddress(destMacAddress);
    auto ieee802SapReq = datapacket->addTag<Ieee802SapReq>();
    ieee802SapReq->setSsap(localSap);
    ieee802SapReq->setDsap(remoteSap);

    emit(packetSentSignal, datapacket);
    llcSocket.send(datapacket);
    packetsSent++;
}

void EthernetAppClient::socketDataArrived(Ieee8022LlcSocket*, Packet *msg)
{
    EV_INFO << "Received packet `" << msg->getName() << "'\n";

    packetsReceived++;
    emit(packetReceivedSignal, msg);
    delete msg;
}

void EthernetAppClient::finish()
{
    cancelAndDelete(timerMsg);
    timerMsg = nullptr;
}

} // namespace inet



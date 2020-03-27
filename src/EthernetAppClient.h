/*
 * EthernetAppClient.h
 *
 *  Created on: 27 mar 2020
 *      Author: alber
 */

#ifndef ETHERNETAPPCLIENT_H_
#define ETHERNETAPPCLIENT_H_

#include "inet/common/INETDefs.h"

#include "inet/applications/base/ApplicationBase.h"
#include "inet/common/packet/Packet.h"
#include "inet/linklayer/common/MacAddress.h"
#include "inet/linklayer/ieee8022/Ieee8022LlcSocket.h"
#include "inet/linklayer/ieee8022/Ieee8022LlcSocketCommand_m.h"

namespace inet {

/**
 * Simple traffic generator for the Ethernet model.
 */
class INET_API EthernetAppClient : public ApplicationBase, public Ieee8022LlcSocket::ICallback
{
  protected:
    enum Kinds { START = 100, NEXT };

    // send parameters
    long seqNum = 0;
    cPar *reqLength = nullptr;
    cPar *respLength = nullptr;
    cPar *sendInterval = nullptr;

    int localSap = -1;
    int remoteSap = -1;
    MacAddress destMacAddress;

    // self messages
    cMessage *timerMsg = nullptr;
    simtime_t startTime;
    simtime_t stopTime;

    Ieee8022LlcSocket llcSocket;

    // receive statistics
    long packetsSent = 0;
    long packetsReceived = 0;

  protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void handleMessageWhenUp(cMessage *msg) override;
    virtual void finish() override;

    virtual bool isGenerator();
    virtual void scheduleNextPacket(bool start);
    virtual void cancelNextPacket();

    virtual MacAddress resolveDestMacAddress();

    virtual void sendPacket();

    // Ieee8022LlcSocket::ICallback
    virtual void socketDataArrived(Ieee8022LlcSocket*, Packet *msg) override;
    virtual void socketClosed(Ieee8022LlcSocket *socket) override;

    // ApplicationBase:
    virtual void handleStartOperation(LifecycleOperation *operation) override;
    virtual void handleStopOperation(LifecycleOperation *operation) override;
    virtual void handleCrashOperation(LifecycleOperation *operation) override;

  public:
    EthernetAppClient() {}
    virtual ~EthernetAppClient();
};

} // namespace inet
#endif /* ETHERNETAPPCLIENT_H_ */

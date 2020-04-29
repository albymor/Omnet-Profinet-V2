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

#ifndef PROFINET_H_
#define PROFINET_H_

#include "inet/common/packet/Packet.h"
#include "inet/networklayer/base/NetworkProtocolBase.h"
#include "inet/common/Protocol.h"
#include "inet/common/lifecycle/OperationalBase.h"
#include "inet/common/IProtocolRegistrationListener.h"

#include "inet/applications/common/SocketTag_m.h"
#include "inet/common/INETUtils.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/ProtocolGroup.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/packet/Message.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/networklayer/base/NetworkProtocolBase.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/networklayer/contract/L3SocketCommand_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/applications/ethernet/EtherApp_m.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/TimeTag_m.h"
#include "inet/common/packet/Packet.h"
#include "inet/linklayer/common/Ieee802Ctrl.h"
#include "inet/linklayer/common/Ieee802SapTag_m.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/applications/base/ApplicationBase.h"
#include "inet/common/packet/Packet.h"
#include "inet/linklayer/common/MacAddress.h"
#include "inet/linklayer/ieee8022/Ieee8022LlcSocket.h"
#include "inet/linklayer/ieee8022/Ieee8022LlcSocketCommand_m.h"

//#include <queue>
//#include <cqueue.h>

//namespace inet {
//namespace profinet {

class Profinet : public inet::NetworkProtocolBase {

protected:
    inet::Ieee8022LlcSocket llcSocket;
    long seqNum = 0;
    inet::simtime_t timeout;
    inet::cMessage * timer;
    inet::cStringTokenizer tokenizer = inet::cStringTokenizer(nullptr);
    inet::cMessage * bootstarpSelfMsg;
    inet::cQueue queue;



public:
    virtual void initialize(int stage) override;
    void handleStartOperation(inet::LifecycleOperation *operation) override; // TODO
    void handleStopOperation(inet::LifecycleOperation *operation) override;
    void handleCrashOperation(inet::LifecycleOperation *operation) override;
    const inet::Protocol& getProtocol() const override;
    void handleLowerPacket(inet::Packet *packet) override;
    void sendDown(inet::cMessage *message, int interfaceId = -1) override;
    inet::MacAddress resolveDestMacAddress(const char *destAddress);
    void handleSelfMessage(inet::cMessage *message) override;
    void genericSend(inet::MacAddress src, inet::MacAddress dest);
};
//}
//}
#endif /* PROFINET_H_ */

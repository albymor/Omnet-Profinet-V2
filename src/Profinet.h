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
//namespace inet {
//namespace profinet {

class Profinet : public inet::NetworkProtocolBase {
public:
    virtual void initialize(int stage) override;
    void handleStartOperation(inet::LifecycleOperation *operation) override; // TODO
    void handleStopOperation(inet::LifecycleOperation *operation) override;
    void handleCrashOperation(inet::LifecycleOperation *operation) override;
    const inet::Protocol& getProtocol() const override;
};
//}
//}
#endif /* PROFINET_H_ */

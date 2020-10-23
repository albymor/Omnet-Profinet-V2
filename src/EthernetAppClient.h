/*
 * EthernetAppClient.h
 *
 *  Created on: 27 mar 2020
 *      Author: alber
 */

#ifndef ETHERNETAPPCLIENT_H_
#define ETHERNETAPPCLIENT_H_

#include "inet/applications/ethernet/EtherAppClient.h"

#include "inet/applications/ethernet/EtherApp_m.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/packet/Packet.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/common/ProtocolTag_m.h"

namespace inet {

/**
 * Simple traffic generator for the Ethernet model.
 */
class EthernetAppClient : public EtherAppClient
{
  protected:
    void sendPacket() override;
};

} // namespace inet
#endif /* ETHERNETAPPCLIENT_H_ */

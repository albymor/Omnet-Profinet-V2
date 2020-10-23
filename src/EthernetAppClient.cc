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


//#include "inet/applications/ethernet/EtherApp_m.h"
/*#include "inet/common/ModuleAccess.h"
#include "inet/common/TimeTag_m.h"
#include "inet/common/packet/Packet.h"*/
#include "inet/linklayer/common/Ieee802Ctrl.h"
//#include "inet/linklayer/common/Ieee802SapTag_m.h"
//#include "inet/linklayer/common/MacAddressTag_m.h"
//#include "inet/networklayer/common/L3AddressResolver.h"
//#include "inet/common/ProtocolTag_m.h"
//#include "inet/common/Protocol.h"

namespace inet {
Define_Module(EthernetAppClient);

void EthernetAppClient::sendPacket()
{
    seqNum++;

    char msgname[30];
    sprintf(msgname, "req-%d-%ld", getId(), seqNum);
    EV_INFO << "Generating packet!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! `" << msgname << "'\n";

    Packet *datapacket = new Packet(msgname, IEEE802CTRL_DATA);
    /*const auto& data = makeShared<EtherAppReq>();

    long len = *reqLength;
    data->setChunkLength(B(len));
    data->setRequestId(seqNum);

    long respLen = *respLength;
    data->setResponseBytes(respLen);

    data->addTag<CreationTimeTag>()->setCreationTime(simTime());

    datapacket->insertAtBack(data);*/

    datapacket->addTag<MacAddressReq>()->setDestAddress(destMacAddress);
    /*auto ieee802SapReq = datapacket->addTag<Ieee802SapReq>();
    ieee802SapReq->setSsap(localSap);
    ieee802SapReq->setDsap(remoteSap);*/

    datapacket->addTag<PacketProtocolTag>()->setProtocol(&Protocol::profinet);

    auto rawBytesData = makeShared<BytesChunk>(); // 10 raw bytes
    rawBytesData->setBytes({0xC0, 0x00, 0x88, 0x92, 0x80 ,0x00 ,0x80 ,0x80 ,0x80 ,0x80 ,0x80 ,0x16 ,0xf0 ,0x00 ,0x00 ,0x80 ,0x80 ,0x00 ,0x00 ,0x00, 0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00, 0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x55 ,0x00 ,0x35, 0x00});
    datapacket->insertAtBack(rawBytesData);


    emit(packetSentSignal, datapacket);
    llcSocket.send(datapacket);
    packetsSent++;
}
} // namespace inet



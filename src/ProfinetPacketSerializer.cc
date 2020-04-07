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

#include "ProfinetPacketSerializer.h"
#include "ProfinetFrame_m.h"
#include "inet/common/packet/serializer/ChunkSerializerRegistry.h"


namespace inet {
Register_Serializer(ProfinetFrame, ProfinetPacketSerializer);
}

void ProfinetPacketSerializer::serialize(inet::MemoryOutputStream& stream, const inet::Ptr<const inet::Chunk>& chunk) const
{
    auto startPosition = stream.getLength();
    const auto& applicationPacket = inet::staticPtrCast<const ProfinetFrame>(chunk);
    stream.writeUint16Be(applicationPacket->getVlan());
    stream.writeUint16Be(applicationPacket->getEtherType());
    stream.writeUint16Be(applicationPacket->getFrameId());
    for(size_t i = 0; i<applicationPacket->getDataArraySize(); i++)
    {
        stream.writeUint8(applicationPacket->getData(i));

    }
    stream.writeUint16Be(applicationPacket->getCycleCounter());
    stream.writeUint16Be(applicationPacket->getDataStatus());
}

const inet::Ptr<inet::Chunk> ProfinetPacketSerializer::deserialize(inet::MemoryInputStream& stream) const
{
    auto startPosition = stream.getPosition();
    auto applicationPacket = inet::makeShared<ProfinetFrame>();
    applicationPacket->setVlan(stream.readUint16Be());
    applicationPacket->setEtherType(stream.readUint16Be());
    applicationPacket->setFrameId(stream.readUint16Be());
    for (size_t i = 0; i < applicationPacket->getDataArraySize(); i++)
    {
        applicationPacket->setData(i, stream.readUint8());
    }
    applicationPacket->setCycleCounter(stream.readUint16Be());
    applicationPacket->setDataStatus(stream.readUint16Be());
    return applicationPacket;
}

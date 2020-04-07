//
// Generated file, do not edit! Created by nedtool 5.6 from ProfinetFrame.msg.
//

#ifndef __PROFINETFRAME_M_H
#define __PROFINETFRAME_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif

// dll export symbol
#ifndef INET_API
#  if defined(INET_EXPORT)
#    define INET_API  OPP_DLLEXPORT
#  elif defined(INET_IMPORT)
#    define INET_API  OPP_DLLIMPORT
#  else
#    define INET_API
#  endif
#endif



class ProfinetFrame;
#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

#include "inet/networklayer/contract/ipv4/Ipv4Address_m.h" // import inet.networklayer.contract.ipv4.Ipv4Address

/**
 * Class generated from <tt>ProfinetFrame.msg:24</tt> by nedtool.
 * <pre>
 * class ProfinetFrame extends inet::FieldsChunk
 * {
 *     uint16_t Vlan;
 *     uint16_t EtherType;
 *     uint16_t FrameId;
 *     uint8_t Data[40];
 *     uint16_t CycleCounter;
 *     uint16_t DataStatus;
 * }
 * </pre>
 */
class INET_API ProfinetFrame : public ::inet::FieldsChunk
{
  protected:
    uint16_t Vlan = 0;
    uint16_t EtherType = 0;
    uint16_t FrameId = 0;
    uint8_t Data[40] = {0};
    uint16_t CycleCounter = 0;
    uint16_t DataStatus = 0;

  private:
    void copy(const ProfinetFrame& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const ProfinetFrame&);

  public:
    ProfinetFrame();
    ProfinetFrame(const ProfinetFrame& other);
    virtual ~ProfinetFrame();
    ProfinetFrame& operator=(const ProfinetFrame& other);
    virtual ProfinetFrame *dup() const override {return new ProfinetFrame(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual uint16_t getVlan() const;
    virtual void setVlan(uint16_t Vlan);
    virtual uint16_t getEtherType() const;
    virtual void setEtherType(uint16_t EtherType);
    virtual uint16_t getFrameId() const;
    virtual void setFrameId(uint16_t FrameId);
    virtual size_t getDataArraySize() const;
    virtual uint8_t getData(size_t k) const;
    virtual void setData(size_t k, uint8_t Data);
    virtual uint16_t getCycleCounter() const;
    virtual void setCycleCounter(uint16_t CycleCounter);
    virtual uint16_t getDataStatus() const;
    virtual void setDataStatus(uint16_t DataStatus);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const ProfinetFrame& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, ProfinetFrame& obj) {obj.parsimUnpack(b);}

#endif // ifndef __PROFINETFRAME_M_H


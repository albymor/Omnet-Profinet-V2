//
// Generated file, do not edit! Created by nedtool 5.6 from Profinet.msg.
//

#ifndef __PROFINET_M_H
#define __PROFINET_M_H

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



class Profinet;
#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

/**
 * Class generated from <tt>Profinet.msg:23</tt> by nedtool.
 * <pre>
 * class Profinet
 * {
 *     int someField;
 *     string anotherField;
 *     double arrayField2[10];
 * }
 * </pre>
 */
class INET_API Profinet
{
  protected:
    int someField = 0;
    omnetpp::opp_string anotherField;
    double arrayField2[10] = {0};

  private:
    void copy(const Profinet& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Profinet&);

  public:
    Profinet();
    Profinet(const Profinet& other);
    virtual ~Profinet();
    Profinet& operator=(const Profinet& other);
    virtual void parsimPack(omnetpp::cCommBuffer *b) const;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b);

    // field getter/setter methods
    virtual int getSomeField() const;
    virtual void setSomeField(int someField);
    virtual const char * getAnotherField() const;
    virtual void setAnotherField(const char * anotherField);
    virtual size_t getArrayField2ArraySize() const;
    virtual double getArrayField2(size_t k) const;
    virtual void setArrayField2(size_t k, double arrayField2);
};

#endif // ifndef __PROFINET_M_H


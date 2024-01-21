//
// Generated file, do not edit! Created by opp_msgtool 6.0 from tcp/TCPSegment.msg.
//

#ifndef __TCPSEGMENT_M_H
#define __TCPSEGMENT_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0600
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

class TCPSegment;
/**
 * Class generated from <tt>tcp/TCPSegment.msg:2</tt> by opp_msgtool.
 * <pre>
 * packet TCPSegment
 * {
 *     unsigned short srcPort = 0;
 *     unsigned short destPort = 0;
 *     unsigned int seqNr = 0;
 *     unsigned int ackNr = 0;
 * 
 *     bool cwr = false;
 *     bool ece = false;
 *     bool urg = false;
 *     bool ack = false;
 *     bool psh = false;
 *     bool rst = false;
 *     bool syn = false;
 *     bool fin = false;
 * 
 *     char dataOffset = 0;
 *     unsigned short dataWindow = 0;
 * }
 * </pre>
 */
class TCPSegment : public ::omnetpp::cPacket
{
  protected:
    unsigned short srcPort = 0;
    unsigned short destPort = 0;
    unsigned int seqNr = 0;
    unsigned int ackNr = 0;
    bool cwr = false;
    bool ece = false;
    bool urg = false;
    bool ack = false;
    bool psh = false;
    bool rst = false;
    bool syn = false;
    bool fin = false;
    char dataOffset = 0;
    unsigned short dataWindow = 0;

  private:
    void copy(const TCPSegment& other);

  protected:
    bool operator==(const TCPSegment&) = delete;

  public:
    TCPSegment(const char *name=nullptr, short kind=0);
    TCPSegment(const TCPSegment& other);
    virtual ~TCPSegment();
    TCPSegment& operator=(const TCPSegment& other);
    virtual TCPSegment *dup() const override {return new TCPSegment(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual unsigned short getSrcPort() const;
    virtual void setSrcPort(unsigned short srcPort);

    virtual unsigned short getDestPort() const;
    virtual void setDestPort(unsigned short destPort);

    virtual unsigned int getSeqNr() const;
    virtual void setSeqNr(unsigned int seqNr);

    virtual unsigned int getAckNr() const;
    virtual void setAckNr(unsigned int ackNr);

    virtual bool getCwr() const;
    virtual void setCwr(bool cwr);

    virtual bool getEce() const;
    virtual void setEce(bool ece);

    virtual bool getUrg() const;
    virtual void setUrg(bool urg);

    virtual bool getAck() const;
    virtual void setAck(bool ack);

    virtual bool getPsh() const;
    virtual void setPsh(bool psh);

    virtual bool getRst() const;
    virtual void setRst(bool rst);

    virtual bool getSyn() const;
    virtual void setSyn(bool syn);

    virtual bool getFin() const;
    virtual void setFin(bool fin);

    virtual char getDataOffset() const;
    virtual void setDataOffset(char dataOffset);

    virtual unsigned short getDataWindow() const;
    virtual void setDataWindow(unsigned short dataWindow);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TCPSegment& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TCPSegment& obj) {obj.parsimUnpack(b);}


namespace omnetpp {

template<> inline TCPSegment *fromAnyPtr(any_ptr ptr) { return check_and_cast<TCPSegment*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __TCPSEGMENT_M_H

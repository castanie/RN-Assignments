#ifndef TCP_H_
#define TCP_H_

#include <omnetpp.h>
#include "TCPSegment_m.h"
#include "TCPControlInfo_m.h"

class TCP : public cSimpleModule
{
private:
    unsigned int state;
    unsigned int seqNr;
    unsigned int ackNr;
    std::queue<TCPSegment *> *segmentQueue;
    cMessage *timeoutEvent;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void handleControlInfo(cPacket *msg);
    virtual void handleAppMessage(cPacket *msg);
    virtual void handleTCPSegment(cPacket *msg);

    virtual void handleAck(TCPSegment *msg);
    virtual void handleListen(TCPSegment *segment);
    virtual void handleSynSent(TCPSegment *segment);
    virtual void handleSynReceived(TCPSegment *segment);
    virtual void handleEstablished(TCPSegment *segment);
    virtual void handleFinWait1(TCPSegment *segment);
    virtual void handleFinWait2(TCPSegment *segment);
    virtual void handleCloseWait(TCPSegment *segment);
    virtual void handleClosing(TCPSegment *segment);
    virtual void handleLastAck(TCPSegment *segment);
    virtual void handleTimeWait(TCPSegment *segment);

    virtual void sendSyn();
    virtual void sendSynAck();
    virtual void sendAck();
    virtual void sendFin();
    virtual void signalStatus();
    virtual void encapsulateData(cPacket *msg);
    virtual void decapsulateData(cPacket *msg);
};

#endif

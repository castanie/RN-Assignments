#include <stdio.h>
#include <queue>

#include "../3rdParty/IPv4Address.h"
#include "../3rdParty/IPv6Address.h"
#include "../app/HTTPClient.h"
#include "../app/HTTPServer.h"
#include "TCP.h"

Define_Module(TCP);

// ------------------------------------------------------ //

enum Event
{
    OPEN,
    SEND,
    RECEIVE,
    CLOSE,
    ABORT,
    STATUS,
};

enum State
{
    LISTEN,
    SYN_SENT,
    SYN_RECEIVED,
    ESTABLISHED,
    FIN_WAIT_1,
    FIN_WAIT_2,
    CLOSE_WAIT,
    CLOSING,
    LAST_ACK,
    TIME_WAIT,
    CLOSED,
};

void TCP::initialize()
{
    state = par("initialState").intValue();
    seqNr = std::rand();
    ackNr = 0;
    segmentQueue = new std::queue<TCPSegment *>();
    timeoutEvent = new cMessage();
}

// ------------------------------------------------------ //

void TCP::handleMessage(cMessage *msg)
{
    EV << msg << endl;
    EV << this->getName() << ": " << this->state << endl;
    if (msg->isSelfMessage())
    {
        EV << this->getName() << ": isSelfMessage" << endl;
        if (this->segmentQueue->front())
        {
            send(this->segmentQueue->front()->dup(), "toLowerLayer");
        }
        scheduleAt(simTime() + par("retransTimeout").doubleValue(), this->timeoutEvent);
    }
    else if (msg->arrivedOn("fromUpperLayer"))
    {
        EV << this->getName() << ": fromUpperLayer" << endl;
        if (!strcmp(msg->getClassName(), "TCPControlInfo"))
        {
            this->handleControlInfo((cPacket *)msg);
        }
        else
        {
            this->handleAppMessage((cPacket *)msg);
        }
    }
    else if (msg->arrivedOn("fromLowerLayer"))
    {
        EV << this->getName() << ": fromLowerLayer" << endl;
        if (uniform(0, 1) < par("packetLossProb").doubleValue())
        {
            return;
        }
        this->handleTCPSegment((cPacket *)msg);
    }
}

void TCP::handleControlInfo(cPacket *msg)
{
    switch (((TCPControlInfo *)msg)->getTcpCommand())
    {
    case OPEN:
        this->sendSyn();
        this->state = SYN_SENT;

        scheduleAt(simTime() + par("retransTimeout").doubleValue(), this->timeoutEvent);
        break;
    case CLOSE:
        this->sendFin();
        this->state = FIN_WAIT_1;
        break;
    default:
        break;
    }
}

void TCP::handleAppMessage(cPacket *msg)
{
    switch (state)
    {
    case LISTEN:
        break;
    case SYN_SENT:
        break;
    case SYN_RECEIVED:
        break;
    case ESTABLISHED:
        encapsulateData(msg);
        break;
    case FIN_WAIT_1:
        break;
    case FIN_WAIT_2:
        break;
    case CLOSE_WAIT:
        break;
    case CLOSING:
        break;
    case LAST_ACK:
        break;
    case TIME_WAIT:
        break;
    default:
        break;
    }
}

void TCP::handleTCPSegment(cPacket *msg)
{
    EV << this->getName() << ": " << this->state << endl;
    TCPSegment *segment = (TCPSegment *)msg;

    switch (this->state)
    {
    case LISTEN:
        handleListen(segment);
        break;
    case SYN_SENT:
        handleSynSent(segment);
        break;
    case SYN_RECEIVED:
        handleSynReceived(segment);
        break;
    case ESTABLISHED:
        handleEstablished(segment);
        break;
    case FIN_WAIT_1:
        handleFinWait1(segment);
        break;
    case FIN_WAIT_2:
        handleFinWait2(segment);
        break;
    case CLOSE_WAIT:
        // handleCloseWait();
        break;
    case CLOSING:
        // handleClosing();
        break;
    case LAST_ACK:
        handleLastAck(segment);
        break;
    case TIME_WAIT:
        // handleTimeWait();
        break;
    default:
        break;
    }
}

// ------------------------------------------------------ //

void TCP::sendSyn()
{
    TCPSegment *synSegment = new TCPSegment();
    synSegment->setSeqNr(seqNr);
    synSegment->setAckNr(ackNr);
    synSegment->setSyn(true);
    send(synSegment->dup(), "toLowerLayer");
    this->segmentQueue->push(synSegment);
}

void TCP::sendSynAck()
{
    TCPSegment *synAckSegment = new TCPSegment();
    synAckSegment->setSeqNr(seqNr);
    synAckSegment->setAckNr(ackNr);
    synAckSegment->setSyn(true);
    synAckSegment->setAck(true);
    send(synAckSegment->dup(), "toLowerLayer");
    this->segmentQueue->push(synAckSegment);
}

void TCP::sendAck()
{
    TCPSegment *ackSegment = new TCPSegment();
    ackSegment->setSeqNr(seqNr);
    ackSegment->setAckNr(ackNr);
    ackSegment->setAck(true);
    send(ackSegment->dup(), "toLowerLayer");
    this->segmentQueue->push(ackSegment);
}

void TCP::sendFin()
{
    TCPSegment *finSegment = new TCPSegment();
    finSegment->setSeqNr(seqNr);
    finSegment->setAckNr(ackNr);
    finSegment->setFin(true);
    send(finSegment->dup(), "toLowerLayer");
    this->segmentQueue->push(finSegment);
}

void TCP::signalStatus()
{
    TCPControlInfo *controlInfo = new TCPControlInfo();
    controlInfo->setTcpStatus(OPEN);
    send(controlInfo, "toUpperLayer");
}

void TCP::encapsulateData(cPacket *msg)
{
    TCPSegment *dataSegment = new TCPSegment();
    dataSegment->setSeqNr(seqNr);
    dataSegment->setAckNr(ackNr);
    dataSegment->encapsulate(msg);
    send(dataSegment->dup(), "toLowerLayer");
    this->segmentQueue->push(dataSegment);
}

void TCP::decapsulateData(cPacket *msg)
{
    send(msg->decapsulate(), "toUpperLayer");
}

// ------------------------------------------------------ //

void TCP::handleAck(TCPSegment *segment)
{
    this->ackNr = segment->getSeqNr() + 1;
    EV << this->getName() << ".seqNr: " << this->seqNr << endl;
    EV << this->getName() << ".ackNr: " << this->ackNr << endl;
    EV << this->segmentQueue->front() << endl;
    return;
    while (this->segmentQueue->front()->getAckNr() < this->ackNr)
    {
        this->segmentQueue->pop();
    }
    rescheduleAt(simTime() + par("retransTimeout").doubleValue(), this->timeoutEvent);
}

void TCP::handleListen(TCPSegment *segment)
{
    if (segment->getSyn())
    {
        this->ackNr = segment->getSeqNr() + 1;
        this->sendSynAck();
        this->state = SYN_RECEIVED;
    }
}

void TCP::handleSynSent(TCPSegment *segment)
{
    if (segment->getSyn() && segment->getAck())
    {
        this->handleAck(segment);
        this->sendAck();
        this->state = ESTABLISHED;

        signalStatus();
    }
}

void TCP::handleSynReceived(TCPSegment *segment)
{
    if (segment->getAck())
    {
        this->handleAck(segment);
        this->state = ESTABLISHED;

        // signalStatus();
    }
}

void TCP::handleEstablished(TCPSegment *segment)
{
    if (segment->getFin())
    {
        this->state = CLOSE_WAIT;
        this->sendAck();
    }

    this->decapsulateData(segment);
    this->sendAck();
}

void TCP::handleFinWait1(TCPSegment *segment)
{
    if (segment->getFin() && segment->getAck())
    {
        this->state = TIME_WAIT;
    }
    else if (segment->getFin())
    {
        this->state = CLOSING;
    }
    else if (segment->getAck())
    {
        this->state = FIN_WAIT_2;
    }
}

void TCP::handleFinWait2(TCPSegment *segment)
{
    if (segment->getFin())
    {
        this->sendAck();
        this->state = TIME_WAIT;
    }
}

void TCP::handleCloseWait(TCPSegment *segment) {}

void TCP::handleClosing(TCPSegment *segment) {}

void TCP::handleLastAck(TCPSegment *segment)
{
    if (segment->getAck())
    {
        this->state = CLOSED;
    }
}

void TCP::handleTimeWait(TCPSegment *segment) {}

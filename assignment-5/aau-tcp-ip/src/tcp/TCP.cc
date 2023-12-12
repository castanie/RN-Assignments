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
// (c) 2019 Christian Timmerer, Alpen-Adria-Universität Klagenfurt / Bitmovin Inc.
//          christian.timmerer@itec.aau.at / christian.timmerer@bitmovin.com
//
// 621.800 (19W) Computer Networks and Network Programming

#include <stdio.h>
#include <queue>
#include "../3rdParty/IPv4Address.h"
#include "../3rdParty/IPv6Address.h"
#include "TCP.h"

Define_Module(TCP);

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

parameters : State current_state = LISTEN;

int seqn;
int ackn;
std::queue<cMessage *> *message_queue;

void TCP::initialize()
{
    seqn = std::rand();
    ackn = -1;
    message_queue = new std::queue<cMessage *>();
}

void TCP::handleMessage(cMessage *msg)
{
    // TODO Handle timeouts.
    // TODO Simulate packet loss.

    if (msg->arrivedOn("fromUpperLayer"))
    {
        // Comes from higher layer.
        this->handleAppMessage((cPacket *)msg);
    }

    else if (msg->arrivedOn("fromLowerLayer"))
    {
        // Comes from lower layer.
        // Packet loss:
        if (uniform(0, 1) < par("packetLossProb"))
        {
            return;
        }
        this->handleTCPSegment((cPacket *)msg);
    }
}

void TCP::handleAppMessage(cPacket *msg)
{
    TCPSegment *message = (TCPSegment *)msg;
    if (message)
    {
        message_queue->push(message);
    }

    // TCP control:
    // Determine event.
    // tcpCommand = 0 -> return;
    // tcpCommand = 1 -> current_state = LISTEN;
    // tcpCommand = 2 -> current_state = CLOSED;
    // Determine source and destination.
    // return;

    TCPSegment *syn_segment = new TCPSegment();

    switch (current_state)
    {
    case CLOSED:
        break;
    case LISTEN:
        syn_segment->setSeqNr(seqn);
        syn_segment->setAckNr(ackn);
        syn_segment->setSyn(true);
        send(syn_segment->dup(), "toLowerLayer");
        scheduleAt(simTime() + 1.0, message);
        current_state = SYN_SENT;
        break;
    case SYN_SENT:
        // Queue, no connection yet (waiting for server-side ACK).
        break;
    case SYN_RECEIVED:
        // Queue, no connection yet (waiting for client-side ACK).
        break;
    case ESTABLISHED:
        // Pack data and relay "toLowerLayer".
        // Skip for now:
        send(message_queue->front()->dup(), "toLowerLayer");
        scheduleAt(simTime() + 1.0, message);
        break;
    default:
        break;
    }

    // Clean up:
    delete message;
}

void TCP::handleTCPSegment(cPacket *msg)
{
    TCPSegment *segment = (TCPSegment *)msg;

    // TCP segment:
    // ...

    TCPSegment *synack_segment = new TCPSegment();
    TCPSegment *ack_segment = new TCPSegment();

    switch (current_state)
    {
    case CLOSED:
        break;
    case LISTEN:
        synack_segment->setSeqNr(seqn);
        synack_segment->setAckNr(ackn);
        synack_segment->setSyn(true);
        synack_segment->setAck(true);
        send(synack_segment->dup(), "toLowerLayer");
        scheduleAt(simTime() + 1.0, segment);
        current_state = SYN_SENT;
        break;
    case SYN_SENT:
        // Check if server-side SYN-ACK, or at least ACK.
        if (segment->getSyn() && segment->getAck()) // && (segment->getAckNr() == )
        {
            cancelEvent(synack_segment);
            ack_segment->setSeqNr(seqn);
            ack_segment->setAckNr(ackn);
            ack_segment->setAck(true);
            send(ack_segment, "toLowerLayer");
            scheduleAt(simTime() + 1.0, segment);
            current_state = ESTABLISHED;
        }
        break;
    case SYN_RECEIVED:
        // Check if client-side ACK.
        break;
    case ESTABLISHED:
        // Unpack data and relay "toUpperLayer".
        // Skip for now:
        send(segment->dup(), "toUpperLayer");
        scheduleAt(simTime() + 1.0, segment);
        break;
    default:
        break;
    }

    // Clean up:
    delete segment;
}

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

#include "TCP.h"
#include <stdio.h>
#include "../3rdParty/IPv4Address.h"
#include "../3rdParty/IPv6Address.h"

Define_Module(TCP);

private:
int seqn;
int ackn;

void TCP::initialize()
{
    // TODO Initialize seqn and ackn.
    seqn = std::rand();
    ackn = -1;
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
        this->handleTCPSegment((cPacket *)msg);
    }
}

void TCP::handleAppMessage(cPacket *msg)
{
    TCPSegment *segment;

    // Establish connection:

    //// Send SYN
    *segment = new TCPSegment();
    segment->setSeqNr();
    segment->setSyn(true);
    send(segment, "toLowerLayer");
    //// Receive SYN-ACK
    while (true)
    {
        *segment = receive();
        if (segment->getSyn() && segment->getAck())
        {
            break;
        }
    }
    //// Send ACK
    *segment = new TCPSegment();
    segment->setAck(true);
    send(segment, "toLowerLayer");

    // Send data:

    //// Split into data segments with max. 1,500 bytes
    int maxSegmentSize = 1500;
    int segmentCount = ceil((double)msg->getByteLength() / maxSegmentSize);

    for (int i = 0; i < segmentCount; i++)
    {
        int segmentSize = (i < segmentCount - 1) ? maxSegmentSize : msg->getByteLength() % maxSegmentSize;

        segment->setByteLength(segmentSize);

        send(segment, "toLowerLayer");

        //// Set timeout
        cMessage *timeoutNotification = new cMessage("timeout");
        scheduleAt(simTime() + timeoutDuration, timeoutNotification);
    }

    // Terminate connection:

    *segment = new TCPSegment();
    segment->setFin(true);
    send(segment, "toLowerLayer");
}

void TCP::handleTCPSegment(cPacket *msg)
{
    // TODO handle input from lower layer
}

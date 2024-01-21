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
// (c) 2018 Christian Timmerer, Alpen-Adria-Universität Klagenfurt / Bitmovin Inc.
//          christian.timmerer@itec.aau.at / christian.timmerer@bitmovin.com
//
// 621.800 (18W) Computer Networks and Network Programming

#include <stdio.h>
#include <queue>

#include "Aloha.h"

Define_Module(Aloha);

// ------------------------------------------------------ //

// Maximum Transmission Unit?

void Aloha::initialize()
{
    this->frameQueue = new std::queue<cMessage *>();
    this->timeoutEvent = new cMessage();
    this->backoffFactor = 0;
}

// ------------------------------------------------------ //

void Aloha::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        EV << "isSelfMessage" << endl;
        if (!this->frameQueue->empty())
        {
            send(this->frameQueue->front()->dup(), "outLowerLayer");
        }
    }
    else if (msg->arrivedOn("inUpperLayer"))
    {
        this->handleUpperLayer(msg);
    }
    else if (msg->arrivedOn("inLowerLayer"))
    {
        this->handleLowerLayer(msg);
    }
}

void Aloha::handleUpperLayer(cMessage *msg)
{
    EV << "inUpperLayer" << endl;
    IPDatagram *ipDatagram = (IPDatagram *)msg;
    this->encapsulateData(msg);
}

void Aloha::handleLowerLayer(cMessage *msg)
{
    EV << "inLowerLayer" << endl;
    if (strcmp(msg->getName(), "COL") == 0)
    {
        EV << "Collision signalled!" << endl;
        if (!this->frameQueue->empty())
        {
            EV << "Scheduled retransmisison at simTime() + " << ((std::rand() % 8) * par("slotDelay").doubleValue()) << "!" << endl;
            scheduleAt(simTime() + ((std::rand() % 8) * par("slotDelay").doubleValue()), this->timeoutEvent);
        }
    }
    else if (strcmp(msg->getClassName(), "AlohaFrame") == 0)
    {
        AlohaFrame *alohaFrame = (AlohaFrame *)msg;
        EV << getParentModule()->par("macAddress").stringValue() << endl;
        EV << alohaFrame->getDest().str() << endl;

        inet::MACAddress *macAddress = new inet::MACAddress(getParentModule()->par("macAddress").stringValue());

        EV << (alohaFrame->getDest().compareTo(*macAddress) == 0) << endl;

        if (alohaFrame->getDest().compareTo(*macAddress) == 0)
        {
            // This message is directed at us.
            this->decapsulateData(msg);
        }
        else if (alohaFrame->getSrc().compareTo(*macAddress) == 0)
        {
            // If the link returns our message,
            // it has been relayed successfully.
            // We can remove it from the queue:
            this->frameQueue->pop();
        }
    }
}

// ------------------------------------------------------ //

void Aloha::encapsulateData(cMessage *msg)
{
    AlohaControlInfo *alohaControlInfo = (AlohaControlInfo *)((IPDatagram *)msg)->getControlInfo();
    AlohaFrame *alohaFrame = new AlohaFrame();
    alohaFrame->setSrc(alohaControlInfo->getSrc());
    alohaFrame->setDest(alohaControlInfo->getDest());
    alohaFrame->encapsulate((cPacket *)msg);
    send(alohaFrame->dup(), "outLowerLayer");
    this->frameQueue->push(alohaFrame);
}

void Aloha::decapsulateData(cMessage *msg)
{
    send(((cPacket *)msg)->decapsulate(), "outUpperLayer");
}

// ------------------------------------------------------ //

void Aloha::sendCopyOf(cMessage *msg, double delay)
{
    cMessage *copy = (cMessage *)msg->dup();
    sendDelayed(copy, simTime() + delay, "outLowerLayer");
}

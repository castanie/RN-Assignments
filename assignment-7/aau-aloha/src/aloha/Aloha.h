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

#ifndef ALOHA_H_
#define ALOHA_H_

#include <omnetpp.h>

#include "../3rdParty/IPv4Address.h"
#include "../3rdParty/MACAddress.h"

#include "../messages/AlohaControlInfo_m.h"
#include "../messages/AlohaFrame_m.h"
#include "../messages/IPDatagram_m.h"

using namespace std;

class Aloha : public cSimpleModule
{

private:
    std::queue<cMessage *> *frameQueue;
    cMessage *timeoutEvent;
    int backoffFactor;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void handleUpperLayer(cMessage *msg);
    virtual void handleLowerLayer(cMessage *msg);
    virtual void encapsulateData(cMessage *msg);
    virtual void decapsulateData(cMessage *msg);
    virtual void sendCopyOf(cMessage *msg, double delay);
};

#endif /* ALOHA_H_ */

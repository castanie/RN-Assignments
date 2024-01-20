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

#include "Aloha.h"

Define_Module(Aloha);

void Aloha::initialize() {

}

void Aloha::handleMessage(cMessage *msg) {
    // TODO: implement ALOHA
}

void Aloha::sendCopyOf(cMessage *msg, double delay) {
    // Duplicate message and send the copy.
    cMessage *copy = (cMessage *) msg->dup();
    sendDelayed(copy, simTime() + delay, "outLowerLayer");
}

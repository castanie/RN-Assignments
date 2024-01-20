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

#include "HTTPClient.h"
#include "HTTPClientMsg_m.h"
#include "HTTPServerMsg_m.h"
#include "../tcp/TCPControlInfo_m.h"
#include "../tcp/TCPSegment_m.h"

Define_Module(HTTPClient);

void HTTPClient::initialize()
{
    // Open connection:
    TCPControlInfo *controlInfo = new TCPControlInfo();
    controlInfo->setTcpCommand(0);
    send(controlInfo, "toLowerLayer");
}

void HTTPClient::handleMessage(cMessage *msg)
{
    if (!strcmp(msg->getClassName(), "TCPControlInfo"))
    {
        // Create requests:
        std::string arr[] = {
            "GET /demo/\r\n",
            "GET /demo/logo.gif\r\n",
            "GET /demo/TechnikErleben.png\r\n",
        };

        // Send requests:
        for (const auto &request : arr)
        {
            HTTPClientMsg *clientMsg = new HTTPClientMsg();
            clientMsg->setResource(request.c_str());
            send(clientMsg, "toLowerLayer");
        }

        // Close connection:
        TCPControlInfo *controlInfo = new TCPControlInfo();
        controlInfo->setTcpCommand(3);
        send(controlInfo, "toLowerLayer");
    }
    else
    {
        HTTPServerMsg *serverMsg = check_and_cast<HTTPServerMsg *>(msg);
        if (serverMsg)
        {
            std::string response = serverMsg->getResponse();
            EV << response << endl;
        }
    }
}

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

#include <unordered_map>

#include "HTTPServer.h"
#include "HTTPClientMsg_m.h"
#include "HTTPServerMsg_m.h"

Define_Module(HTTPServer);

void HTTPServer::initialize()
{
    // TODO implement initialize
}

void HTTPServer::handleMessage(cMessage *msg)
{
    // TODO implement handleMessage
    HTTPClientMsg *clientMsg = check_and_cast<HTTPClientMsg *>(msg);
    HTTPServerMsg *serverMsg = new HTTPServerMsg("500 Internal Server Error");

    std::unordered_map<std::string, std::string> responseDict =
        {
            {
                "GET /demo/\r\n",
                "<html>\n\n<head>\n    <title>Demo Web Site 2023</title>\n</head>\n\n<body>\n    <img src=\"logo.gif\" />\n    <h1>Welcome</h1> <img src=\"TechnikErleben.png\" />\n</body>\n\n</html>",
            },
            {
                "GET /demo/logo.gif\r\n",
                "logo.gif",
            },
            {
                "GET /demo/TechnikErleben.png\r\n",
                "TechnikErleben.png",
            },
        };

    if (clientMsg)
    {
        std::string request = clientMsg->getResource();
        std::string response;
        if (responseDict.find(request) != responseDict.end())
        {
            response = responseDict[request];
        }
        else
        {
            response = "404 Not Found";
        }
        serverMsg->setResponse(response.c_str());
    }

    send(serverMsg, "toLowerLayer");
    delete msg;
}

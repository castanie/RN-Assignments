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

package aau_http.simulations;

import aau_http.app.HTTPClient;
import aau_http.app.HTTPServer;
import ned.DelayChannel;

network HTTPNetwork
{
    parameters:
        // TODO add global parameters (if needed)
        @display("bgb=200,120");

    submodules:
        // TODO add submodules comprising a HTTPClient and HTTPServer
        httpClient: HTTPClient {
            @display("p=30,30");
        }
        httpServer: HTTPServer {
            @display("p=150,70");
        }

    connections:
        // TODO connect HTTPClient and HTTPServer
        httpClient.toLowerLayer --> DelayChannel {  delay = 0.1s; } --> httpServer.fromLowerLayer;
        httpServer.toLowerLayer --> DelayChannel {  delay = 0.1s; } --> httpClient.fromLowerLayer;
        
}

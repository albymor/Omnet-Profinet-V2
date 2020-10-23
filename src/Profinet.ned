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

package boh;
import inet.networklayer.base.NetworkProtocolBase;

module Profinet extends NetworkProtocolBase{
   
    parameters:
        @signal[packetSent](type=inet::Packet);
        string destAddress = default("");
        string srcAddress = default("");
        bool bootstrap = default(false);
        int sendTime = default(1000); //tempo inter-frame in us. DEVE ESSERE UN MULTIPLO DI 31.25us
        bool isMaster = default(false); // indica se il device � un master
        int sendClockFactor = default(32);
        int cycleCounter = default(0);
    
     @class(Profinet);
}


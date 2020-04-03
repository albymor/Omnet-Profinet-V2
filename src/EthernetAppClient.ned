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

import inet.applications.ethernet.EtherAppClient;


//
// A simple traffic generator for the Ethernet model and the 802.11 model,
// and generally for any L2 model that accepts ~Ieee802SapReq tags on the
// packets. It generates packets containing ~EtherAppReq chunks. It should
// be connected directly to ~EtherEncap/~Ieee8022Llc.
//
simple EthernetAppClient extends EtherAppClient
{
     @class(inet::EthernetAppClient);
         
}


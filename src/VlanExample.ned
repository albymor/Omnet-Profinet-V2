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


import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.ethernet.Eth100M;
import inet.node.ethernet.EtherSwitch;
import boh.EthernetHost;
import inet.node.inet.StandardHost;
import inet.applications.ethernet.EtherAppServer;
import inet.applications.ethernet.EtherAppClient;
import boh.ProfinetDevice;
import inet.node.inet.WirelessHost;
import inet.node.wireless.AccessPoint;
import inet.physicallayer.common.packetlevel.RadioMedium;


network VlanExample
{
    submodules:
        configurator: Ipv4NetworkConfigurator {
            @display("p=100,100;is=s");
        }
        profinetMaster: ProfinetDevice {
            @display("p=249,313");
        }
        profinetDevice2: ProfinetDevice {
            @display("p=500,331");
        }
        profinetDevice3: ProfinetDevice {
            @display("p=550,117");
        }
        profinetDevice4: ProfinetDevice {
            @display("p=550,274");
        }
    connections:
        profinetDevice2.ethg++ <--> Eth100M <--> profinetMaster.ethg++;
        profinetDevice3.ethg++ <--> Eth100M <--> profinetMaster.ethg++;
        profinetDevice2.ethg++ <--> Eth100M <--> profinetDevice4.ethg++;
}

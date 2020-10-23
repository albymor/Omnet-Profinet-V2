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
import inet.node.ethernet.Eth400G;
import inet.node.ethernet.EtherSwitch;
import boh.EthernetHost;
import inet.node.inet.StandardHost;
import inet.applications.ethernet.EtherAppServer;
import inet.applications.ethernet.EtherAppClient;
import inet.node.ethernet.EtherHost;

network VlanExample
{
    @display("bgb=614,338");
    submodules:
        configurator: Ipv4NetworkConfigurator {
            @display("p=100,100;is=s");
        }
        //host1: StandardHost {
        //   @display("p=250,100");
        //}
        switch1: EtherSwitch {
            @display("p=400,68");
        }
        //switch2: EtherSwitch {
        //    @display("p=450,100");
        //}
        //host2: MyStandardHost {
        //    @display("p=550,100");
        //}
        host1: EthernetHost {
            @display("p=481,69");
        }
        host2: EthernetHost {
            @display("p=469,231");
        }
        Controller_Host: EthernetHost {
            @display("p=92,172");
        }
        switch2: EtherSwitch {
            @display("p=400,230");
        }
        Controller_Switch: EtherSwitch {
            @display("p=210,171");
        }
    connections:
        //host1.ethg++ <--> Eth100M <--> switch1.ethg++;
        host1.ethg <--> Eth400G {  length = 1.2m; } <--> switch1.ethg++;
        host2.ethg <--> Eth400G {  length = 1.2m; } <--> switch2.ethg++;
        Controller_Host.ethg <--> Eth400G {  length = 1.2m; } <--> Controller_Switch.ethg++;

        switch2.ethg++ <--> Eth100M {  length = 3m; } <--> switch1.ethg++;
        switch2.ethg++ <--> Eth100M {  length = 3m; } <--> Controller_Switch.ethg++;
}

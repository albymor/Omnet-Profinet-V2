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


import inet.node.ethernet.Eth100M;
import inet.node.ethernet.EtherSwitch;
import boh.EthernetHost;
import inet.node.inet.StandardHost;
import inet.applications.ethernet.EtherAppServer;
import inet.applications.ethernet.EtherAppClient;
import inet.common.MessageDispatcher;
import inet.common.lifecycle.NodeStatus;
import inet.common.packet.recorder.PcapRecorder;
import inet.linklayer.configurator.L2NodeConfigurator;
import inet.linklayer.contract.IEthernetInterface;
import inet.linklayer.contract.IExternalInterface;
import inet.linklayer.contract.IMacAddressTable;
import inet.linklayer.contract.IMacRelayUnit;
import inet.linklayer.contract.ISpanningTree;
import inet.linklayer.ethernet.IEtherEncap;
import inet.networklayer.common.InterfaceTable;

module ProfinetDevice{
    parameters:
        @networkNode();
        @labels(node,ethernet-node);
        @display("i=device/pc2");
        int numEthInterfaces = default(0);  // minimum number of ethernet interfaces
    gates:
        inout ethg[numEthInterfaces] @labels(EtherFrame-conn);
    submodules:
        switch: EtherSwitch {
            @display("p=350,100");
        }
        host: EthernetHost {
            @display("p=289,231");
        }    
    connections:
        host.ethg <--> Eth100M <--> switch.ethg++;
        
        for i=0..sizeof(ethg)-1 {
            ethg[i] <--> switch.ethg++;
        }    
}
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

network Network
{
    @display("bgb=592,327");
    submodules:
        pc1: Client {
            @display("p=95,64");
        }
        pc3: Client {
            @display("p=95,245");
        }
        pc2: Client {
            @display("p=412,64");
        }
        pc4: Client {
            @display("p=412,245");
        }
        server: Server {
            @display("p=271,151");
        }
        connections:
            server.out1-->pc1.in;
            server.out2-->pc2.in;
            server.out3-->pc3.in;
            server.out4-->pc4.in;
            pc1.out-->server.in1;
            pc2.out-->server.in2;
            pc3.out-->server.in3;
            pc4.out-->server.in4;
}

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

#include "client.h"
#include <string>
using namespace std;
Define_Module(Client);

void Client::initialize()
{

    //Pc1 sending encrypted message to server using ceasor cipher
    if(strcmp(getName(),"pc1")==0)
    {
        cMessage *msg=new cMessage("hello");
        string plaintext=msg->getFullName();
                int  key=2;
                int size=plaintext.size();
                char encrypt[size];
                for(int i=0;i<size;i++)
                {
                    char ch = ((plaintext[i]-'a'+2)%26)+'a';
                    encrypt[i] = ch;
                }
                cMessage *msgs= new cMessage(encrypt);
                        send(msgs,"out");
            }
    //Pc3 sending encrypted message by autokey
    if(strcmp(getName(),"pc3")==0)
    {
        cMessage *msg=new cMessage("attackatdawn");
                std::string plaintext=msg->getFullName();
                int message_size=plaintext.size();
                 std::string key="jazz";
                 int key_size=key.size();
                 int total_keySize=message_size-key_size;
                 std::string new_key = key + plaintext.substr(0,total_keySize);
                 char encrypt[message_size+1];
                 for(int i=0; i<message_size;i++)
                 {
                     char ch=(((plaintext[i]-'a')+(new_key[i]-'a'))%26)+'a';
                     encrypt[i]=ch;
                 }
                 encrypt[message_size] = '\0';
                 cMessage *newmsgs=new cMessage(encrypt);
                  send(newmsgs,"out");
    }
}

void Client::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(strcmp(getName(),"pc2")==0)
    {
        std::string ciphertext=msg->getFullName();
                int key=2;
                int size=ciphertext.size();
                char decrypt[size];
                for(int i=0;i<size;i++)
                {
                    char ch = ((ciphertext[i]-'a'-2)%26)+'a';
                    decrypt[i] = ch;
                }
                cMessage *msgs= new cMessage(decrypt);
                        send(msgs,"out");
    }
    if(strcmp(getName(),"pc4")==0)
    {
        std::string ciphertext=msg->getFullName();
                    int message_size=ciphertext.size();
                    std::string key="jazz";
                    int key_size=key.size();
                    char ch;

                    char decrypt[message_size];
                    for(int i=0; i<(message_size);i++)
                    {
                        if(i<key_size)
                        {
                            int val=((ciphertext[i]-'a')-(key[i]-'a'));
                            val = (val < 0) ? val + 26 : val;
                            ch=(val%26)+'a';
                        }
                        else {
                            int val=((ciphertext[i]-'a')-(decrypt[i-key_size]-'a'));
                            val = (val < 0) ? val + 26 : val;
                            ch=(val%26)+'a';
                        }
                        decrypt[i]=ch;
                    }
                    decrypt[message_size]='\0'; // add null terminator
                    cMessage *newmsgs=new cMessage( decrypt);
                    send(newmsgs,"out");
    }
}

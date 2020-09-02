/*This code is for Stage 0 of SRA task : DATA RELAY
Link to the task : https://github.com/SRA-VJTI/practice-assignments
Library used : Paho Eclipse MQTT for C++
Code for JSON stream and Publishing is yet to be included 
The structure of this code is as follows:
There are 5 floors of a building with 10 edge boards on each floor
Each floor consists of 6 temperature_sensor_bots and 4 distance_sensor_bots
The following code is for the temperature bots only
Library github link : https://github.com/eclipse/paho.mqtt.cpp
*/

#include <random>
#include <string>
#include <thread>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <jsoncpp/json/json.h>
#include "mqtt/async_client.h"

using namespace std;
using namespace std::chrono;

const std::string DEFLT_ADDRESS {"tcp://localhost:1883"};

char* TEMP_TOPICS = []

const string TEMP_TOPICS[0] {"floor1/temp"}; //topic for temperature sensor data from 6 sensors on floor 1
const string TEMP_TOPICS[1] {"floor2/temp"};
const string TEMP_TOPICS[2] {"floor3/temp"};
const string TEMP_TOPICS[3] {"floor4/temp"};
const string TEMP_TOPICS[4] {"floor5/temp"};

const int QOS = 1; //PUB request will be met with a PUBACK request

const auto PERIOD = seconds(5); //time alloted for one message (std::chrono::seconds)

const int MAX_BUFFERED_MESSAGES = 20; //1 bots can send 10 messages at a time, 1 message each

//Time taken to deliver messages = PERIOD*MAX_BUFFERED_MESSAGES = 5*50 = 4 mins 10 secs

const int DELAY = seconds(0.5); //To establish frequency of 500ms for pushing messages

char* PERSIST_DIRS = [];

const string PERSIST_DIRS[0] {"floor1/persist"};
const string PERSIST_DIRS[1] {"floor2/persist"};
const string PERSIST_DIRS[2] {"floor3/persist"};
const string PERSIST_DIRS[3] {"floor4/persist"};
const string PERSIST_DIRS[4] {"floor5/persist"};

void client_define (int n, int pers_dir) {
    string client_name = "cli"+pers_dir;
    string connopts_name = "connopts"+pers_dir;
    string topic_names = "top"+pers_dir;
    int n;
    int pers_dir;
    char* top = [];
    char* connopts = [];
    mqtt::async_client client_name[i](address, clients[n], MAX_BUFFERED_MESSAGES, PERSIST_DIRS[pers_dir]);
    mqtt::topic top[n] = (cli[i], TEMP_TOPICS[pers_dir], QOS, true);
    
}

string random_message_generator(int n) {
    int tstp =123;
    std::random_device drand;
    std::mt19937 gen(drand());
    std::uniform_real_distribution<double> distemp(25,50);
    std::uniform_real_distribution<double> dishum(25,30);
    std::uniform_int_distribution<int> dispr(1,100);
    std::uniform_real_distribution<double> disph(1,14);
    Json::Value val;
    val = {
        "device_id" : n, "timestamp" : tstp, "temperature" : distemp(gen), "humidity" : dishum(gen), "air_pressure" : dispr(gen), "ph" : disph(gen)  
    };
    
    Json::StyledWriter styled;
    string msg = styled.write(val);
    return msg;


}

void temp_client_pub () {


    try
    {
        cout<<"Connecting to server ..' "<<address<<" '.."<<flush; //std::flush used to display logging activity of thread before completion
        for (int i=0; i<6; i++)
        {
            char* msg = []
            client_name[i].connect(connopts)->wait();
            cout<<"OK\n"<<endl; //another available option is <<flush;

            char timebuffer[32];
            
            auto freq = std::chrono::milliseconds(500); //timer set for 500ms

            while(true) {
                this_thread::sleep_until(freq); //data gets pushed every 500ms

                msg[i] = random_message_generator(i);
                string payload = msg[i];
                cout<<payload<<endl;
                top0[i].publish(std::move(payload));

                timebuffer+=PERIOD;


            }
            //Disconnect
            cout<<"\nDisconnecting.."<<flush;
            

        }

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

int main(int argc, char* argv[])
{
    string address = (argv>1) ? string(argv[1]) : DEFLT_ADDRESS;

    mqtt::connect_options connopts;
    connopts.set_keep_alive_interval(MAX_BUFFERED_MESSAGES * PERIOD); 
    connopts.set_clean_session(true);
    connopts.set_automatic_reconnect(true);

    for (int i = 0; i<6; i++)
    {
        char* cli = [];
        client_define(i,0);
        client_define(i,1);
        client_define(i,2);
        client_define(i,3);
        client_define(i,4);

        );

    }
    //All temp_bot_clients are now defined

    //initiating threads for publishing data

    for(int i=0; i<30; i++) //for 30 temp bots
    {
        char* th = [];
        std::thread th[i] (temp_client_pub) 
        th[i].join();
    }

}






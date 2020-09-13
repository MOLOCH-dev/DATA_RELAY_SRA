#include <random>
#include <string>
#include <thread>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
//#include <jsoncpp/json/json.h>
#include <MQTTAsync.h>

using namespace std;
using namespace std::chrono;

//mqtt::async_client client;


const std::string DEFLT_ADDRESS {"tcp://localhost:1883"};




const string TEMP_TOPICS0 {"floor1/temp"}; //topic for temperature sensor data from 6 sensors on floor 1
const string TEMP_TOPICS1 {"floor2/temp"};
const string TEMP_TOPICS2 {"floor3/temp"};
const string TEMP_TOPICS3 {"floor4/temp"};
const string TEMP_TOPICS4 {"floor5/temp"};

const int QOS = 1; //PUB request will be met with a PUBACK request

const auto PERIOD = seconds(5); //time alloted for one message (std::chrono::seconds)

const int MAX_BUFFERED_MESSAGES = 20; //1 bots can send 10 messages at a time, 1 message each

//Time taken to deliver messages = PERIOD*MAX_BUFFERED_MESSAGES = 5*50 = 4 mins 10 secs

const int DELAY = seconds(0.5); //To establish frequency of 500ms for pushing messages


const std::string PERSIST_DIRS0=  "floor1/persist";
const std::string PERSIST_DIRS1 =" floor2/persist";
const std::string PERSIST_DIRS2 ="floor3/persist";
const std::string PERSIST_DIRS3 ="floor4/persist";
const std::string PERSIST_DIRS4 = "floor5/persist";

void client_define(int n, int pers_dir, string address) {
    //string client_name = "cli"+pers_dir;
    string connopts_name = "connopts"+pers_dir;
    string topic_names = "top"+pers_dir;
    string pers_dir_name = "PERSIST_DIR"+pers_dir;
    string temp_topic_name = "TEMP_TOPICS"+pers_dir;
    //char* connopts = [];
    string client_name = pers_dir+"client"+n;
    mqtt::async_client client(address, client_name, MAX_BUFFERED_MESSAGES, pers_dir_name);
    mqtt::topic top(client, temp_topic_name, QOS, true); 
    std::thread th1(temp_client_pub, client, top);
    th1.join();
    
    
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

void temp_client_pub(mqtt::async_client client, mqtt::topic topic) {


    try
    {
        cout<<"Connecting to server ..' "<<address<<" '.."<<flush; //std::flush used to display logging activity of thread before completion
        for (int i=0; i<6; i++)
        {
            char* msg = []
            client.connect(connopts)->wait();
            cout<<"OK\n"<<endl; //another available option is <<flush;

            char timebuffer[32];
            
            auto freq = std::chrono::milliseconds(500); //timer set for 500ms

            while(true) {
                this_thread::sleep_until(freq); //data gets pushed every 500ms

                msg[i] = random_message_generator(i);
                string payload = msg[i];
                cout<<payload<<endl;
                topic.publish(std::move(payload));

                timebuffer+=PERIOD;


            }
            //Disconnect
            //cout<<"\nDisconnecting.."<<flush;
            //client.
            

        }

    }
    catch(const mqtt::exception& e)
    {
        std::cerr << e.what() <<endl;
        return 1
    }
    return 0;
    
}

int main(int argc, char* argv[])
{
    const std::string address = (argv>1) ? string(argv[1]) : DEFLT_ADDRESS;

    mqtt::connect_options connopts;
    connopts.set_keep_alive_interval(MAX_BUFFERED_MESSAGES * PERIOD); 
    connopts.set_clean_session(true);
    connopts.set_automatic_reconnect(true);

    for (int i = 0; i<6; i++)
    {
        char* cli = [];
        client_define(i,0, address);
        client_define(i,1, address);
        client_define(i,2, address);
        client_define(i,3, address);
        client_define(i,4, address);

        );

    }
    //All temp_bot_clients are now defined

    //initiating threads for publishing data

    //for(int i=0; i<5; i++) //for 5 floors
    //{
      //  char* th = [];
        //std::thread th[i] (temp_client_pub) 
        //th[i].join();
    //}

}

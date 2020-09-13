#include <stdio.h>
#include <mosquitto.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>


void *client_define(struct mosquitto *client, int i, int nclients,const char* msg ){
    
    int rc[nclients];
    int rc2[nclients];
    client = mosquitto_new("client_id", true, NULL);
    rc[i] = mosquitto_connect(client, "localhost", 1883, 60);
    rc2[i] =mosquitto_loop_start(client);
    if (rc[i]!=0){
        printf("Client of id %d could not connect to the server, error code %d", i,rc[i]);
        mosquitto_destroy(client);

    }
    if (rc2[i]!=MOSQ_ERR_SUCCESS){
        printf("Client of id %d could not connect to the broker, error code %d", i, rc2[i]);
        mosquitto_destroy(client);
    }
    printf("Client id %d is now connected to broker\n", i);
    mosquitto_publish(client, NULL, "home/sensordata", strlen(msg)+1, msg, 1,false);
    mosquitto_disconnect(client);
    mosquitto_loop_stop(client, true);
    mosquitto_destroy(client);
    printf("published by  client %d\n",i);
    mosquitto_lib_cleanup();
    usleep(500000);//500 ms frequency


}
/*void *dclient_define(struct mosquitto *client, int i, int nclients,const char* msg ){
    
    int rc[nclients];
    int rc2[nclients];
    client = mosquitto_new("client_id", true, NULL);
    rc[i] = mosquitto_connect(client, "localhost", 1883, 60);
    rc2[i] =mosquitto_loop_start(client);
    if (rc[i]!=0){
        printf("Client of id %d could not connect to the server, error code %d", i,rc[i]);
        mosquitto_destroy(client);

    }
    if (rc2[i]!=MOSQ_ERR_SUCCESS){
        printf("Client of id %d could not connect to the broker, error code %d", i, rc2[i]);
        mosquitto_destroy(client);
    }
    printf("Client id %d is now connected to broker\n", i);
    mosquitto_publish(client, NULL, "house/temp", strlen(msg)+1, msg, 1, false);
    mosquitto_disconnect(client);
    mosquitto_loop_stop(client, false);
    mosquitto_destroy(client);
    usleep(500000);//500 ms frequency


}*/


int main(){
    int ntclients = 50;
    int ndclients = 20;
    char *add =  (char *)malloc(sizeof(add));
    int inf = 1;
    
    
    struct mosquitto * clients[ntclients];
    struct mosquitto * sub_client;
    mosquitto_lib_init();
    while(inf ==1){
    
        for (int i=0; i<ntclients; i++){
            //pthread_t thread_id;
            //const char* msgt = trandom_message_generator(i,add);
            if(i<30){
            int temp = (rand()%(111-39+1))+39;
            int humid = (rand()%(100+1));
            int tens = (rand()%10);
            int thousands = (rand()%1000);
            int air_presh = (rand()%(301-2+1))+2;
            int phint = (rand()%15);
            double dhumidity = humid + (thousands/1000);
            double dtemperature = temp + (humid/100);
            double dph = phint + (tens/10);
            char finalhumid[20];
            char finaltemp[20];
            char finalph[20];
            char finalap[20];
            char finalid[20];
            sprintf(finalhumid,"%f",dhumidity);
            sprintf(finaltemp,"%f",dtemperature);
            sprintf(finalph,"%f",dph);
            sprintf(finalap,"%d",air_presh);
            sprintf(finalid,"%d",i);
            char msgf[500]; 
            //char * msgt = msgf;


            /*char *msgt = "{\'device_id\': finalid,\
            \'timestamp\': \'30/08/2020 22:15:25\',\
            \'temperature\': finaltemp,\
            \'humidity\': finalhumid,\
            \'air_pressure\': finalap,\
            \'ph\': finalph,\
            }";*/
            char msg1[] = "{\'device_id\':";
            char msg2[] = ",\
            \'timestamp\': \'30/08/2020 22:15:25\',\
            \'temperature\':";
            char msg3[] = ",\
            \'humidity\':";
            char msg4[] = ",\
            \'air_pressure\':";
            char msg5[] = ",\
            \'ph\':";
            char msg6[] = ",\
            }";
            strcat(msgf,msg1);
            strcat(msgf,finalid);
            strcat(msgf,msg2);
            strcat(msgf,finaltemp);
            strcat(msgf,msg3);
            strcat(msgf,finalhumid);
            strcat(msgf,msg4);
            strcat(msgf,finalap);
            strcat(msgf,msg5);
            strcat(msgf,finalph);
            strcat(msgf,msg6);
            
            //temp messages done;
            


            client_define(clients[i], i, 50,msgf);}

            else if (i>29){
            
                char msgd[200];
                int dist = (rand()%(100+1));
                char distance[20];
                
                
                char id[20];
                double ddist = dist + (dist/100);
                sprintf(distance,"%f",ddist);
                sprintf(id,"%d",i);
                int random = (rand()%10);
                char switch_s[10] = "ON";
                char msg1[] = "{\'device_id\':";
                char msg2[] = ",\
                \'timestamp\': \'30ma/08/2020 22:15:25\',\
                \'distance\':";
                char msg3[] = ",\
                \'switch_state\':";
                char msg4[] = "}";
                strcat(msgd,msg1);
                strcat(msgd,id);
                strcat(msgd,msg2);
                strcat(msgd,distance);
                strcat(msgd,msg3);
                strcat(msgd,switch_s);
                strcat(msgd,msg4);

            
                client_define(clients[i],i,50,msgd);

                if (i==50){
                    i = 0;
                }
                
                

            }
            mosquitto_lib_cleanup();
            



        }
        

    }
       
    
    return 0;
}
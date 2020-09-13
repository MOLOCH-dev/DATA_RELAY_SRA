/*

C program to (1) subscribe to a topic
             (2) parse the json strings in the message payload
             (3) compress them and write them to a file every 2 minutes

For reference, from source file of "Mosquitto.h"
struct mosquitto_message{
	int mid;
	char *topic;
	void *payload;
	int payloadlen;
	int qos;
	bool retain;
};

Json Library used is https://github.com/udp/json-parser/blob/master/json.h


Compression Algorithm Implemented:-
https://www.geeksforgeeks.org/run-length-encoding/



*/


#include <stdio.h>
#include <mosquitto.h>
#include "json.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

/*static void compress_message(char *rec_message,int message_length, FILE *compfile){

    compfile =  fopen("received_data.txt", "a");

    
    char *dataToAppend, *countchar;
    char currentData[] = rec_message;
    for (int i = 0; i<message_length; i++){
        //Count occurences of current character
        int count = 1;
        while ((i<(message_length-1)) && currentData[i]==currentData[i+1]){
            //if (rec_message[i] != "/" || rec_message[i] == ",") // "/" character will be ignored as it rarely occurs beyond 2 at a time in json string
            //{ 
                count++;
                
                sprintf(countchar,"%d",count);
                char currentchar = currentData[i];

            //}
            //else{
              //  count = NULL;
        
                strcat(dataToAppend,currentchar);
                strcat(dataToAppend,countchar);

                fputs(dataToAppend,compfile);
        

        }

    }
    fclose(compfile);
    sleep(120); //Compress data evert 2 minutes


}*/

static void print_depth_shift(int depth)
{
        int j;
        for (j=0; j < depth; j++) {
                printf(" ");
        }
}

static void process_value(json_value* value, int depth);

static void process_object(json_value* value, int depth)
{
        int length, x;
        if (value == NULL) {
                return;
        }
        length = value->u.object.length;
        for (x = 0; x < length; x++) {
                print_depth_shift(depth);
                printf("object[%d].name = %s\n", x, value->u.object.values[x].name);
                process_value(value->u.object.values[x].value, depth+1);
        }
}

static void process_array(json_value* value, int depth)
{
        int length, x;
        if (value == NULL) {
                return;
        }
        length = value->u.array.length;
        printf("array\n");
        for (x = 0; x < length; x++) {
                process_value(value->u.array.values[x], depth);
        }
}


static void process_value(json_value* value, int depth){
    int j;
    if (value==NULL){
        return;
    }

    if( value->type!= json_object){
        print_depth_shift(depth);
    }
    switch (value->type) {
        case json_none:
            printf("none\n");
            break;
        case json_object:
            process_object(value, depth+1);
            break;
        case json_array:
            process_array(value, depth+1);
            break;
        case json_integer:
            printf("int: %10" PRId64 "\n", value->u.integer);
            break;
        case json_double:
            printf("double: %f\n", value->u.dbl);
            break;
        case json_string:
            printf("string: %s\n", value->u.string.ptr);
            break;
        case json_boolean:
            printf("bool: %d\n", value->u.boolean);
            break;
        }

}



void my_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message){
    FILE *compfile;
    
    json_char* json;
    json_value* value;
    char *rec_message; //character array to store the messages in
    //memset(rec_message, "/0", sizeof(rec_message));
    if(message->payloadlen){
        printf("message detected");
        rec_message = message->payload;
        json = (json_char*)rec_message;
        value = json_parse(json,message->payloadlen);
        if (value == NULL) {
            fprintf(stderr, "Unable to parse data\n");
            free(rec_message);
            exit(1);
        }
        process_value(value, 0);

        json_value_free(value);

        compfile =  fopen("received_data.txt", "a");

    
        char *countchar, *dataToAppend;

        char msgcast = *((char *)message->payload);
        int messsage_length = message->payloadlen;
        //for (int i = 0; i<messsage_length; i++){
        //Count occurences of current character
        int count = 1;
        /*while ((i<(messsage_length-1)) && msgcast[i]==msgcast[i+1]){
            //if (rec_message[i] != "/" || rec_message[i] == ",") // "/" character will be ignored as it rarely occurs beyond 2 at a time in json string
            //{ 
                count++;
                
                sprintf(countchar,"%d",count);
                

            //}
            //else{
              //  count = NULL;
        
                strcat(dataToAppend,msgcast[i]);
                strcat(dataToAppend,countchar);

                fputs(dataToAppend,compfile);
        

        }

    }
    fclose(compfile);
    sleep(120); //Compress data evert 2 minutes


        //compress_message(message->payload, message->payloadlen,compfile);
        
        
        free(rec_message);



    }
    else{
        printf("%s (null)",message->topic);
    }*/
    

    }
}

int main(){
    char client_id[] = "sub_client";
    int rc1;
    struct mosquitto * mosq;
    FILE *fp;
    
    mosquitto_lib_init();
    mosq = mosquitto_new(client_id,true,NULL);
    rc1 =mosquitto_connect(mosq, "localhost", 1883, 60);
    mosquitto_message_callback_set(mosq,my_message_callback);
    if (rc1!=0){
        printf("Client could not connect to broker\n");
        mosquitto_destroy(mosq);

    }
    printf("Client is now connected to broker\n");
    mosquitto_subscribe(mosq,NULL,"home/sensordata",1);
    mosquitto_loop_forever(mosq, -1, 1);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    return 0;






}

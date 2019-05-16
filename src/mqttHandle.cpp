//
// Created by hjk on 2018/11/12.
//
#include "../inc/mqttHandle.h"
const char *loraMqttHost="localhost";
const char *loraMattTopic="loradata";
string MqttPubHost="127.0.0.1";
int MqttPubPort=1883;
string MqttPubTopic="loraPub";
string MqttSubHost="127.0.0.1";
int MqttSubPort=1883;
string MqttSubTopic="loradata";
string MqttThisNode_Id="0100000000000001";
std::mutex mtxs;
string mqtt::getDatafrommqtt::getDataOnce(bool &ifGot) {

};

void mqtt::getDatafrommqtt::setConnect() {
    mosquitto_lib_init();
    mosq = mosquitto_new(NULL, clean_session, NULL);
    if(!mosq){
        fprintf(stderr, "Error: Out of memory.\n");
        return ;
    }
    mosquitto_log_callback_set(mosq, my_log_callback);
    mosquitto_connect_callback_set(mosq, my_connect_callback);
    mosquitto_message_callback_set(mosq, my_message_callback);
    mosquitto_subscribe_callback_set(mosq, my_subscribe_callback);
    if(mosquitto_connect(mosq, MqttSubHost.c_str(), MqttSubPort, loraMqttKeepalive)){
        fprintf(stderr, "Unable to connect.\n");
        return ;
    }
    else std::cout<<"connect OK!"<<std::endl;
    int subreturn=mosquitto_subscribe(mosq,mid,MqttSubTopic.c_str(),1);
    if(subreturn==MOSQ_ERR_SUCCESS)
        std::cout<<"subcribe OK!"<<std::endl;
    mosquitto_loop_forever(mosq, -1, 1);

}
void my_message_callback(struct mosquitto *mosq, void *userdata,
                                                const struct mosquitto_message *message)
{
    //std::cout<<"Got message and waiting towrite"<<endl;
    int semid=CreatSem();
    struct MqttFlag *readflag=new MqttFlag;
    while(1)
    {
            Sem_V(semid);
 	       // std::cout<<"start get flag"<<endl;
            ReadFlag(readflag);
            if(readflag->dbisFree)
            {
 		        std::cout<<"flag true"<<endl;
                break;
             }
            Sem_P(semid);
    }
    //std::cout<<"Ready towritrite!"<<endl;
    if(message->payloadlen)
    {
        //printf("%s %s\n", message->topic, message->payload); }else{
        //printf("%s (null)\n", message->topic);
        struct  MqttData *mqttData=new MqttData;
        mqttData->mqttlen=message->payloadlen;
        memcpy(mqttData->mqttdata,message->payload,message->payloadlen);
        std::cout<<"start write Data"<<endl;
        for(int i=0;i<TIMERETRY,!WriteData(mqttData);++i);
	    //WriteData(mqttData);
        std::cout<<"write Ok and start write flag"<<endl;
        readflag->dbisFree= false;
        for (int j = 0;j<TIMERETRY,!WriteFlag(readflag);++j);
        WriteFlag(readflag);
        std::cout<<"write OK"<<endl;
    }
    Sem_P(semid);
   // fflush(stdout);
}

void my_connect_callback(struct mosquitto *mosq, void *userdata, int result) {
    int i;
    if(!result){
        /* Subscribe to broker information topics on successful connect. */
       // mosquitto_subscribe(mosq, NULL, "$SYS/#", 2);
        std::cout<<"connect_back"<<endl;
    }else{
        fprintf(stderr, "Connect failed\n");
    }
}
void my_subscribe_callback(struct mosquitto *mosq, void *userdata, int mid, int qos_count,
                                                  const int *granted_qos) {
    int i;

    printf("Subscribed (mid: %d): %d", mid, granted_qos[0]);
    for(i=1; i<qos_count; i++){
        printf(", %d", granted_qos[i]);
    }
    printf("\n");
}
void my_log_callback(struct mosquitto *mosq, void *userdata, int level, const char *str) {
    /* Pring all log messages regardless of level. */
    printf("%s\n", str);
}

mqtt::sendDatafrommqtt::sendDatafrommqtt() {
    thistopics=MqttPubTopic;
    setConnect();
}

mqtt::sendDatafrommqtt::sendDatafrommqtt(string topics) {
    setConnect();
    thistopics=topics;
}

void mqtt::sendDatafrommqtt::disConnect() {
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    isconnected= false;
}
void mqtt::sendDatafrommqtt::setConnect() {
    mosquitto_lib_init();
    mosq = mosquitto_new(NULL, clean_session, NULL);
    if(!mosq){
        fprintf(stderr, "Error: Out of memory.\n");
        return ;
    }
    mosquitto_log_callback_set(mosq, my_log_callback);
    mosquitto_connect_callback_set(mosq, my_connect_callback);
    mosquitto_message_callback_set(mosq, my_message_callback);
    mosquitto_subscribe_callback_set(mosq, my_subscribe_callback);
    if(mosquitto_connect(mosq, MqttPubHost.c_str(), MqttPubPort, loraMqttKeepalive)){
        fprintf(stderr, "Unable to connect.\n");
        return ;
    }
    else std::cout<<"connect OK!"<<std::endl;
    isconnected= true;
}

bool mqtt::sendDatafrommqtt::sendData(string topics, char *data, int datalen) {
    if(!isconnected) setConnect();
    if(!isconnected) return false;
    mosquitto_publish(mosq,mid,topics.c_str(),datalen,data,1,true);
    return true;
}

bool mqtt::sendDatafrommqtt::sendData(char *data, int datalen) {
    if(thistopics.compare("NULL")==0) return false;
    if(!isconnected) setConnect();
    if(!isconnected) return false;
    mosquitto_publish(mosq,mid,thistopics.c_str(),datalen,data,1,true);
    return true;
}

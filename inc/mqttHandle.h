//
// Created by hjk on 2018/11/12.
//

#ifndef LORAHANDLBYC_MQTTHANDLE_H
#define LORAHANDLBYC_MQTTHANDLE_H


#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>
#include <mosquitto.h>
#include <stdio.h>
#include "transmit.h"
#include <thread>
#include <mutex>
#include <memory>
#define loraMqttPort  1883
#define loraMqttKeepalive 60
#define CLIENTID    "LoraClientByC"
#define TOPIC       "loradata"
#define PAYLOAD     "Hello World!"
#define QOS         1
#define TIMEOUT     10000L
#define TIMERETRY   10
using namespace std;
extern string MqttPubHost;
extern string MqttPubTopic;
extern int MqttPubPort;
extern string MqttSubHost;
extern string MqttSubTopic;
extern int MqttSubPort;
void my_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message);
void my_connect_callback(struct mosquitto *mosq, void *userdata, int result);
void my_subscribe_callback(struct mosquitto *mosq, void *userdata, int mid, int qos_count, const int *granted_qos);
void my_log_callback(struct mosquitto *mosq, void *userdata, int level, const char *str);
namespace mqtt{
    class getDatafrommqtt{
    public:
        getDatafrommqtt(){setConnect();}
        string getDataOnce(bool &ifGot);
        void setConnect();
        ~getDatafrommqtt(){
            mosquitto_destroy(mosq);
            mosquitto_lib_cleanup();
            std::cout<<"disconnect mqtt"<<endl;
        }
    private:
        struct mosquitto *mosq = NULL;
        int *mid=NULL;
        bool clean_session = true;
    };

    class sendDatafrommqtt{
    public:
        sendDatafrommqtt();
        sendDatafrommqtt(string topics);
        void setConnect();
        bool sendData(string topics,char *data,int datalen);
        bool sendData(char *data,int datalen);
        void disConnect();
        ~sendDatafrommqtt(){
            mosquitto_destroy(mosq);
            mosquitto_lib_cleanup();
            //std::cout<<"disconnect mqtt"<<endl;
        }
    private:
        struct mosquitto *mosq = NULL;
        int *mid=NULL;
        bool clean_session = true;
        bool isconnected= false;
        string thistopics="NULL";
    };
}

#endif //LORAHANDLBYC_MQTTHANDLE_H
//
// Created by hjk on 2018/11/16.
//
#include "../inc/initValue.h"

initValue::initValue() {
    thisjsonpath="NULL";
}
initValue::initValue(string jsonpath) {
    thisjsonpath=jsonpath;
}

bool initValue::initSetMqtt() {
    if(thisjsonpath.compare("NULL")==0) return false;
    try{
        ifstream ifs;
        ifs.open(thisjsonpath,std::ifstream::in);
        ifs.close();
    }
    catch (exception e)
    {
        std::cout<<e.what()<<endl;
    }
    jsonHandle json(thisjsonpath);
    MqttSubHost=json.getStringValue(string("MqttSubHost"));
    MqttSubPort=json.getIntValue(string("MqttSubPort"));
    MqttSubTopic=json.getStringValue(string("MqttSubTopic"));
    MqttPubHost=json.getStringValue(string("MqttPubHost"));
    MqttPubPort=json.getIntValue(string("MqttPubPort"));
    MqttPubTopic=json.getStringValue(string("MqttPubTopic"));
    std::cout<<"MqttSubHost:"<<MqttSubHost<<endl;
    std::cout<<"MqttSubPort:"<<MqttSubPort<<endl;
    std::cout<<"MqttSubTopic:"<<MqttSubTopic<<endl;
    std::cout<<"MqttPubHost:"<<MqttSubHost<<endl;
    std::cout<<"MqttPubPort:"<<MqttPubPort<<endl;
    std::cout<<"MqttPubTopic:"<<MqttPubTopic<<endl;
    return true;
}

bool initValue::initSetDb() {
    if(thisjsonpath.compare("NULL")==0) return false;
    return true;
}


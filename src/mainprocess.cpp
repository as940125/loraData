//
// Created by hjk on 2018/11/13.
//
#include "../inc/mainprocess.h"
std::mutex mtx;
std::map<string,int> Process::lightAlarm;
bool paraInit()
{
    initValue init("/loraDataHandle.json");
    if(!init.initSetMqtt()) return false;
    if(!init.initSetDb()) return false;
    return true;
}
void mqttHandlefunc()
{
    std::cout<<"starting Mqtt"<<std::endl;
    mqtt::getDatafrommqtt *getData=new getDatafrommqtt;
    std::cout<<"Mqtt end"<<std::endl;
}

void sendOnce(string nodeplay_eui){
    vector<string> nodeseuis;
    vector<char> alarmnum;
    db *dbpoint=new db;
    char Send[102];
    dbpoint->dbFindNodeofNodeplayEUI(nodeseuis,nodeplay_eui);
    packagebuf packagebufs;
    packagebufs.type=1;
    memset(packagebufs.state,0,100);
    for(int i=1;i<nodeseuis.size();++i)
    {
        unsigned char online;
        unsigned char alarmstate;
        dbpoint->dbFindNodestate(nodeseuis[i],alarmstate,online);
        packagebufs.state[i]=online;
        std::cout<<nodeseuis[i]<<":"<<(unsigned int) alarmstate<<"Online:"<<(unsigned int)online<<endl;
        if((unsigned int)alarmstate!=128&&online==1)
            alarmnum.push_back(i);
    }
    if(alarmnum.size()==0){
        packagebufs.num=0;
        memcpy(Send,&packagebufs, sizeof(packagebufs));
        mqtt::sendDatafrommqtt sendget;
        sendget.sendData("nodeplay/tx/"+nodeplay_eui,Send, sizeof(Send));
    }else{
        for(int j=0;j<alarmnum.size();++j)
        {
            packagebufs.num=alarmnum[j];
            memcpy(Send,&packagebufs, sizeof(packagebufs));
            mqtt::sendDatafrommqtt sendget;
            sendget.sendData("nodeplay/tx/"+nodeplay_eui,Send, sizeof(Send));
        }
    }
}

void ManualProcess(string dev_euis,char *p,size_t plen)
{
    db *dbpoint=new db;
    if(dbpoint->charToUint(p[0])!=128){//alarm
        std::lock_guard<std::mutex> lockGuard(mtx);
        vector<string> light;
        dbpoint->FindLightAlarmBelongtoManual(dev_euis,light);
        mqtt::sendDatafrommqtt sendmqtt;
        string topic1="application/1/device/";
        for(int i=0;i<light.size();++i)
        {
            char data[200];
            std::cout<<dev_euis<<"#"<<light[i]<<endl;
            string jsons="{\"confirmed\":true,\"fPort\":2,\"data\":\"AQAAAA==\"}";
            strcpy(data,jsons.c_str());
            sendmqtt.sendData(topic1+light[i]+"/tx",data,jsons.size());
            std::map<string,int>::iterator it=Process::lightAlarm.find(light[i]);
            if(it==Process::lightAlarm.end())
                Process::lightAlarm.insert(std::pair<string,int>(light[i],64));
            usleep(2000);
        }
    }
}

int DataHandle(MqttData *mqttData)
{
    if(mqttData->mqttlen<16)
        return -1;
    char dev_euis[17];
    char *dev_eui=dev_euis;
    memcpy(dev_eui,mqttData->mqttdata,16);
    dev_eui[16]='\0';
    string dev_euistr(dev_eui);
    db *dbpoint=new db;
    std::cout<<"Get Type"<<endl;
    string types=dbpoint->dbGetDevType(dev_euistr);
    std::cout<<"Get Type OK"<<endl;
    char data[50];
    std::cout<<types<<endl;
    memcpy(data,mqttData->mqttdata+17,mqttData->mqttlen-17);
    data[mqttData->mqttlen-17]='\0';
    if(types.compare("smoke")==0)
    {
        if(mqttData->mqttlen!=21) return 0;
        bool samedata=dbpoint->dbIfsameData(dev_euistr,4);
        if(samedata)
            return 0;
        dbpoint->dbSmokeInsert(data, dev_euistr);
        //char dataack[]={0x01,0x02};
       // dbpoint->dbInsertSmokeACK(dev_euistr,dataack,1);
        if(dbpoint->charToUint(data[0])!=128&&dbpoint->charToUint(data[0])!=0x00) //异常
        {
            string nodeplay=dbpoint->dbGetNodeplayEui(dev_euistr);
            /*char data[]={0x01,0x02};
            dbpoint->dbInsertLightWaringdown("0101010000000001",data,2);
            mqtt::sendDatafrommqtt sendget;
            string comand="down#";
            string comand2=comand+"0101010000000001";
            char Send[22];
            strcpy(Send,comand2.c_str());
            sendget.sendData("gateway/0000/rx",Send,comand2.size());*/          //the old version to send to lightalarm
            sendOnce(nodeplay);
        }
    }
    else if(types.compare("tem_humi")==0)
    {
        //if(mqttData->mqttlen!=34) return 0;
        dbpoint->dbTemHumiInsert(data, dev_euistr);
    }
    else if(types.compare("manual")==0)
    {
        dbpoint->dbInsertManualState(dev_euistr,data,4);
        ManualProcess(dev_euistr,data,4);
    }
    else if(types.compare("light_alarm")==0)
    {
        dbpoint->dbInsertLightalarm(dev_euistr, data, 4);
        if(dbpoint->charToUint(data[0])==64) {
            std::lock_guard <std::mutex> lockGuard(mtx);
            std::map<string, int>::iterator it = Process::lightAlarm.find(dev_euistr);
            if(it!=Process::lightAlarm.end())
                Process::lightAlarm.erase(it);
        }
    }
    return 0;
}

void dbHandlefunc()
{
    std::cout<<"Database server starting!"<<endl;
    int semid=CreatSem();
    int firsttime=0;
    struct MqttFlag *readflag=new MqttFlag;
    while(1)
    {
        Sem_V(semid);
        ReadFlag(readflag);
        if(!readflag->dbisFree)
        {
            struct  MqttData *mqttData=new MqttData;
            ReadData(mqttData);
            std::cout<<"Got Data len:"<<mqttData->mqttlen<<endl;
            mqtt::sendDatafrommqtt sendget;
            sendget.sendData(mqttData->mqttdata,mqttData->mqttlen);
            if(firsttime==0) firsttime++;
            else DataHandle(mqttData);
            readflag->dbisFree= true;
            WriteFlag(readflag);
        }
        Sem_P(semid);
    }
}

void broadHandle()
{
    while(1)
    {
        vector<string> nodeplay;
        db *dbpoint=new db;
        dbpoint->dbFindAllNodeplay(nodeplay);
        for(int i=0;i<nodeplay.size();++i)
        {
            sendOnce(nodeplay[i]);
        }
        sleep(30);
    }
}

void handleDownLightAlarm()
{
    while(1)
    {
        sleep(240);
        while(1){
            std::lock_guard<std::mutex> lockGuard(mtx);
            mqtt::sendDatafrommqtt sendmqtt;
            string topic1="application/1/device/";
            std::map<string,int>::iterator it;
            for(it=Process::lightAlarm.begin();it!=Process::lightAlarm.end();it++)
            {
                char data[200];
                string jsons="{\"confirmed\":true,\"fPort\":2,\"data\":\"TEQx\"}";
                strcpy(data,jsons.c_str());
                sendmqtt.sendData(topic1+it->first+"/tx",data,jsons.size());
            }
            break;
        }
    }
}

void Process::mains()
{
    if(TransmitInit()<0)
    {
        std::cout<<"Transmit Init Failed!"<<std::endl;
        return;
    }
    if(!paraInit())
        return;
    sleep(1);
    std::thread thread_mqtt(mqttHandlefunc);
    std::thread thread_db(dbHandlefunc);
    std::thread thread_broad(broadHandle);
    std::thread thread_lightalarm(handleDownLightAlarm);
    //std::thread threadtest(test);
    thread_mqtt.join();
    thread_db.join();
    thread_broad.join();
    thread_lightalarm.join();
    //threadtest.join();
}
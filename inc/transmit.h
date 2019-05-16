//
// Created by hjk on 2018/11/13.
//
#ifndef LORAHANDLBYC_TRANSMIT_H
#define LORAHANDLBYC_TRANSMIT_H
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <iostream>
#define KeyShared 9201
#define KeyFlag   9202
#define KeySem    9203
#define MAXSizeData 200
using namespace std;
extern int mqttRecivedatalen;
typedef int sem_t;
typedef struct MqttData{
    int mqttlen;
    char mqttdata[MAXSizeData];
};
typedef struct MqttFlag{
    bool dbisFree;
};
union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};
int TransmitInit();
int CreatSharedMemory();
int CreatSharedFlag();
int CreatSem();
bool WriteData(MqttData *mqttData);
bool ReadData(MqttData *mqttData);
bool WriteFlag(MqttFlag *mqttFlag);
bool ReadFlag(MqttFlag *mqttFlag);
int Sem_P(sem_t semid);          //+1
int Sem_V(sem_t semid);           //-1

#endif //LORAHANDLBYC_TRANSMIT_H

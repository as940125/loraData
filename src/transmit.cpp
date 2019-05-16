//
// Created by hjk on 2018/11/13.
//
#include "../inc/transmit.h"

int mqttRecivedatalen;
int TransmitInit()
{
    int shmid=CreatSharedMemory();
    int shmidf=CreatSharedFlag();
    std::cout<<"KeySem Value:"<<KeySem<<std::endl;
    int semidSem=CreatSem();
    if(shmid<0||shmidf<0||semidSem<0)
    {
        std::cout<<"SharedMemory Creat Error!"<<std::endl;
        return -1;
    }
    else
        std::cout<<"SharedMemory Creat OK!:"<<shmid<<std::endl;
    struct MqttFlag *init=new MqttFlag;
    init->dbisFree= true;
    struct MqttData *initdata=new MqttData;
    memset(initdata->mqttdata,0,MAXSizeData);
    initdata->mqttlen=0;
    if(!WriteFlag(init)) return -1;
    if(!WriteData(initdata)) return -1;
    return 1;
}

int CreatSharedMemory()
{
    int shmid=shmget( KeyShared,1024,0666|IPC_CREAT );
    if(shmid<0)
        std::cout<<"SharedMemory Creat Error!"<<std::endl;
    else
        std::cout<<"SharedMemory Creat OK!"<<std::endl;
    return shmid;
}

int CreatSharedFlag()
{
    int shmid=shmget( KeyFlag,32,0666|IPC_CREAT );
    if(shmid<0)
        std::cout<<"SharedMemory Creat Error!"<<std::endl;
    else
        std::cout<<"SharedMemory Creat OK!"<<std::endl;
    return shmid;
}
int CreatSem()
{
    union semun sem;
    sem.val = 1;
    int semid=semget(KeySem,1,IPC_CREAT|0666);
    if(semid==-1)
    {
        std::cout<<"Sem Creat Error!"<<std::endl;
        return -1;
    }
    semctl(semid,0,SETVAL,sem);
    return semid;
}

int Sem_P(sem_t semid)
{
    struct sembuf sops={0,+1,SEM_UNDO}; //P,wait()
    return (semop(semid,&sops,1));
}

int Sem_V(sem_t semid)
{
    struct sembuf sops={0,-1,SEM_UNDO}; //P,wait()
    return (semop(semid,&sops,1));
}
bool WriteData(MqttData *mqttData)
{
    try {
        int shmid = shmget(KeyShared, 1024, 0666 | IPC_CREAT);
        if(shmid<0)
        {
            std::cout<<"Write to Share Memorry Error!"<<endl;
            return false;
        }
        void *shm = shmat(shmid, (void *) 0, 0);
        MqttData *mqttData1 = (MqttData *) shm;
        mqttData1->mqttlen = mqttData->mqttlen;
        memcpy(mqttData1->mqttdata, mqttData->mqttdata, mqttData->mqttlen);
        shmdt(shm);
    }
    catch (int i){
        if(i==0) return false;
    };
    return true;
}

bool ReadData(MqttData *mqttData)
{
    try
    {
        int shmid = shmget(KeyShared, 1024, 0666 | IPC_CREAT);
        if(shmid<0)
        {
            std::cout<<"Read Share Memorry Error!"<<endl;
            throw 0;
        }
        void *shm = shmat(shmid, (void *) 0, 0);
        MqttData *mqttData1 = (MqttData *) shm;
        mqttData->mqttlen = mqttData1->mqttlen;
        memcpy(mqttData->mqttdata, mqttData1->mqttdata, mqttData1->mqttlen);
        shmdt(shm);
    }
    catch (int i){
        if(i==0) return false;
    };
    return true;
}

bool WriteFlag(MqttFlag *mqttFlag)
{
    try {
        int shmid = shmget(KeyFlag, 32, 0666 | IPC_CREAT);
        if(shmid<0)
        {
            std::cout<<"Write to Share Memorry Flag Error!"<<endl;
            return false;
        }
        void *shm = shmat(shmid, (void *) 0, 0);
       MqttFlag *mqttFlag1=(MqttFlag *) shm;
       mqttFlag1->dbisFree=mqttFlag->dbisFree;
       shmdt(shm);
    }
    catch (int i){
        if(i==0) return false;
    };
    return true;
}

bool ReadFlag(MqttFlag *mqttFlag)
{
    try {
          int shmid = shmget(KeyFlag, 32, 0666 | IPC_CREAT);
          if(shmid<0)
          {
              std::cout<<"Read Share Memorry Flag Error!"<<endl;
              return false;
          }
          void *shm = shmat(shmid, (void *) 0, 0);
          MqttFlag *mqttFlag1=(MqttFlag *) shm;
          mqttFlag->dbisFree=mqttFlag1->dbisFree;
          shmdt(shm);
    }
    catch (int i){
        if(i==0) return false;
    };
    return true;
}
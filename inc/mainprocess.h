//
// Created by hjk on 2018/11/13.
//

#ifndef LORAHANDLBYC_MAINPROCESS_H
#define LORAHANDLBYC_MAINPROCESS_H

#include "dbHandle.h"
#include "mqttHandle.h"
#include "transmit.h"
#include "jsonHandle.h"
#include "initValue.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <mutex>
#include <vector>
#include <unistd.h>
#include <map>
#include <utility>
#include <iterator>
using namespace std;
using namespace mqtt;
void mqttHandlefunc();
void dbHandlefunc();

struct packagebuf//package format
{
    char state[100];//0:offline, 1:online, 2:others
    char num;//alarm Num, 0:no alarm
    char type;//alarm type, 0:no alarm, 1:powerdown 2:fire alarm
};

class Process{
public:
    void mains();
    static std::map<string,int> lightAlarm;
private:
};
#endif //LORAHANDLBYC_MAINPROCESS_H




//
// Created by hjk on 2018/11/16.
//

#ifndef LORAHANDLBYCALI_INITVALUE_H
#define LORAHANDLBYCALI_INITVALUE_H
#include "jsonHandle.h"
#include "mqttHandle.h"
class initValue{
public:
    initValue();
    initValue(string jsonpath);
    bool initSetMqtt();
    bool initSetDb();
private:
    string thisjsonpath;
};
#endif //LORAHANDLBYCALI_INITVALUE_H

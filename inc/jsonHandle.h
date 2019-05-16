//
// Created by hjk on 2018/11/16.
//

#ifndef LORAHANDLBYCALI_JSONHANDLE_H
#define LORAHANDLBYCALI_JSONHANDLE_H
#include <jsoncpp/json/json.h>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace Json;
class jsonHandle
{
public:
    jsonHandle();
    jsonHandle(string path);
    string getStringValue(string path,string valuename);
    string getStringValue(string valuename);
    int getIntValue(string path,string valuename);
    int getIntValue(string valuename);
    ~jsonHandle(){}
private:
    string thispath;
    Json::Value jsonRoot;
    Json::Reader jsonReader;
    ofstream ofs; //标准输出流
    ifstream ifs; //标准输入流
};
#endif //LORAHANDLBYCALI_JSONHANDLE_H

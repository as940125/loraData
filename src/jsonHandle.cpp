//
// Created by hjk on 2018/11/16.
//

#include "../inc/jsonHandle.h"

jsonHandle::jsonHandle() {
    thispath="NULL";
}
jsonHandle::jsonHandle(string path) {
    thispath=path;
    try {
        ifs.open(path);
    }
    catch (int i)
    {
        std::cout<<"Open json file failed!"<<endl;
    }
    //jsonRoot.clear();
}

string jsonHandle::getStringValue(string path, string valuename) {
    std::ifstream ifstream1(path,ios::binary);
    Json::Reader jsonReader1;
    jsonRoot.clear();
    if(jsonReader1.parse(ifstream1,jsonRoot))
        return jsonRoot[valuename].asString();
}

string jsonHandle::getStringValue(string valuename) {
    if(thispath.compare("NULL")==0)
        return "WRONG";
    else
    {
        std::ifstream ifstream1(thispath,ios::binary);
        jsonRoot.clear();
        if(jsonReader.parse(ifstream1,jsonRoot))
            return jsonRoot[valuename].asString();
    }
}

int jsonHandle::getIntValue(string path, string valuename) {
    std::ifstream ifstream1(path,ios::binary);
    Json::Reader jsonReader1;
    jsonRoot.clear();
    if(jsonReader1.parse(ifstream1,jsonRoot))
        return jsonRoot[valuename].asInt();
}

int jsonHandle::getIntValue(string valuename) {
    if(thispath.compare("NULL")==0)
        return 0;
    else
    {
        std::ifstream ifstream1(thispath,ios::binary);
        jsonRoot.clear();
        if(jsonReader.parse(ifstream1,jsonRoot))
            return jsonRoot[valuename].asInt();
    }
}

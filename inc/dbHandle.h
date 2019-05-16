//
// Created by hjk on 2018/11/12.
//

#ifndef LORAHANDLBYC_DBHANDLE_H
#define LORAHANDLBYC_DBHANDLE_H
#include "pqDbHandle.h"
#include <string>
#include <iostream>
#include <algorithm>
//#include <math>
#include<sstream>
#include <time.h>
#include <vector>
#include "transmit.h"
using  namespace std;
extern const char *dbnames;
class db{
public:
    db();
    bool dbInseartanewline(string tablename,string data);
    string dbGetDevType(string dev_eui);
    bool dbSmokeInsert(char *data,string dev_euis);
    bool dbTemHumiInsert(char *data,string dev_euis);
    string dbGetNodeplayEui(string dev_euis);
    void dbFindNodeofNodeplayEUI(vector<string>& euis,string nodeplayeui);
    void dbFindNodestate(string dev_euis,unsigned char &alarmstate,unsigned char &online);
    bool dbIfsameData(string dev_euis,int dis);
    void dbFindAllNodeplay(vector<string> &dev_euis);
    void dbInsertLightWaringdown(string dev_euis,char *p,size_t plen);
    void dbInsertSmokeACK(string dev_euis, char *p,size_t plen);
    void dbInsertManualState(string dev_euis,char *p,size_t plen);
    void dbInsertLightalarm(string dev_euis,char*p,size_t plen);
    void StringEUItoByteEUI(string dev_euis,unsigned char dev_eui[8]);
    void FindLightAlarmBelongtoManual(string dev_eui_manual,vector<string> &light);
    unsigned int charToUint(char ch);
    string getTime();
    time_t strTime2unix(std::string timeStamp);
    virtual ~db();
private:
    dbAPI *dbAPIp;
    string dbname;
};
#endif //LORAHANDLBYC_DBHANDLE_H

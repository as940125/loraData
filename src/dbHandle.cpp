//
// Created by hjk on 2018/11/12.
//
#include "../inc/dbHandle.h"

const char *dbnames="postgresql";
db::db()
{
    string ss(dbnames);
    dbAPI dbapi;
    dbAPIp=dbapi.getDb(ss);
};
db::~db()
{
    delete dbAPIp;
};

bool db::dbInseartanewline(string tablename,string data) {
    string test="INSERT INTO tem_hum_para (dev_eui,temp_value,humi_value,datetime,light_value) VALUES('aabb',3.2,2.1,'2018-11-12 22:13:33',2.0)";
    dbAPIp->dbSql(data);
}

string db::dbGetDevType(string dev_eui) {
    string type("FINDNONE");
   // string type("tem_humi");
    string sql1="SELECT dev_eui,type FROM sensor_info WHERE dev_eui='"+dev_eui+"'";
    result answer=dbAPIp->dbSqlSelect(sql1);
    for (result::const_iterator c = answer.begin(); c != answer.end(); ++c)
        if(c[0].as<string>().compare(dev_eui)==0) return c[1].as<string>();
    return type;
}

void db::dbFindNodeofNodeplayEUI(vector<string> &euis,string nodeplayeui) {
    string sql="SELECT dev_eui,posx,posy FROM sensor_info WHERE posx='"+nodeplayeui+"'";
    result answer=dbAPIp->dbSqlSelect(sql);
    for (result::const_iterator c = answer.begin(); c != answer.end(); ++c)
    {
        if(c[1].as<string>().compare(nodeplayeui)==0)
        {
            string num=c[2].as<string>();
            int nums=std::atoi(num.c_str());
            if(euis.size()<nums+1) euis.resize(nums+1);
            euis[nums]=c[0].as<string>();
        }
    }
}
void db::dbFindAllNodeplay(vector<string> &dev_euis) {
    string sql="SELECT playnode_eui FROM node_playnode";
    result answer=dbAPIp->dbSqlSelect(sql);
    for (result::const_iterator c = answer.begin(); c != answer.end(); ++c)
    {
        dev_euis.push_back(c[0].as<string>());
    }
}
void db::dbFindNodestate(string dev_euis, unsigned char &alarmstate, unsigned char &online) {
    string sql="SELECT dev_eui,alarm_state,datetime from smoke_para where dev_eui='"+dev_euis+"' order by datetime desc limit 1";
    result answer=dbAPIp->dbSqlSelect(sql);
    online= 0;
    for (result::const_iterator c = answer.begin(); c != answer.end(); ++c)
    {
        if(c[0].as<string>().compare(dev_euis)==0)
        {
            alarmstate=c[1].as<unsigned int>();
            string timelast=c[2].as<string>();
            string timenow=getTime();
            time_t timestart=strTime2unix(timelast);
            time_t timeend=strTime2unix(timenow);
            double dif=difftime(timeend,timestart);
            if(dif<2*60*60) online= 1;
        }
    }
}
bool db::dbIfsameData(string dev_euis, int dis) {   //dis second
    string sql="SELECT dev_eui,datetime from smoke_para where dev_eui='"+dev_euis+"' order by datetime desc limit 1";
    result answer=dbAPIp->dbSqlSelect(sql);
    bool ifsame= false;
    for (result::const_iterator c = answer.begin(); c != answer.end(); ++c)
    {
        if(c[0].as<string>().compare(dev_euis)==0)
        {
            string timelast=c[1].as<string>();
            string timenow=getTime();
            time_t timestart=strTime2unix(timelast);
            time_t timeend=strTime2unix(timenow);
            double dif=difftime(timeend,timestart);
            std::cout<<"Dif:"<<dif<<endl;
            if(dif<dis) ifsame= true;
        }
    }
    return ifsame;
}
bool db::dbSmokeInsert(char *data,string dev_euis) {
    int alarm_state=charToUint(data[0]);
    int white_smoke=charToUint(data[1]);
    int black_smoke=charToUint(data[2]);
    double voltage=1048.0/(256.0+charToUint(data[3]));
    string save1="INSERT INTO smoke_para (dev_eui,white_smoke,datetime,black_smoke,voltage,alarm_state) VALUES('"+dev_euis+"',";
    string alarm_states;
    string white_smokes;
    string black_smokes;
    string voltages;
    ostringstream os;
    os<<std::abs(alarm_state);
    istringstream is1(os.str());
    is1>>alarm_states; os.str("");
    os<<std::abs(white_smoke);
    istringstream is2(os.str());
    is2>>white_smokes; os.str("");
    os<<std::abs(black_smoke);
    istringstream is3(os.str());
    is3>>black_smokes; os.str("");
    os<<voltage;
    istringstream is4(os.str());
    is4>>voltages;
    string datetimes=getTime();
    string save2=save1+white_smokes+","+"'"+datetimes+"',"+black_smokes+","+voltages+","+alarm_states+")";
    //std::cout<<save2<<endl;
    dbAPIp->dbSql(save2);
    return true;
}

bool db::dbTemHumiInsert(char *data,string dev_euis) {
    string save1="INSERT INTO tem_hum_para (dev_eui,temp_value,humi_value,datetime,light_value) VALUES('"+dev_euis+"',";
    string datetimes=getTime();
    char  light[20];
    char  temp[20];
    char  rh[20];
    int i=0;
    if(data[0]!='L')
    {
        std::cout<<"tem_humi data error!"<<endl;
        return false;
    }
    data+=2;
    //std::cout<<"db"<<endl;
    while(*data!=' ')
    {
        light[i++]=*data;
        data++;
    }
    light[i]='\0';
    i=0;
    for(data+=3;*data!=' ';i++,data++)
        temp[i]=*data;
    temp[i]='\0';
    i=0;
    for(data+=4;*data!='\0';i++,data++)
        rh[i]=*data;
    rh[i]='\0';
    string lights(light);
    string temps(temp);
    string humis(rh);
    string save2=save1+temps+","+humis+",'"+datetimes+"',"+lights+")";
    std::cout<<save2<<endl;
    dbAPIp->dbSql(save2);
    return true;
}
void db::dbInsertManualState(string dev_euis, char *p, size_t plen) {
    string datetimes=getTime();
    double voltage=(1.0+(double)charToUint(p[3])-1.0)/75.0;
    unsigned int alrmstate=charToUint(p[0]);
    string voltages;
    string alrmstates;
    ostringstream os;
    os<<voltage;
    istringstream is1(os.str());
    is1>>voltages;os.str("");
    os<<alrmstate;
    istringstream is2(os.str());
    is2>>alrmstates;
    string save1="INSERT INTO manual_alarm_para (dev_eui,datetime,alarm_state,voltage) "\
                 "VALUES('"+dev_euis+"','"+datetimes+"',"+alrmstates+","+voltages+")";
    dbAPIp->dbSql(save1);
}

void db::dbInsertLightalarm(string dev_euis, char *p, size_t plen) {
    unsigned int state=charToUint(p[0]);
    string datetimes=getTime();
    string states;
    ostringstream os;
    os<<state;
    istringstream is1(os.str());
    is1>>states;
    string sqls="INSERT INTO light_alarm_para (dev_eui,datetime,state) VALUES('"+
                dev_euis+"','"+datetimes+"',"+states+")";
    dbAPIp->dbSql(sqls);
}
string db::dbGetNodeplayEui(string dev_euis) {
    string type("FINDNONE");
    string save1="SELECT dev_eui,posx from sensor_info where dev_eui='"+dev_euis+"'";
    result answer=dbAPIp->dbSqlSelect(save1);
    for (result::const_iterator c = answer.begin(); c != answer.end(); ++c)
        if(c[0].as<string>().compare(dev_euis)==0) return c[1].as<string>();
    return type;
}

void db::FindLightAlarmBelongtoManual(string dev_eui_manual, vector <string> &light) {
    string sqls="SELECT dev_eui_light,dev_eui_manual from light_alarm_info where dev_eui_manual='"
                +dev_eui_manual+"'";
    result answer=dbAPIp->dbSqlSelect(sqls);
    for (result::const_iterator c = answer.begin(); c != answer.end(); ++c)
        light.push_back(c[0].as<string>());
}

string db::getTime() {
    time_t timep;
    time (&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S",localtime(&timep) );
    return tmp;
}

void db::dbInsertLightWaringdown(string dev_euis, char *p,size_t plen) {
    pqxx::connection conn("dbname=loraserver user=loraserver password=dbpassword hostaddr=106.14.211.51 port=5432");
    conn.prepare( "test", "INSERT INTO downlink_queue(reference,dev_eui,confirmed,pending,fport,data) VALUES ($1,$2,$3,$4,$5,$6)" );
    pqxx::work work( conn );
    string ss("hello");
    void * bin_data =(void *)p;
    size_t bin_size = plen;
    unsigned char dev_eui[8];
    StringEUItoByteEUI(dev_euis,dev_eui);
    void * bin_eui=(void *)dev_eui;
    pqxx::binarystring blobdata( bin_data, bin_size );
    pqxx::binarystring blobeui(bin_eui,8);
    pqxx::result r = work.prepared( "test" )(ss.c_str())(blobeui)(1)(1)(2)( blobdata ).exec();
    work.commit();
    conn.disconnect();
}
void db::dbInsertSmokeACK(string dev_euis, char *p,size_t plen)
{
    std::cout<<"/*****************/"<<endl;
    std::cout<<"/*****dbInsertSmokeACK******/"<<endl;
    std::cout<<"/*****************/"<<endl;
    pqxx::connection conn("dbname=loraserver user=loraserver password=dbpassword hostaddr=106.14.211.51 port=5432");
    conn.prepare("test1","SELECT dev_eui from downlink_queue where reference='"+dev_euis+"'");
    pqxx::work works(conn);
    unsigned char dev_eui[8];
    StringEUItoByteEUI(dev_euis,dev_eui);
    void * bin_eui=(void *)dev_eui;
    pqxx::binarystring blobeui(bin_eui,8);
    pqxx::result answer = works.prepared("test1").exec();
    works.commit();
    result::const_iterator c = answer.begin();
    if(c != answer.end())
        return;
    std::cout<<"need to Insert"<<endl;
    conn.prepare( "test", "INSERT INTO downlink_queue(reference,dev_eui,confirmed,pending,fport,data) VALUES ($1,$2,$3,$4,$5,$6)" );
    pqxx::work work( conn );
    string ss(dev_euis);
    void * bin_data =(void *)p;
    size_t bin_size = plen;
    pqxx::binarystring blobdata( bin_data, bin_size );
    pqxx::result r = work.prepared( "test" )(ss.c_str())(blobeui)(1)(1)(2)( blobdata ).exec();
    work.commit();
    conn.disconnect();
}

time_t db::strTime2unix(std::string timeStamp)
{
    struct tm tm;
    memset(&tm, 0, sizeof(tm));

    sscanf(timeStamp.c_str(), "%d-%d-%d %d:%d:%d",
           &tm.tm_year, &tm.tm_mon, &tm.tm_mday,
           &tm.tm_hour, &tm.tm_min, &tm.tm_sec);

    tm.tm_year -= 1900;
    tm.tm_mon--;

    return mktime(&tm);
}

void db::StringEUItoByteEUI(string dev_euis, unsigned char dev_eui[8]) {
    for(int i=0;i<8;++i)
    {
        unsigned char temp=0x00;
        if(dev_euis[i*2]>0x39) temp=(dev_euis[i*2]-0x57)<<4;
        else temp=(dev_euis[i*2]-0x30)<<4;
        if(dev_euis[i*2+1]>0x39) temp=temp|(dev_euis[i*2+1]-0x57);
        else temp=temp|(dev_euis[i*2+1]-0x30);
        dev_eui[i]=temp;
    }
}

unsigned int db::charToUint(char ch) {
    unsigned int temp=ch&0x7f;
    temp=temp|((int)ch<0?0x80:0x00);
    return temp;
}



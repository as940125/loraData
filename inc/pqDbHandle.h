//
// Created by hjk on 2018/11/12.
//

#ifndef LORAHANDLBYC_PQDBHANDLE_H
#define LORAHANDLBYC_PQDBHANDLE_H
#include <pqxx/pqxx>
#include <thread>
#include <mutex>
#include <string>
#include <iostream>
using namespace pqxx;
using namespace std;

class dbAPI
{
public:
     dbAPI();
     dbAPI *getDb(string dbname);
     bool  dbSql(string sqlline);
     result dbSqlSelect(string sqlselectline);
private:
};

class pqdb :public dbAPI
{
    public:
         static pqdb * getInstance();
         pqxx::connection dbconnection;
    private:
         pqdb();
         virtual ~pqdb();
         pqxx::connection *dbconnectionp;
         static pqdb *pqdbinstance;
};
#endif //LORAHANDLBYC_PQDBHANDLE_H
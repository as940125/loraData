//
// Created by hjk on 2018/11/12.
//
#include "../inc/pqDbHandle.h"

pqdb * pqdb::pqdbinstance=new pqdb;
dbAPI::dbAPI() {
}
dbAPI* dbAPI::getDb(string dbname) {
    string dbtype1="postgresql";
    string dbtype2="mysql";
    pqdb *pqdb1=pqdb::getInstance();
    if(dbtype1.compare(dbname))
    return pqdb1;
}

bool  dbAPI::dbSql(string sqlline) {
    pqdb *pqdb1=pqdb::getInstance();
    pqxx::work W(pqdb1->dbconnection);
    W.exec(sqlline);
    W.commit();
    return  true;
   // std::cout<<"insert test"<<endl;
}

result dbAPI::dbSqlSelect(string sqlselectline) {
    pqdb *pqdb1=pqdb::getInstance();
    nontransaction N(pqdb1->dbconnection);
    result R(N.exec(sqlselectline));
    return R;
}

pqdb::pqdb():dbconnection("dbname=loraserver user=loraserver password=dbpassword hostaddr=106.14.211.51 port=5432") {
    try  {
        dbconnectionp=new connection("dbname=loraserver user=loraserver password=dbpassword hostaddr=106.14.211.51 port=5432");
        if(dbconnectionp->is_open())
            std::cout<<"db connection Ok:"<<dbconnectionp->dbname()<<endl;
        else
            std::cout<<"db connection Not Ok!"<<std::endl;
    }
    catch (int i)
    {
    }
}

pqdb::~pqdb() {
    dbconnectionp->disconnect();
    dbconnection.disconnect();
    std::cout<<"postgresql disconnect OK!"<<std::endl;
}
pqdb* pqdb::getInstance() {
    std::mutex mtx;
    if (pqdbinstance == NULL)
    {
        mtx.lock();
        if (pqdbinstance == NULL)
        {
            pqdbinstance = new pqdb;
        }
        mtx.unlock();
    }
    return pqdbinstance;
};


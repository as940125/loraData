#include <iostream>
#include "./inc/mqttHandle.h"
#include "./inc/dbHandle.h"
#include "./inc/mainprocess.h"
#include "./inc/jsonHandle.h"
using namespace mqtt;
int main() {
    std::cout << "Hello, World!" << std::endl;
//    db *dbpoint=new db;
//    char data[]={0x01,0x02};
//    dbpoint->dbInsertLightWaringdown("0101010000000015",data,2);
    Process process;
    process.mains();
    std::cout<<"wait!"<<endl;
    while(1) {
    }
    return 0;
}
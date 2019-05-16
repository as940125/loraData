cmake_minimum_required(VERSION 2.8)
project(LoraHandlByC)

set(CMAKE_CXX_STANDARD 11)
SET( CMAKE_CXX_FLAGS "-std=c++11 -O3 -l pthread -l mosquitto -l pq -l pqxx -l jsoncpp -l json_linux-gcc-5.4.0_libmt -g ")
add_executable(LoraHandlByC main.cpp src/mqttHandle.cpp inc/mqttHandle.h src/pqDbHandle.cpp inc/pqDbHandle.h src/dbHandle.cpp inc/dbHandle.h src/mainprocess.cpp inc/mainprocess.h src/transmit.cpp inc/transmit.h src/jsonHandle.cpp inc/jsonHandle.h src/initValue.cpp inc/initValue.h)
target_link_libraries(LoraHandlByC mosquitto pthread pq pqxx jsoncpp json_linux-gcc-5.4.0_libmt)
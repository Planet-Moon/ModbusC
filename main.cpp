#include <iostream>
#include <hello.h>
#include <ModbusDevice.h>
#include <ModbusRegister.h>
#include <SMADevice.h>
#include <SMAStorageBoy.h>
#include <cassert>
#include <chrono>
#include <signal.h>


bool run_test = true;

void signal_handler(int signal)
{
    if(signal != SIGINT){
        return;
    }
    else{
        run_test = false;
        std::cout<<"stopping test"<<std::endl;
    }
}

int main(int argc, char** argv){

    signal(SIGINT, signal_handler);

    hello::hello_world();
    mb::Device heatingControl("192.168.178.107",502);

    bool ret_val = false;

    mb::Register<short> waterTankTop(heatingControl.connection, 2, 0.1, "°C");
    std::cout << "waterTankTop: " + mb::printVector(waterTankTop.readRawData(&ret_val)) + ", status: " << ret_val << std::endl;

    mb::Register<short> waterTankMiddle(heatingControl.connection, 5, 0.1, "°C");
    std::cout << "waterTankMiddle: " + mb::printVector(waterTankMiddle.readRawData(&ret_val)) + ", status: " << ret_val << std::endl;

    mb::Register<float> testRegister(heatingControl.connection, 45, 0.1, "°C");
    std::cout << "testRegister: " << testRegister.getValue(&ret_val) << ", status: "<< ret_val << std::endl;

    testRegister.setValue(float(753));
    float testValue = 3.14156;
    testRegister.setValue(testValue);
    float testValueRet = testRegister.getValue();
    float testDiff = abs(testValueRet - testValue);
    assert(testDiff <= testRegister.factor);

    SMA::StorageBoy storageBoy("192.168.178.113", 502);

    for(int i = 0; i <8000 && run_test; ++i){
        std::cout << i << "-------------------------" << std::endl;
        int test_slaveId = modbus_get_slave(storageBoy.connection);
        storageBoy.testRead();
        volatile int test_power = storageBoy.get_power();
        volatile int test_dcWatt = storageBoy.get_dcWatt();
        volatile unsigned int test_soc = storageBoy.get_soc();
        volatile unsigned int test_dischargeCurrent = storageBoy.get_dischargeCurrent();
        volatile unsigned int test_chargeCurrent = storageBoy.get_chargeCurrent();
        volatile unsigned int test_maxDischargeCurrent = storageBoy.get_maxDischargeCurrent();
        volatile unsigned int test_maxChargeCurrent = storageBoy.get_maxChargeCurrent();
        volatile bool test_online = storageBoy.online;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        std::cout << i << "+++---+++---+++---+++---" << std::endl;
    }

    SMA::Device sunnyBoy("192.168.178.128", 502);

    return 0;
}

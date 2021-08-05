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
    SMA::Device sunnyBoy("192.168.178.128", 502);

    for(int i = 0; i <8000 && run_test; ++i){
        std::cout << i << "-------------------------" << std::endl;
        std::cout << "->sunnyBoy" << std::endl;
        sunnyBoy.testRead();
        volatile int sunnyBoy_slaveId = modbus_get_slave(sunnyBoy.connection);
        volatile int sunnyBoy_power = sunnyBoy.get_power();
        volatile int sunnyBoy_dcWatt = sunnyBoy.get_dcWatt();
        volatile int sunnyBoy_mainsFeedIn = sunnyBoy.get_mainsFeedIn();
        volatile int sunnyBoy_mainsSupply = sunnyBoy.get_mainsSupply();
        volatile bool sunnyBoy_online = sunnyBoy.online;

        std::cout << "->storageBoy" << std::endl;
        storageBoy.testRead();
        volatile int storageBoy_slaveId = modbus_get_slave(storageBoy.connection);
        volatile int storageBoy_power = storageBoy.get_power();
        volatile int storageBoy_dcWatt = storageBoy.get_dcWatt();
        volatile unsigned int storageBoy_soc = storageBoy.get_soc();
        volatile unsigned int storageBoy_dischargeCurrent = storageBoy.get_dischargeCurrent();
        volatile unsigned int storageBoy_chargeCurrent = storageBoy.get_chargeCurrent();
        volatile unsigned int storageBoy_maxDischargeCurrent = storageBoy.get_maxDischargeCurrent();
        volatile unsigned int storageBoy_maxChargeCurrent = storageBoy.get_maxChargeCurrent();
        volatile unsigned int storageBoy_mainsFeedIn = sunnyBoy.get_mainsFeedIn();
        volatile unsigned int storageBoy_mainsSupply = sunnyBoy.get_mainsSupply();
        volatile bool storageBoy_online = storageBoy.online;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        std::cout << i << "+++---+++---+++---+++---" << std::endl;
    }

    return 0;
}

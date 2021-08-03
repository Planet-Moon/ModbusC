#include <iostream>
#include <hello.h>
#include <ModbusDevice.h>
#include <ModbusRegister.h>
#include <SMADevice.h>
#include <SMAStorageBoy.h>
#include <cassert>

int main(int argc, char** argv){
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

    {
        SMA::Device smaDevice("192.168.178.113",502);
        smaDevice.test();
    }
    {
        SMA::StorageBoy storageBoy("192.168.178.113", 502);
        std::cout << "Power: " << storageBoy.get_power() << std::endl;
        std::cout << "DcWatt: " << storageBoy.get_dcWatt() << std::endl;
        std::cout << "SoC: " << storageBoy.get_soc() << std::endl;
        std::cout << "mainsFeedIn: " << storageBoy.get_mainsFeedIn() << std::endl;
        std::cout << "mainsSupply: " << storageBoy.get_mainsSupply() << std::endl;
        int soc_ = storageBoy.soc.getValue();
    }

    SMA::Device sunnyBoy("192.168.178.128", 502);
    return 0;
}

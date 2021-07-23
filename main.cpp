#include <iostream>
#include <hello.h>
#include <ModbusDevice.h>
#include <ModbusRegister.h>
#include <SMADevice.h>
#include <SMAStorageBoy.h>

int main(int argc, char** argv){
    hello::hello_world();
    mb::Device heatingControl("192.168.178.107",502);

    bool ret_val = false;

    mb::Register<float> waterTankTop(heatingControl.connection, 2, 1, 0.1, "°C");
    std::cout << "waterTankTop: " + mb::printVector(waterTankTop.readRawData(&ret_val)) + ", status: " << ret_val << std::endl;

    mb::Register<float> waterTankMiddle(heatingControl.connection, 5, 1, 0.1, "°C");
    std::cout << "waterTankMiddle: " + mb::printVector(waterTankMiddle.readRawData(&ret_val)) + ", status: " << ret_val << std::endl;

    mb::Register<float> testRegister(heatingControl.connection, 45,1,0.1,"°C");
    std::cout << "testRegister: " + mb::printVector(testRegister.readRawData(&ret_val))+", status: "<< ret_val << std::endl;

    SMA::Device smaDevice("192.168.178.113",502);
    smaDevice.test();

    SMA::StorageBoy storageBoy("192.168.178.113", 502);
    std::cout << "Power: " << storageBoy.readPower() << std::endl;
    std::cout << "DcWatt: " << storageBoy.readDcWatt() << std::endl;
    std::cout << "SoC: " << storageBoy.readSoC() << std::endl;
    return 0;
}

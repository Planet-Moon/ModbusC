#include <iostream>
#include "hello.h"
#include "ModbusDevice.h"
#include "SMADevice.h"

int main(int argc, char** argv){
    // hello::hello_world();
    // mbDevice::test_modbus();
    mbDevice::ModbusDevice heatingControl(mbDevice::ModbusDevice("192.168.178.107",502));
    mbDevice::ModbusRegister waterTankTop(mbDevice::ModbusRegister(2,1,0.1,mbDevice::mbDataType::Float,"°C"));
    mbDevice::ModbusRegister waterTankMiddle(mbDevice::ModbusRegister(5,1,0.1,mbDevice::mbDataType::Float,"°C"));
    heatingControl.addRegister("waterTankTop", &waterTankTop);
    heatingControl.addRegister("waterTankMiddle", &waterTankMiddle);

    mbDevice::ModbusRegister testRegister(mbDevice::ModbusRegister(45,1,0.1,mbDevice::mbDataType::Float,"°C"));
    heatingControl.addRegister("testRegister", &testRegister);
    float testRegisterValue;
    heatingControl.writeRegister("testRegister",17);
    heatingControl.readRegister("testRegister",testRegisterValue);
    heatingControl.writeRegister("testRegister",123.4);
    heatingControl.readRegister("testRegister",testRegisterValue);

    // test_device.test_class();
    // test_device.test_all_registers();
    std::vector<uint16_t> waterTankTopRawData(heatingControl.readRegisterRawData("waterTankTop"));
    std::vector<uint16_t> waterTankMiddleRawData(heatingControl.readRegisterRawData("waterTankMiddle"));
    float waterTankTopValue;
    heatingControl.readRegister("waterTankTop",waterTankTopValue);
    float waterTankMiddleValue;
    heatingControl.readRegister("waterTankMiddle",waterTankMiddleValue);
    SMA::SMADevice smaDevice(SMA::SMADevice("192.168.178.113",502));
    return 0;
}

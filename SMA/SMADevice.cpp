#include "SMADevice.h"
#include <iostream>
#include <cassert>
#include <ModbusRegister.h>

#define INIT_DEVICE_REGISTERS \
    deviceInfo(this->connection, 42109), \
    serialNumber(this->connection, 30057), \
    rebootRegister(this->connection, 40077), \
    model(this->connection, 30057), \
    mainsFeedIn(this->connection, 30867, 1, " W"), \
    mainsSupply(this->connection, 30865, 1, " W")

#define GENERATE_MB_GET_FUNC(type, mbRegister) \
    type Device::get_##mbRegister(bool* ret){ \
        return (##mbRegister.getValue(ret)); \
    }

#define GENERATE_MB_SET_FUNC(type, mbRegister) \
    void Device::set_##mbRegister(type input, bool* ret){ \
        ##mbRegister.setValue(input, ret); \
    }


namespace SMA{
    Device::Device(const char* ipAddress, int port):
        mb::Device(ipAddress, port),
        INIT_DEVICE_REGISTERS
    {
        deviceInit();
        return;
    }

    Device::Device(std::string ipAddress, int port) :
        mb::Device(ipAddress, port),
        INIT_DEVICE_REGISTERS
    {
        deviceInit();
        return;
    }

    void Device::deviceInit()
    {
        parseDeviceInfo();
        serialNumber_ = static_cast<unsigned int>(MODBUS_GET_INT32_FROM_INT16(serialNumber.readRawData().data(), 0));
        model_ = static_cast<unsigned int>(MODBUS_GET_INT32_FROM_INT16(model.readRawData().data(), 0));
        return;
    }

    void Device::parseDeviceInfo()
    {
        assert(modbus_set_slave(this->connection, 1) == 0);
        bool valid = false;
        std::vector<uint16_t> return_value = deviceInfo.readRawData(&valid);
        assert(("error reading device info",valid));
        slaveId_ = return_value[3];
        pysicalSusyId_ = static_cast<unsigned short>(return_value[2]);
        pysicalSerialNumber_ = static_cast<unsigned int>(MODBUS_GET_INT32_FROM_INT16(return_value.data(), 0));
        assert(modbus_set_slave(this->connection, slaveId_) == 0);
    }

    GENERATE_MB_GET_FUNC(int, mainsFeedIn);

    GENERATE_MB_GET_FUNC(int, mainsSupply);

    void Device::reboot(){
    }

    void Device::test()
    {
        bool ret_val = false;
        std::cout << "Test output" << std::endl;
        model_ = static_cast<unsigned int>(MODBUS_GET_INT32_FROM_INT16(model.readRawData(&ret_val).data(),0));
        std::cout << "Model: " << model_ << ", valid: "<< ret_val << std::endl;

        return;
    }
}
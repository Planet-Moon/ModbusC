#include "SMADevice.h"
#include <iostream>
#include <cassert>
#include <ModbusRegister.h>

#define INIT_DEVICE_REGISTERS \
    mbDeviceInfo(this->connection, 42109, 4), \
    mbSerialNumber(this->connection, 30057, 2), \
    mbRebootRegister(this->connection, 40077, 2), \
    mbModel(this->connection, 30057, 2), \
    mbMainsFeedIn(this->connection, 30867, 2, 1, " W"), \
    mbMainsSupply(this->connection, 30865, 2, 1, " W")


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
        serialNumber = static_cast<unsigned int>(MODBUS_GET_INT32_FROM_INT16(mbSerialNumber.readRawData().data(), 0));
        model_ = static_cast<unsigned int>(MODBUS_GET_INT32_FROM_INT16(mbModel.readRawData().data(), 0));
        return;
    }

    void Device::parseDeviceInfo()
    {
        assert(modbus_set_slave(this->connection, 1) == 0);
        bool valid = false;
        std::vector<uint16_t> return_value = mbDeviceInfo.readRawData(&valid);
        assert(("error reading device info",valid));
        slaveId_ = return_value[3];
        pysicalSusyId = static_cast<unsigned short>(return_value[2]);
        pysicalSerialNumber = static_cast<unsigned int>(MODBUS_GET_INT32_FROM_INT16(return_value.data(), 0));
        assert(modbus_set_slave(this->connection, slaveId_) == 0);
    }

    void Device::reboot(){
    }

    void Device::test()
    {
        bool ret_val = false;
        std::cout << "Test output" << std::endl;
        model_ = static_cast<unsigned int>(MODBUS_GET_INT32_FROM_INT16(mbModel.readRawData(&ret_val).data(),0));
        std::cout << "Model: " << model_ << ", valid: "<< ret_val << std::endl;

        return;
    }
}
#include "SMADevice.h"
#include <iostream>
#include <cassert>
#include <exception>
#include <ModbusRegister.h>

#define INIT_DEVICE_REGISTERS \
    mbReg_deviceInfo(this, 42109), \
    mbReg_serialNumber(this, 30057), \
    mbReg_rebootRegister(this, 40077), \
    mbReg_model(this, 30057), \
    mbReg_power(this, 30775, 1, " W"), \
    mbReg_dcWatt(this, 30773, 1, " W"), \
    mbReg_mainsFeedIn(this, 30867, 1, " W"), \
    mbReg_mainsSupply(this, 30865, 1, " W")

#define GENERATE_MB_GET_FUNC(type, mbRegister) \
    type Device::get_##mbRegister(bool* ret){ \
        type retval = 0; \
        if(online){ \
            retval = mbReg_##mbRegister.getValue(ret); \
        } \
        return (retval); \
    }

#define GENERATE_MB_SET_FUNC(type, mbRegister) \
    void Device::set_##mbRegister(type input, bool* ret){ \
        if(online){ \
            mbReg_##mbRegister.setValue(input, ret); \
        } \
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
        try {
            parseDeviceInfo();
            online = true;
            bool test{false};
            serialNumber_ = static_cast<unsigned int>(MODBUS_GET_INT32_FROM_INT16(mbReg_serialNumber.readRawData(&test).data(), 0));
            model_ = static_cast<unsigned int>(MODBUS_GET_INT32_FROM_INT16(mbReg_model.readRawData(&test).data(), 0));
            start_thread();
        }
        catch (std::exception& e){
            std::cerr << e.what() << std::endl;
            online = false;
        }
        return;
    }

    void Device::parseDeviceInfo()
    {
        std::runtime_error connection_exception("SMADevice "+ipAddress+":"+std::to_string(port)+ " not reachable");
        if(modbus_set_slave(connection, 1) != 0){
            throw connection_exception;
        }
        bool valid{false};
        std::vector<uint16_t> return_value = mbReg_deviceInfo.readRawData(&valid);
        if(!valid){
            throw connection_exception;
        }
        slaveId_ = return_value[3];
        physicalSusyId_ = static_cast<unsigned short>(return_value[2]);
        physicalSerialNumber_ = static_cast<unsigned int>(MODBUS_GET_INT32_FROM_INT16(return_value.data(), 0));
        if(modbus_set_slave(connection, slaveId_) != 0){
            throw connection_exception;
        }
    }

    unsigned int Device::get_power(bool* ret)
    {
        int temp = 0;
        if(online){
            temp = mbReg_power.getValue(ret);
        }
        if(temp < 0){
            temp = 0;
        }
        return temp;
    }

    unsigned int Device::get_dcWatt(bool* ret)
    {
        int temp = 0;
        if(online){
            temp = mbReg_dcWatt.getValue(ret);
        }
        if(temp < 0)
            temp = 0;
        return temp;
    }

    GENERATE_MB_GET_FUNC(unsigned int, mainsFeedIn);

    GENERATE_MB_GET_FUNC(unsigned int, mainsSupply);

    void Device::reboot(){
        if(online){
            mb::Register<int> reboot(this,40077);
            reboot.setValue(1146);
            online = false;
            stop_thread();
            disconnect();
            while(!online){
                connect(ipAddress.c_str(), port);
            }
            start_thread();
        }
        return;
    }

    void Device::test()
    {
        bool ret_val = false;
        std::cout << "Test output" << std::endl;
        if(online){
            model_ = static_cast<unsigned int>(MODBUS_GET_INT32_FROM_INT16(mbReg_model.readRawData(&ret_val).data(),0));
            std::cout << "Model: " << model_ << ", valid: "<< ret_val << std::endl;
        }
        else{
            std::cout << "not online";
        }
        return;
    }

    bool Device::device_read_all_registers()
    {
        bool result = true;
        power = get_power(&result);
        dcWatt = get_dcWatt(&result);
        mainsFeedIn = get_mainsFeedIn(&result);
        mainsSupply = get_mainsSupply(&result);
        return result;
    }

    bool Device::read_all_registers()
    {
        bool result = true;
        result = result && device_read_all_registers();
        return result;
    }

    void Device::testRead(bool* ret /* = nullptr */)
    {
        std::cout << "online start: " << online << std::endl;
        std::cout << "power: " << get_power(ret) << std::endl;
        std::cout << "dcWatt: " << get_dcWatt(ret) << std::endl;
        std::cout << "mainsFeedIn: " << get_mainsFeedIn(ret) << std::endl;
        std::cout << "mainsSupply: " << get_mainsSupply(ret) << std::endl;
        std::cout << "online end: " << online << std::endl;
    }
}

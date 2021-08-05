#include "SMADevice.h"
#include <iostream>
#include <cassert>
#include <exception>
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
        type retval = 0; \
        if(online){ \
            retval = ##mbRegister.getValue(ret); \
        } \
        return (retval); \
    }

#define GENERATE_MB_SET_FUNC(type, mbRegister) \
    void Device::set_##mbRegister(type input, bool* ret){ \
        if(online){ \
            ##mbRegister.setValue(input, ret); \
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
            serialNumber_ = static_cast<unsigned int>(MODBUS_GET_INT32_FROM_INT16(serialNumber.readRawData(&test).data(), 0));
            model_ = static_cast<unsigned int>(MODBUS_GET_INT32_FROM_INT16(model.readRawData(&test).data(), 0));
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
        if(modbus_set_slave(this->connection, 1) != 0){
            throw connection_exception;
        }
        bool valid{false};
        std::vector<uint16_t> return_value = deviceInfo.readRawData(&valid);
        if(!valid){
            throw connection_exception;
        }
        slaveId_ = return_value[3];
        pysicalSusyId_ = static_cast<unsigned short>(return_value[2]);
        pysicalSerialNumber_ = static_cast<unsigned int>(MODBUS_GET_INT32_FROM_INT16(return_value.data(), 0));
        if(modbus_set_slave(this->connection, slaveId_) != 0){
            throw connection_exception;
        }
    }

    GENERATE_MB_GET_FUNC(int, mainsFeedIn);

    GENERATE_MB_GET_FUNC(int, mainsSupply);

    void Device::reboot(){
        if(online){
            mb::Register<int> reboot(this->connection,40077);
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
            model_ = static_cast<unsigned int>(MODBUS_GET_INT32_FROM_INT16(model.readRawData(&ret_val).data(),0));
            std::cout << "Model: " << model_ << ", valid: "<< ret_val << std::endl;
        }
        else{
            std::cout << "not online";
        }
        return;
    }

    void Device::test_connection()
    {
        unsigned int model_temp = static_cast<unsigned int>(
            MODBUS_GET_INT32_FROM_INT16(
                model.readRawData().data(),
                0
            )
        );
        online = model_temp == model_;
        if(!online){
            throw std::runtime_error("SMADevice "+ipAddress+":"+std::to_string(port)+ " not reachable");
        }
    }
}

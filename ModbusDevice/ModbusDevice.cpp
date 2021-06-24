#include <iostream>
#include <exception>
#include "ModbusDevice.h"

namespace mbDevice{

    ModbusDevice::ModbusDevice(const char* ipAddress_, int port_/*=502*/){
        ipAddress = ipAddress_;
        port = port_;
        mb = modbus_new_tcp(ipAddress_,port_);
        modbus_connect(mb);
    }

    ModbusDevice::ModbusDevice(std::string ipAddress_, int port_/*=502*/){
        ipAddress = ipAddress_;
        port = port_;
        mb = modbus_new_tcp(ipAddress_.c_str(),port_);
        modbus_connect(mb);
    }

    ModbusDevice::~ModbusDevice(){
        modbus_close(mb);
        modbus_free(mb);
    }

    void ModbusDevice::addRegister(std::string name_, int addr_, int nb_, float factor_, mbDataType type_, std::string unit_){
        registers[name_] = ModbusRegister(addr_, nb_, factor_, type_, unit_);
    }

    void ModbusDevice::addRegister(std::string name_, ModbusRegister* mbRegister){
        registers[name_] = *mbRegister;
    }

    std::vector<uint16_t> ModbusDevice::readRegisterRawData(std::string name){
        return registers[name].readRawData(mb);
    }

    void ModbusDevice::readRegister(std::string name, bool &retVal){
        registers[name].read(mb, retVal);
    }

    void ModbusDevice::readRegister(std::string name, int &retVal){
        registers[name].read(mb, retVal);
    }

    void ModbusDevice::readRegister(std::string name, unsigned int &retVal){
        registers[name].read(mb, retVal);
    }

    void ModbusDevice::readRegister(std::string name, float &retVal){
        registers[name].read(mb, retVal);
    }

    void ModbusDevice::writeRegister(std::string name, bool* input){
        registers[name].write(mb, input);
    }

    void ModbusDevice::writeRegister(std::string name, int* input){
        registers[name].write(mb, input);
    }

    void ModbusDevice::writeRegister(std::string name, unsigned int* input){
        registers[name].write(mb, input);
    }

    void ModbusDevice::writeRegister(std::string name, float* input){
        registers[name].write(mb, input);
    }

    void ModbusDevice::writeRegister(std::string name, double* input){
        registers[name].write(mb, input);
    }

        void ModbusDevice::writeRegister(std::string name, bool input){
        registers[name].write(mb, input);
    }

    void ModbusDevice::writeRegister(std::string name, int input){
        registers[name].write(mb, input);
    }

    void ModbusDevice::writeRegister(std::string name, unsigned int input){
        registers[name].write(mb, input);
    }

    void ModbusDevice::writeRegister(std::string name, float input){
        registers[name].write(mb, input);
    }

    void ModbusDevice::writeRegister(std::string name, double input){
        registers[name].write(mb, input);
    }

    void ModbusDevice::test_class(){
        std::cout << "ipAddress: " << ipAddress << std::endl;
        std::cout << "port: " << port << std::endl;
        modbus_read_registers(mb,2,5,tab_reg);
        for(int i=0; i<32; ++i){
            std::cout << "tab_reg[" << i << "]: " << tab_reg[i] << std::endl;
        }
    }

    void ModbusDevice::test_all_registers(){
        for(auto& x: registers){
            auto registerValue = x.second.readRawData(mb);
        }
    }

    void test_modbus(){
        modbus_t *mb;
        uint16_t tab_reg[32] = {0};
        mb = modbus_new_tcp("192.168.178.107",502);
        modbus_connect(mb);
        modbus_read_registers(mb,2,5,tab_reg);
        modbus_close(mb);
        modbus_free(mb);
        for(int i=0; i<32; ++i){
            std::cout << "tab_reg[" << i << "]: " << tab_reg[i] << std::endl;
        }
    }
}

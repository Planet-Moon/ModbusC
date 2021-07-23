#include <iostream>
#include <exception>
#include "ModbusDevice.h"

namespace mb{

    Device::Device(const char* ipAddress_, int port_/*=502*/){
        ipAddress = ipAddress_;
        port = port_;
        connection = modbus_new_tcp(ipAddress_,port_);
        modbus_connect(connection);
    }

    Device::Device(std::string ipAddress_, int port_/*=502*/){
        ipAddress = ipAddress_;
        port = port_;
        connection = modbus_new_tcp(ipAddress_.c_str(),port_);
        if (modbus_connect(connection) == -1) {
            std::cerr << "modbus connection error to ip " + ipAddress + ":" << port_ << std::endl;
            modbus_free(connection);
            connection = nullptr;
        }
    }

    Device::~Device(){
        modbus_close(connection);
        modbus_free(connection);
    }  

    void Device::test_class(){
        std::cout << "ipAddress: " << ipAddress << std::endl;
        std::cout << "port: " << port << std::endl;
        // modbus_read_registers(connection,2,5,tab_reg);
        // for(int i=0; i<32; ++i){
        //     std::cout << "tab_reg[" << i << "]: " << tab_reg[i] << std::endl;
        // }
    }

    void Device::test_all_registers(){
        // for(auto& x: registers){
        //     auto registerValue = x.second.readRawData(connection);
        // }
    }

    void test_modbus(){
        modbus_t *mb;
        uint16_t tab_reg[32] = {0};
        mb = modbus_new_tcp("192.168.178.107",502);
        modbus_connect(mb);
        int read_registers = modbus_read_registers(mb,2,5,tab_reg);
        modbus_close(mb);
        modbus_free(mb);
        for(int i=0; i<32; ++i){
            std::cout << "tab_reg[" << i << "]: " << tab_reg[i] << std::endl;
        }
    }
}

#pragma once
#include <modbus.h>
#include <string>
#include <map>
#include <vector>
#include "../ModbusRegister/ModbusRegister.h"
#include "../ModbusDataTypes.h"

namespace mbDevice{

    class ModbusDevice{
        public:
            //properties
            std::string ipAddress;
            int port;
            //methods
            ModbusDevice(const char* ipAddress, int port = 502);
            ModbusDevice(std::string ipAddress, int port = 502);
            ~ModbusDevice();
            void addRegister(std::string name, int addr, int nb, float factor, mbDataType type, std::string unit);
            void addRegister(std::string name, ModbusRegister* mbRegister);
            std::vector<uint16_t> readRegisterRawData(std::string name);
            void readRegister(std::string name, bool&);
            void readRegister(std::string name, int&);
            void readRegister(std::string name, unsigned int&);
            void readRegister(std::string name, float&);
            void readRegister(std::string name, double&);
            void writeRegister(std::string name, bool*);
            void writeRegister(std::string name, int*);
            void writeRegister(std::string name, unsigned int*);
            void writeRegister(std::string name, float*);
            void writeRegister(std::string name, double*);
            void writeRegister(std::string name, bool);
            void writeRegister(std::string name, int);
            void writeRegister(std::string name, unsigned int);
            void writeRegister(std::string name, float);
            void writeRegister(std::string name, double);
            void test_class();
            void test_all_registers();
            std::map<std::string, ModbusRegister> registers;
        private:
            uint16_t tab_reg[32] = {0};
            modbus_t *mb;
    };

    void test_modbus();
}

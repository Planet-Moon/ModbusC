#pragma once
#include <modbus.h>
#include <string>
#include "stdint.h"
#include <vector>
#include "../ModbusDataTypes.h"

namespace mbDevice{

    class ModbusRegister{
        public:
            int addr;
            int nb;
            float factor;
            mbDataType type;
            std::string unit;
            ModbusRegister();
            ModbusRegister(int addr, int nb=1, float factor=1., mbDataType type=mbDataType::UInt, std::string unit="");
            std::vector<uint16_t> readRawData(modbus_t* mb);
            void read(modbus_t* mb, bool&);
            void read(modbus_t* mb, int&);
            void read(modbus_t* mb, unsigned int&);
            void read(modbus_t* mb, float&);
            void read(modbus_t* mb, double&);
            bool writeRawData(modbus_t* mb, const std::vector<uint16_t>* value);
            bool write(modbus_t* mb, bool*);
            bool write(modbus_t* mb, int*);
            bool write(modbus_t* mb, unsigned int*);
            bool write(modbus_t* mb, float*);
            bool write(modbus_t* mb, double*);
            bool write(modbus_t* mb, bool);
            bool write(modbus_t* mb, int);
            bool write(modbus_t* mb, unsigned int);
            bool write(modbus_t* mb, float);
            bool write(modbus_t* mb, double);

        private:
            std::vector<uint16_t> data;
    };
}

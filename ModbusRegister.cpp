#include "ModbusRegister.h"
#include "Conversions.h"
#include <cmath>

namespace mbDevice{

    ModbusRegister::ModbusRegister(int addr_, int nb_, float factor_, mbDataType type_, std::string unit_){
        addr = addr_;
        nb = nb_;
        factor = factor_;
        type = type_;
        unit = unit_;
        std::vector<uint16_t> data_(nb,0);
        data = data_;
    }

    ModbusRegister::ModbusRegister(){}

    std::vector<uint16_t> ModbusRegister::readRawData(modbus_t* mb){
        modbus_read_registers(mb,addr,nb,data.data());
        return data;
    }

    void ModbusRegister::read(modbus_t* mb, bool& retVal){
        std::vector<uint16_t> rawData(readRawData(mb));
        retVal = static_cast<bool>(rawData[0]);
    }

    void ModbusRegister::read(modbus_t* mb, int& retVal){
        std::vector<uint16_t> rawData(readRawData(mb));
        retVal = convertToInt(rawData);
    }

    void ModbusRegister::read(modbus_t* mb, unsigned int& retVal){
        std::vector<uint16_t> rawData(readRawData(mb));
        retVal = convertToUInt(rawData);
    }

    void ModbusRegister::read(modbus_t* mb, float& retVal){
        std::vector<uint16_t> rawData(readRawData(mb));
        retVal = convertToFloat(rawData)*factor;
    }

    void ModbusRegister::read(modbus_t* mb, double& retVal){
        std::vector<uint16_t> rawData(readRawData(mb));
        retVal = convertToFloat(rawData)*factor;
    }

    bool ModbusRegister::writeRawData(modbus_t* mb, const std::vector<uint16_t>* input){
        return modbus_write_registers(mb,addr,nb,input->data()) >= 0;
    }

    bool ModbusRegister::write(modbus_t* mb, bool* input){
        uint16_t test(static_cast<uint16_t>(*input));
        return modbus_write_registers(mb,addr,nb,&test) >= 0;
    }

    bool ModbusRegister::write(modbus_t* mb, int* input){
        uint16_t test(static_cast<uint16_t>(*input));
        return modbus_write_registers(mb,addr,nb,&test) >= 0;
    }

    bool ModbusRegister::write(modbus_t* mb, unsigned int* input){
        uint16_t test(static_cast<uint16_t>(*input));
        return modbus_write_registers(mb,addr,nb,&test) >= 0;
    }

    bool ModbusRegister::write(modbus_t* mb, float* input){
        uint16_t test(static_cast<uint16_t>(*input/factor));
        return modbus_write_registers(mb,addr,nb,&test) >= 0;
    }

    bool ModbusRegister::write(modbus_t* mb, double* input){
        uint16_t test(static_cast<uint16_t>(*input/factor));
        return modbus_write_registers(mb,addr,nb,&test) >= 0;
    }

    bool ModbusRegister::write(modbus_t* mb, bool input){
        uint16_t test(static_cast<uint16_t>(input));
        return modbus_write_registers(mb,addr,nb,&test) >= 0;
    }

    bool ModbusRegister::write(modbus_t* mb, int input){
        uint16_t test(static_cast<uint16_t>(input));
        return modbus_write_registers(mb,addr,nb,&test) >= 0;
    }

    bool ModbusRegister::write(modbus_t* mb, unsigned int input){
        uint16_t test(static_cast<uint16_t>(input));
        return modbus_write_registers(mb,addr,nb,&test) >= 0;
    }

    bool ModbusRegister::write(modbus_t* mb, float input){
        uint16_t test(static_cast<uint16_t>(round(input/factor)));
        return modbus_write_registers(mb,addr,nb,&test) >= 0;
    }

    bool ModbusRegister::write(modbus_t* mb, double input){
        uint16_t test(static_cast<uint16_t>(round(input/factor)));
        return modbus_write_registers(mb,addr,nb,&test) >= 0;
    }
}

#include "SMADevice.h"

namespace SMA{

    void InitRegisters(SMADevice* smaDevice){
        smaDevice->registers["SUSyIDMode"] = mbDevice::ModbusRegister(30003,2);
        smaDevice->registers["SerialNumber"] = mbDevice::ModbusRegister(30057,2);
        smaDevice->registers["FirmwareVersion"] = mbDevice::ModbusRegister(40063,2);
    }

    SMADevice::SMADevice(const char* ipAddress, int port):
        mbDevice::ModbusDevice(ipAddress,port)
    {
        InitRegisters(this);
    }

    SMADevice::SMADevice(std::string ipAddress, int port):
        mbDevice::ModbusDevice(ipAddress,port)
    {
        InitRegisters(this);
    }

    void SMADevice::reboot(){
       mbDevice::ModbusRegister rebootRegister(mbDevice::ModbusRegister(40077,2));
    }
}
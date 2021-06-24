#pragma once
#include "../ModbusDevice/ModbusDevice.h"

namespace SMA{
    class SMADevice: public mbDevice::ModbusDevice{
        public:
            SMADevice(const char* ipAddress, int port = 502);
            SMADevice(std::string ipAddress, int port = 502);
            void reboot();
    };
}
#pragma once
#include "../ModbusDevice/ModbusDevice.h"
#include "../ModbusRegister/ModbusRegister.h"

namespace SMA{
    class Device: public mb::Device{
        // function
        public:
            Device(const char* ipAddress, int port = 502);
            Device(std::string ipAddress, int port = 502);
            void reboot();
            void test();

        private:
            void deviceInit();
            void parseDeviceInfo();

        // properties
        public:
            unsigned int serialNumber{ 0 };

        private:
            short slaveId_{ 3 };
            unsigned short pysicalSusyId{ 0 };
            unsigned int pysicalSerialNumber{ 0 };
            unsigned int model_{ 0 };
            mb::Register<long long> mbDeviceInfo;
            mb::Register<long> mbSerialNumber;
            mb::Register<int> mbModel;
            mb::Register<long> mbRebootRegister;
    };
}

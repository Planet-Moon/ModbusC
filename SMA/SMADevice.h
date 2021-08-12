#pragma once
#include <ModbusDevice.h>
#include <ModbusRegister.h>

namespace SMA
{
    class Device : public mb::Device
    {
        // function
    public:
        Device(const char *ipAddress, int port = 502);
        Device(std::string ipAddress, int port = 502);
        void reboot();
        void test();

        int get_power(bool *ret = nullptr);
        int get_dcWatt(bool *ret = nullptr);
        int get_mainsFeedIn(bool *ret = nullptr);
        int get_mainsSupply(bool *ret = nullptr);

        void testRead(bool *ret = nullptr);

    private:
        void deviceInit();
        void parseDeviceInfo();

        // properties
    public:
        unsigned int serialNumber_{0};

    private:
        short slaveId_{3};
        unsigned short pysicalSusyId_{0};
        unsigned int pysicalSerialNumber_{0};
        unsigned int model_{0};
        mb::Register<long long> deviceInfo;
        mb::Register<unsigned int> serialNumber;
        mb::Register<int> model;
        mb::Register<int> rebootRegister;
        mb::Register<int> power;
        mb::Register<int> dcWatt;
        mb::Register<int> mainsFeedIn;
        mb::Register<int> mainsSupply;

        void test_connection() override;
    };
}

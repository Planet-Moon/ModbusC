#pragma once
#include <ModbusDevice.h>
#include <ModbusRegister.h>

namespace SMA
{
    class Device : public mb::Device
    {
        // function
    public:
        explicit Device(const char *ipAddress, int port = 502);
        explicit Device(std::string ipAddress, int port = 502);
        Device(const Device &other) = delete;
        ~Device() = default;
        void reboot();
        void test();

        int power{0};
        int dcWatt{0};
        int mainsFeedIn{0};
        int mainsSupply{0};

        int get_power(bool *ret = nullptr);
        int get_dcWatt(bool *ret = nullptr);
        int get_mainsFeedIn(bool *ret = nullptr);
        int get_mainsSupply(bool *ret = nullptr);

        void testRead(bool *ret = nullptr);

        virtual bool device_read_all_registers() final;
        virtual bool read_all_registers() override;

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
        mb::Register<long long> mbReg_deviceInfo;
        mb::Register<unsigned int> mbReg_serialNumber;
        mb::Register<int> mbReg_model;
        mb::Register<int> mbReg_rebootRegister;
        mb::Register<int> mbReg_power;
        mb::Register<int> mbReg_dcWatt;
        mb::Register<int> mbReg_mainsFeedIn;
        mb::Register<int> mbReg_mainsSupply;
    };
}

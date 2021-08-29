#pragma once
#include <Observer.h>
#include <ModbusRegister.h>
#include <map>

namespace SMA{
    class ModbusRelayInterface: public Observer
    {
    public:
        explicit ModbusRelayInterface(std::shared_ptr<mb::Device> mbDeviceIn, std::shared_ptr<mb::Device> mbDeviceOut, unsigned int addressOffset = 0);
        explicit ModbusRelayInterface(unsigned int addressOffset);
        explicit ModbusRelayInterface();
        ModbusRelayInterface(const ModbusRelayInterface&) = delete;
        ~ModbusRelayInterface() = default;
        virtual void update() override;
        virtual void initRegisters();
        unsigned int addressOffset = 0;
        std::map<std::string,mb::Register<unsigned int>> registerMap;
        std::shared_ptr<mb::Device> deviceIn;
        std::shared_ptr<mb::Device> deviceOut;
    };
}
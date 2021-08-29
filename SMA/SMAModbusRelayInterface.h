#pragma once
#include <Observer.h>
#include <ModbusRegister.h>
#include <map>

namespace SMA{
    class ModbusRelayInterface: public Observer
    {
    public:
        explicit ModbusRelayInterface(unsigned int addressOffset);
        explicit ModbusRelayInterface();
        ModbusRelayInterface(const ModbusRelayInterface&) = delete;
        ~ModbusRelayInterface() = default;
        virtual void update() override;
    };
}
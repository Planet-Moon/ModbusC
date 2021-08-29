#pragma once
#include <SMAModbusRelayInterface.h>
#include <SMADevice.h>

namespace SMA{
    class ModbusRelayDevice : public ModbusRelayInterface
    {
        public:
            explicit ModbusRelayDevice(std::shared_ptr<Device> deviceIn, std::shared_ptr<mb::Device> deviceOut, unsigned int addressOffset = 0);
            ModbusRelayDevice(const ModbusRelayDevice& other) = delete;
            ~ModbusRelayDevice() = default;
            virtual void update() override;
            mb::Register<unsigned int>registerPower;
            mb::Register<unsigned int>registerDcWatt;
            std::shared_ptr<Device> deviceIn;
    };
}
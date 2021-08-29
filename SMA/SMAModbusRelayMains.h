#pragma once
#include <SMAModbusRelayInterface.h>
#include <SMADevice.h>

namespace SMA{
    class ModbusRelayMains : public ModbusRelayInterface
    {
        public:
            explicit ModbusRelayMains(std::shared_ptr<Device> deviceIn, std::shared_ptr<mb::Device> deviceOut, unsigned int addressOffset = 0);
            ModbusRelayMains(const ModbusRelayMains& other) = delete;
            ~ModbusRelayMains() = default;
            virtual void update() override;
            mb::Register<unsigned int> registerMainsFeedIn;
            mb::Register<unsigned int> registerMainsSupply;
            std::shared_ptr<Device> deviceIn;
            void mains_update();

        private:
            unsigned int _mainsFeedIn_old;
            unsigned int _mainsSupply_old;
    };
}
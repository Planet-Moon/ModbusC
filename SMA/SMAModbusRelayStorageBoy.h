#pragma once
#include <SMAModbusRelayInterface.h>
#include <SMAStorageBoy.h>

namespace SMA{
    class ModbusRelayStorageBoy : public ModbusRelayInterface
    {
        public:
            explicit ModbusRelayStorageBoy(std::shared_ptr<StorageBoy> deviceIn, std::shared_ptr<mb::Device> deviceOut, unsigned int addressOffset = 0);
            ModbusRelayStorageBoy(const ModbusRelayStorageBoy& other) = delete;
            ~ModbusRelayStorageBoy() = default;
            virtual void update() override;
            mb::Register<unsigned int>registerSoc;
            mb::Register<unsigned int>registerChargeCurrent;
            mb::Register<unsigned int>registerDischargeCurrent;
            std::shared_ptr<StorageBoy> deviceIn;
            void storageBoy_update();

        private:
            unsigned int _soc_old;
            unsigned int _chargeCurrent_old;
            unsigned int _dischargeCurrent_old;
    };
}
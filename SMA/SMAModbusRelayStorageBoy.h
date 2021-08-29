#pragma once
#include <SMAModbusRelayInterface.h>
#include <SMAStorageBoy.h>

namespace SMA{
        /**
         * @brief Modbus relay for StorageBoy values
         *
         * Used to send the values of StorageBoy to another modbus device.
         *
         * Values:
         * - soc
         * - chargeCurrent
         * - dischargeCurrent
         *
         */
    class ModbusRelayStorageBoy : public ModbusRelayInterface
    {
        public:
            /**
             * @brief Construct a new Modbus Relay StorageBoy object
             *
             * @param deviceIn Device the values are read from
             * @param deviceOut Device the values are written to
             * @param addressOffset Register offset of the registers the values are written to
             */
            explicit ModbusRelayStorageBoy(std::shared_ptr<StorageBoy> deviceIn, std::shared_ptr<mb::Device> deviceOut, unsigned int addressOffset = 0);
            ModbusRelayStorageBoy(const ModbusRelayStorageBoy& other) = delete;
            ~ModbusRelayStorageBoy() = default;
            virtual void update() override;
            /// Register where the StorageBoy::soc value will be written to
            mb::Register<unsigned int>registerSoc;
            /// Register where the StorageBoy::chargeCurrent value will be written to
            mb::Register<unsigned int>registerChargeCurrent;
            /// Register where the StorageBoy::dischargeCurrent value will be written to
            mb::Register<unsigned int>registerDischargeCurrent;
            /// StorageBoy the values are read from
            std::shared_ptr<StorageBoy> deviceIn;
            /**
             * @brief Relay the StorageBoy values
             *
             * Gets called by #update
             *
             * Relays:
             * - StorageBoy::soc
             * - StorageBoy::chargeCurrent
             * - StorageBoy::dischargeCurrent
             *
             */
            void storageBoy_update();

        private:
            /// Previously read StorageBoy::soc value
            unsigned int _soc_old;
            /// Previously read StorageBoy::chargeCurrent value
            unsigned int _chargeCurrent_old;
            /// Previously read StorageBoy::dischargeCurrent value
            unsigned int _dischargeCurrent_old;
    };
}
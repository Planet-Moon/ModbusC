#pragma once
#include <SMAModbusRelayInterface.h>
#include <SMADevice.h>

namespace SMA{

    /**
     * @brief Modbus relay for Mains values
     *
     * Used to send the values of mains supply to another modbus device.
     *
     * Values:
     * - Device::mainsFeedIn
     * - Device::mainsSupply
     *
     */
    class ModbusRelayMains : public ModbusRelayInterface
    {
        public:
            /**
             * @brief Construct a new Modbus Relay Mains object
             *
             * @param deviceIn Device the values are read from
             * @param deviceOut Device the values are written to
             * @param addressOffset Register offset of the registers the values are written to
             */
            explicit ModbusRelayMains(std::shared_ptr<Device> deviceIn, std::shared_ptr<mb::Device> deviceOut, unsigned int addressOffset = 0);
            ModbusRelayMains(const ModbusRelayMains& other) = delete;
            ~ModbusRelayMains() = default;
            virtual void update() override;
            /// Register where the Device::mainsFeedIn value will be written to
            mb::Register<unsigned int> registerMainsFeedIn;
            /// Register where the Device::mainsSupply value will be written to
            mb::Register<unsigned int> registerMainsSupply;
            /// Device where the values are read from
            std::shared_ptr<Device> deviceIn;
            /**
             * @brief Relay the mains values
             *
             * Gets called by #update
             *
             * Relays:
             * - Device::mainsFeedIn
             * - Device::mainsSupply
             *
             */
            void mains_update();

        private:
            /// Previously read Device::mainsFeedIn value
            unsigned int _mainsFeedIn_old;
            /// Previously read Device::mainsSupply value
            unsigned int _mainsSupply_old;
    };
}
#pragma once
#include <SMAModbusRelayInterface.h>
#include <SMADevice.h>

namespace SMA{
    /**
     * @brief Modbus relay for SMA::Device
     *
     * Used to send the values of SMA::Device to another modbus device.
     */
    class ModbusRelayDevice : public ModbusRelayInterface
    {
        public:
            /**
             * @brief Construct a new Modbus Relay Device object
             *
             * @param deviceIn Device the values are read from
             * @param deviceOut Device the values are written to
             * @param addressOffset Register offset of the registers the values are written to
             */
            explicit ModbusRelayDevice(std::shared_ptr<Device> deviceIn, std::shared_ptr<mb::Device> deviceOut, unsigned int addressOffset = 0);
            ModbusRelayDevice(const ModbusRelayDevice& other) = delete;
            ~ModbusRelayDevice() = default;
            virtual void update() override;
            /// Register where the Device::power value will be written to
            mb::Register<unsigned int>registerPower;
            /// Register where the Device::dcWatt value will be written to
            mb::Register<unsigned int>registerDcWatt;
            /**
             * @brief Set the power register address
             *
             * @param address
             */
            void set_power_register_address(int address);
            /**
             * @brief Set the dcWatt register address
             *
             * @param address
             */
            void set_dcWatt_register_address(int address);
            /// Device where the values are read from
            std::shared_ptr<Device> deviceIn;
            /**
             * @brief Relay the device values
             *
             * Gets called by #update
             *
             * Relays:
             * - Device::power
             * - Device::dcWatt
             *
             */
            void device_update();

        private:
            /// Previously read Device::power value
            unsigned int _power_old;
            /// Previously read Device::dcWatt value
            unsigned int _dcWatt_old;
    };
}
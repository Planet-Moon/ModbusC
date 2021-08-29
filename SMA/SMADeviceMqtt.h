#pragma once
#include <SMADevice.h>
#include <SMAMqttInterface.h>
#include <chrono>
#include <thread>

namespace SMA {
    /**
     * @brief Interface for a SMA::Device to Mqtt
     *
     */
    class DeviceMqtt: virtual public MqttInterface
    {
    public:
        /**
         * @brief Construct a new Device Mqtt object
         *
         * @param name Name of the device
         * @param device Device object to be interfaced
         * @param client MqttClient to publish values to
         */
        explicit DeviceMqtt(std::string name, std::shared_ptr<Device> device, std::shared_ptr<myMqtt::Client> client);
        DeviceMqtt(const DeviceMqtt& other) = delete;
        ~DeviceMqtt() = default;

        /// Device object to be interfaced
        std::shared_ptr<Device> device;
        /**
         * @brief Publish device values
         *
         * Gets called by #update
         *
         * Publishes:
         * - power
         * - dcWatt
         *
         */
        void device_update();
        void update() override;

    private:
        /// Previously read power value
        unsigned int _power_old;
        /// Previously read dcWatt value
        unsigned int _dcWatt_old;
    };
}

#pragma once
#include <SMADevice.h>
#include <SMAMqttInterface.h>
#include <chrono>
#include <thread>

namespace SMA {
    /**
     * @brief Mains power supply Mqtt interface
     *
     */
    class MainsMqtt: virtual public MqttInterface
    {
    public:
        /**
         * @brief Construct a new Mains Mqtt object
         *
         * @param name Name of Mains object (used in topic)
         * @param device SMADevice to read mains values from
         * @param client MqttClient to publish values
         */
        explicit MainsMqtt(std::string name, std::shared_ptr<Device> device, std::shared_ptr<myMqtt::Client>  client);
        MainsMqtt(const MainsMqtt& other) = delete;
        ~MainsMqtt() = default;
        /**
         * @brief Device object used to read values
         *
         */
        std::shared_ptr<Device> device;
        /**
         * @brief Publish mains values
         *
         * Gets called by #update.
         *
         * Publishes:
         * - SMA::Device::mainsFeedIn
         * - SMA::Device::mainsSupply
         */
        void mains_update();
        void update() override;

    protected:
        /// Previously read mains feed in
        unsigned int _mainsFeedIn_old;
        /// Previously read mains supply
        unsigned int _mainsSupply_old;
    };
}

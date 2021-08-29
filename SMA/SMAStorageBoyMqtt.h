#pragma once
#include <SMAStorageBoy.h>
#include <SMAMqttInterface.h>

namespace SMA {

    /**
     * @brief StorageBoy Mqtt interface
     *
     */
    class StorageBoyMqtt: virtual public MqttInterface
    {
    public:
        /**
         * @brief Construct a new Storage Boy Mqtt object
         *
         * @param name Names of StorageBoy object (used in topic)
         * @param storageBoy StorageBoy to read values from
         * @param client MqttClient to publish values
         */
        explicit StorageBoyMqtt(std::string name, std::shared_ptr<StorageBoy> storageBoy, std::shared_ptr<myMqtt::Client> client);
        StorageBoyMqtt(const StorageBoyMqtt& other) = delete;
        ~StorageBoyMqtt() = default;
        /**
         * @brief storageBoy object
         *
         */
        std::shared_ptr<StorageBoy> storageBoy;
        /**
         * @brief Publish storageBoy values
         *
         * Gets called by #update.
         *
         * Publishes continuously:
         * - soc
         * - dischargeCurrent
         * - chargeCurrent
         *
         * Publishes once:
         * - maxDischargeCurrent
         * - maxChargeCurrent
         *
         */
        void storageboy_update();
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
        /// Previously read mainsFeedIn value
        unsigned int _mainsFeedIn_old;
        /// Previously read mainsSupply value
        unsigned int _mainsSupply_old;
        /// Previously read soc value
        unsigned int _soc_old;
        /// Previously read dischargeCurrent value
        unsigned int _dischargeCurrent_old;
        /// Previously read chargeCurrent value
        unsigned int _chargeCurrent_old;
    };
}

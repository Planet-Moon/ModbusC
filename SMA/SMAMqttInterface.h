#pragma once
#include <MqttClient.h>
#include <Observer.h>


namespace SMA{
    /**
     * @brief Mqtt Interface
     *
     */
    class MqttInterface: public Observer
    {
    public:
        /**
         * @brief Construct a new Mqtt Interface object
         *
         * @param name Name of the device (will be later used in the topic)
         * @param client MqttClient object
         */
        explicit MqttInterface(std::string name, std::shared_ptr<myMqtt::Client> client);
        MqttInterface(const MqttInterface& other) = delete;
        ~MqttInterface() = default;
        /**
         * @brief Mqtt Client object
         *
         * This will be used to publish messages
         */
        std::shared_ptr<myMqtt::Client> client;
        /**
         * @brief Name of the Mqtt device
         *
         */
        std::string name{""};
        /**
         * @brief TopicPrefix (optional)
         *
         */
        std::string topicPrefix{""};

        /**
         * @brief Switch between publish on/off
         *
         * @param send_Status Status to be set to
         */
        virtual void sending(bool send_Status) final;
        virtual void update() override;

    protected:
        /**
         * @brief Flag to enable/disable publish
         *
         */
        bool _send_mqtt{false};
        /**
         * @brief Flag of the first run
         *
         * Used to send constant variables once at the first run
         *
         */
        bool first_run;
        /**
         * @brief Base topic to be published to.
         *
         * Generated from name and TopicPrefix by #update_base_topic.
         *
         */
        std::string base_topic;
        /**
         * @brief Generator of #base_topic
         *
         */
        void update_base_topic();
    };
}

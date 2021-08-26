#pragma once
#include <MqttClient.h>
#include <Observer.h>


namespace SMA{
    class MqttInterface: public Observer
    {
    public:
        explicit MqttInterface(std::string name, std::shared_ptr<myMqtt::Client> client);
        MqttInterface(const MqttInterface& other) = delete;
        ~MqttInterface() = default;
        std::shared_ptr<myMqtt::Client> client;
        std::string name{""};
        std::string topicPrefix{""};

        virtual void sending(bool send_Status) final;
        virtual void update() override;

    protected:
        bool run_thread_task{true};
        bool _send_mqtt{false};
    };
}

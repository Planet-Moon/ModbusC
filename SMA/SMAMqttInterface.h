#pragma once
#include <MqttClient.h>


namespace SMA{
    class MqttInterface
    {
    public:
        explicit MqttInterface(std::string name, std::shared_ptr<myMqtt::Client> client);
        MqttInterface(const MqttInterface& other) = delete;
        ~MqttInterface();
        std::shared_ptr<myMqtt::Client> client;
        std::unique_ptr<std::thread> thread;
        std::chrono::seconds period_time{2};
        std::string name{""};
        std::string topicPrefix{""};

        virtual void sending(bool send_Status) final;
        virtual void thread_task();

    protected:
        bool run_thread_task{true};
        bool _send_mqtt{false};
    };
}

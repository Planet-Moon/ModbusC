#pragma once
#include <MqttClient.h>


namespace SMA{
    class MqttInterface
    {
    public:
        MqttInterface(std::string name, myMqtt::Client* client);
        ~MqttInterface();
        myMqtt::Client* client;
        std::thread* thread;
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
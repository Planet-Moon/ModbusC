#pragma once
#include <SMADevice.h>
#include <MqttClient.h>
#include <chrono>
#include <thread>

namespace SMA {
    class DeviceMqtt: public Device
    {
    public:
        DeviceMqtt(std::string name, const char* ipAddress, myMqtt::Client* client, int port = 502);
        ~DeviceMqtt();
        myMqtt::Client* client = nullptr;
        void device_thread_task();
        std::thread* thread;
        std::chrono::seconds period_time{2};
        void sending(bool send_status);
    private:
        bool run_thread_task{true};

    public:
        int _power;
        int _dcWatt;
        int _mainsFeedIn;
        int _mainsSupply;
        std::string name;
        std::string topicPrefix{""};

    private:
        int __power_old;
        int __dcWatt_old;
        int __mainsFeedIn_old;
        int __mainsSupply_old;
        bool _send_mqtt{false};
    };
}

#pragma once
#include <SMADevice.h>
#include <SMAMqttInterface.h>
#include <chrono>
#include <thread>

namespace SMA {
    class MainsMqtt: virtual public MqttInterface
    {
    public:
        MainsMqtt(std::string name, Device* device, myMqtt::Client* client);
        Device* device;
        void device_thread_task();
        void thread_task() override;

    public:
        int _mainsFeedIn;
        int _mainsSupply;

    protected:
        int _mainsFeedIn_old;
        int _mainsSupply_old;
    };
}

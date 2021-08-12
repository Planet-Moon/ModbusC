#pragma once
#include <SMADevice.h>
#include <SMAMqttInterface.h>
#include <chrono>
#include <thread>

namespace SMA {
    class DeviceMqtt: public MqttInterface
    {
    public:
        DeviceMqtt(std::string name, Device* device, myMqtt::Client* client);
        Device* device;
        void device_thread_task();
        void thread_task() override;

    public:
        int _power;
        int _dcWatt;
        int _mainsFeedIn;
        int _mainsSupply;

    protected:
        int _power_old;
        int _dcWatt_old;
        int _mainsFeedIn_old;
        int _mainsSupply_old;
    };
}

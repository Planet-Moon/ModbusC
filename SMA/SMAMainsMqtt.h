#pragma once
#include <SMADevice.h>
#include <SMAMqttInterface.h>
#include <chrono>
#include <thread>

namespace SMA {
    class MainsMqtt: virtual public MqttInterface
    {
    public:
        explicit MainsMqtt(std::string name, std::shared_ptr<Device> device, std::shared_ptr<myMqtt::Client>  client);
        MainsMqtt(const MainsMqtt& other) = delete;
        ~MainsMqtt() = default;
        std::shared_ptr<Device> device;
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

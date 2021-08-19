#pragma once
#include <SMADevice.h>
#include <SMAMqttInterface.h>
#include <chrono>
#include <thread>

namespace SMA {
    class DeviceMqtt: virtual public MqttInterface
    {
    public:
        explicit DeviceMqtt(std::string name, std::shared_ptr<Device> device, std::shared_ptr<myMqtt::Client> client);
        DeviceMqtt(const DeviceMqtt& other) = delete;
        ~DeviceMqtt() = default;

        std::shared_ptr<Device> device;
        void device_thread_task();
        void thread_task() override;

    public:
        int _power;
        int _dcWatt;

    protected:
        int _power_old;
        int _dcWatt_old;
    };
}

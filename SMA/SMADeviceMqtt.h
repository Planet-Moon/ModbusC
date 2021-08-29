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
        void device_update();
        void update() override;

    private:
        unsigned int _power_old;
        unsigned int _dcWatt_old;
    };
}

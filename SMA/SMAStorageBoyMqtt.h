#pragma once
#include <SMAStorageBoy.h>
#include <SMAMqttInterface.h>

namespace SMA {
    class StorageBoyMqtt: virtual public MqttInterface
    {
    public:
        StorageBoyMqtt(std::string name, StorageBoy* storageBoy, myMqtt::Client* client);
        StorageBoy* storageBoy;
        void storageboy_thread_task();
        void device_thread_task();
        void thread_task() override;

    public:
        int _power;
        int _dcWatt;
        int _mainsFeedIn;
        int _mainsSupply;
        int _soc;
        int _dischargeCurrent;
        int _chargeCurrent;
        int _maxDischargeCurrent;
        int _maxChargeCurrent;

    private:
        int _power_old;
        int _dcWatt_old;
        int _mainsFeedIn_old;
        int _mainsSupply_old;
        int _soc_old;
        int _dischargeCurrent_old;
        int _chargeCurrent_old;
        int _maxDischargeCurrent_old;
        int _maxChargeCurrent_old;
    };
}

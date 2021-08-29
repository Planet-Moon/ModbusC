#include <SMADeviceMqtt.h>
#include <cmath>
#include <cassert>

namespace SMA{
    DeviceMqtt::DeviceMqtt(std::string name_, std::shared_ptr<Device> device_, std::shared_ptr<myMqtt::Client> client_):
        device(device_),
        MqttInterface(name_, client_)
    {
    }

    void DeviceMqtt::device_update()
    {
        if(abs(static_cast<int>(device->power)-static_cast<int>(_power_old))>3 || first_run){
            client->publish(base_topic+"power",std::to_string(device->power),1,true);
            _power_old = device->power;
        }

        if(abs(static_cast<int>(device->dcWatt)-static_cast<int>(_dcWatt_old))>3 || first_run){
            client->publish(base_topic+"dcWatt",std::to_string(device->dcWatt),1,true);
            _dcWatt_old = device->dcWatt;
        }
    }

    void DeviceMqtt::update()
    {
        if(_send_mqtt){
            update_base_topic();
            device_update();
            if(first_run)
                first_run = false;
        }
    }
}

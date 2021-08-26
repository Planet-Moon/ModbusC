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
        if(_send_mqtt){
            std::string base_topic = "";
            if(!topicPrefix.empty()){
                base_topic += topicPrefix+"/";
            }
            base_topic += name+"/";

            bool ret = false;
            _power = device->power;
            _dcWatt = device->dcWatt;

            if(ret){
                if(abs(_power-_power_old)>3){
                    client->publish(base_topic+"power",std::to_string(_power),1,true);
                    _power_old = _power;
                }

                if(abs(_dcWatt-_dcWatt_old)>3){
                    client->publish(base_topic+"dcWatt",std::to_string(_dcWatt),1,true);
                    _dcWatt_old = _dcWatt;
                }
            }
        }
    }

    void DeviceMqtt::update()
    {
        device_update();
    }
}

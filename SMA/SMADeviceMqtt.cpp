#include <SMADeviceMqtt.h>
#include <cmath>
#include <cassert>

namespace SMA{
    DeviceMqtt::DeviceMqtt(std::string name_, Device* device_, myMqtt::Client* client_):
        device(device_),
        MqttInterface(name_, client_)
    {

    }

    void DeviceMqtt::device_thread_task()
    {
        if(_send_mqtt){
            std::string base_topic = "";
            if(!topicPrefix.empty()){
                base_topic += topicPrefix+"/";
            }
            base_topic += name+"/";

            bool ret = false;
            _power = device->get_power(&ret);
            _dcWatt = device->get_dcWatt(&ret);

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

    void DeviceMqtt::thread_task()
    {
        while(run_thread_task)
        {
            device_thread_task();
            std::this_thread::sleep_for(period_time);
        }
        return;
    }
}

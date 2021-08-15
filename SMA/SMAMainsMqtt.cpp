#include <SMAMainsMqtt.h>
#include <cmath>
#include <cassert>

namespace SMA{
    MainsMqtt::MainsMqtt(std::string name_, Device* device_, myMqtt::Client* client_):
        device(device_),
        MqttInterface(name_, client_)
    {

    }

    void MainsMqtt::device_thread_task()
    {
        if(_send_mqtt){
            std::string base_topic = "";
            if(!topicPrefix.empty()){
                base_topic += topicPrefix+"/";
            }
            base_topic += name+"/";

            bool ret = false;
            _mainsFeedIn = device->get_mainsFeedIn(&ret);
            _mainsSupply = device->get_mainsSupply(&ret);

            if(ret){
                if(abs(_mainsFeedIn-_mainsFeedIn_old)>3){
                    client->publish(base_topic+"mainsFeedIn",std::to_string(_mainsFeedIn),1,true);
                    _mainsFeedIn_old = _mainsFeedIn;
                }

                if(abs(_mainsSupply-_mainsSupply_old)>3){
                    client->publish(base_topic+"mainsSupply",std::to_string(_mainsSupply),1,true);
                    _mainsSupply_old = _mainsSupply;
                }
            }
        }
    }

    void MainsMqtt::thread_task()
    {
        while(run_thread_task)
        {
            device_thread_task();
            std::this_thread::sleep_for(period_time);
        }
        return;
    }
}

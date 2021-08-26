#include <SMAMainsMqtt.h>
#include <cmath>
#include <cassert>

namespace SMA{
    MainsMqtt::MainsMqtt(std::string name_, std::shared_ptr<Device> device_, std::shared_ptr<myMqtt::Client> client_):
        device(device_),
        MqttInterface(name_, client_)
    {

    }

    void MainsMqtt::mains_update()
    {
        if(_send_mqtt){
            std::string base_topic = "";
            if(!topicPrefix.empty()){
                base_topic += topicPrefix+"/";
            }
            base_topic += name+"/";

            bool ret = false;
            _mainsFeedIn = device->mainsFeedIn;
            _mainsSupply = device->mainsSupply;

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

    void MainsMqtt::update()
    {
        mains_update();
    }
}

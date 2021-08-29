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
        if(abs(static_cast<int>(device->mainsFeedIn)-static_cast<int>(_mainsFeedIn_old))>3 || first_run){
            client->publish(base_topic+"feedIn",std::to_string(device->mainsFeedIn),1,true);
            _mainsFeedIn_old = device->mainsFeedIn;
        }

        if(abs(static_cast<int>(device->mainsSupply)-static_cast<int>(_mainsSupply_old))>3 || first_run){
            client->publish(base_topic+"supply",std::to_string(device->mainsSupply),1,true);
            _mainsSupply_old = device->mainsSupply;
        }

        const int power_delta{static_cast<int>(device->mainsSupply) - static_cast<int>(device->mainsFeedIn)};
        if(abs(power_delta - _power_delta_old)>3 || first_run){
            client->publish(base_topic+"power_delta",std::to_string(power_delta),1,true);
            _power_delta_old = power_delta;
        }
    }

    void MainsMqtt::update()
    {
        if(_send_mqtt){
            update_base_topic();
            mains_update();
            if(first_run)
                first_run = false;
        }
    }
}

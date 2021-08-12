#include <SMADeviceMqtt.h>
#include <cmath>

namespace SMA{
    DeviceMqtt::DeviceMqtt(std::string name_, const char* ipAddress, myMqtt::Client* client_, int port /* = 502 */):
        name(name_),
        Device(ipAddress, port),
        client(client_)
    {
        bool result;
        thread = new std::thread(&DeviceMqtt::device_thread_task, this);
    }

    DeviceMqtt::~DeviceMqtt()
    {
        run_thread_task = false;
        thread->join();
    }

    void DeviceMqtt::device_thread_task()
    {
        while(run_thread_task)
        {
            if(_send_mqtt){
                std::string base_topic = "";
                if(!topicPrefix.empty()){
                    base_topic += topicPrefix+"/";
                }
                base_topic += name+"/";

                _power = get_power();
                _dcWatt = get_dcWatt();
                _mainsFeedIn = get_mainsFeedIn();
                _mainsSupply = get_mainsSupply();

                if(abs(_power-__power_old)>3){
                    client->publish(base_topic+"power",std::to_string(_power),1,true);
                    __power_old = _power;
                }

                if(abs(_dcWatt-__dcWatt_old)>3){
                    client->publish(base_topic+"dcWatt",std::to_string(_dcWatt),1,true);
                    __dcWatt_old = _dcWatt;
                }

                if(abs(_mainsFeedIn-__mainsFeedIn_old)>3){
                    client->publish(base_topic+"mainsFeedIn",std::to_string(_mainsFeedIn),1,true);
                    __mainsFeedIn_old = _mainsFeedIn;
                }

                if(abs(_mainsSupply-__mainsSupply_old)>3){
                    client->publish(base_topic+"mainsSupply",std::to_string(_mainsSupply),1,true);
                    __mainsSupply_old = _mainsSupply;
                }
            }
            std::this_thread::sleep_for(period_time);
        }
        return;
    }

    void DeviceMqtt::sending(bool send_status)
    {
        _send_mqtt = send_status;
    }
}

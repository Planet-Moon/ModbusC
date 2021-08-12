#include <SMAStorageBoyMqtt.h>
#include <cmath>
#include <cassert>


namespace SMA {
    StorageBoyMqtt::StorageBoyMqtt(std::string name_, StorageBoy* storageBoy_, myMqtt::Client* client_):
        storageBoy(storageBoy_),
        MqttInterface(name_, client_)
    {

    }

    void StorageBoyMqtt::device_thread_task()
    {
        if(_send_mqtt){
            std::string base_topic = "";
            if(!topicPrefix.empty()){
                base_topic += topicPrefix+"/";
            }
            base_topic += name+"/";

            bool ret = false;
            _power = storageBoy->get_power(&ret);
            // assert(ret == true && "error reading power");
            _dcWatt = storageBoy->get_dcWatt(&ret);
            _mainsFeedIn = storageBoy->get_mainsFeedIn(&ret);
            _mainsSupply = storageBoy->get_mainsSupply(&ret);

            if(ret){
                if(abs(_power-_power_old)>3){
                    client->publish(base_topic+"power",std::to_string(_power),1,true);
                    _power_old = _power;
                }

                if(abs(_dcWatt-_dcWatt_old)>3){
                    client->publish(base_topic+"dcWatt",std::to_string(_dcWatt),1,true);
                    _dcWatt_old = _dcWatt;
                }

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

    void StorageBoyMqtt::storageboy_thread_task()
    {
        if(_send_mqtt){
            std::string base_topic = "";
            if(!topicPrefix.empty()){
                base_topic += topicPrefix+"/";
            }
            base_topic += name+"/";

            bool ret = false;
            _soc = storageBoy->get_soc(&ret);
            _dischargeCurrent = storageBoy->get_dischargeCurrent(&ret);
            _chargeCurrent = storageBoy->get_chargeCurrent(&ret);
            _maxDischargeCurrent = storageBoy->get_maxDischargeCurrent(&ret);
            _maxChargeCurrent = storageBoy->get_maxChargeCurrent(&ret);
            // assert("return of modbus false" && ret == true);

            if(ret){
                if(abs(_soc-_soc_old)>3){
                    client->publish(base_topic+"soc",std::to_string(_soc),1,true);
                    _soc_old = _soc;
                }

                if(abs(_dischargeCurrent-_dischargeCurrent_old)>3){
                    client->publish(base_topic+"dischargeCurrent",std::to_string(_dischargeCurrent),1,true);
                    _dischargeCurrent_old = _dischargeCurrent;
                }

                if(abs(_maxDischargeCurrent-_maxDischargeCurrent_old)>3){
                    client->publish(base_topic+"maxDischargeCurrent",std::to_string(_maxDischargeCurrent),1,true);
                    _maxDischargeCurrent_old = _maxDischargeCurrent;
                }

                if(abs(_maxChargeCurrent-_maxChargeCurrent_old)>3){
                    client->publish(base_topic+"mainsSupply",std::to_string(_maxChargeCurrent),1,true);
                    _maxChargeCurrent_old = _maxChargeCurrent;
                }
            }
        }
        return;
    }

    void StorageBoyMqtt::thread_task()
    {
        while(run_thread_task)
        {
            device_thread_task();
            storageboy_thread_task();
            std::this_thread::sleep_for(period_time);
        }
        return;
    }
}
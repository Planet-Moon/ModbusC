#include <SMAStorageBoyMqtt.h>
#include <cmath>
#include <cassert>


namespace SMA {
    StorageBoyMqtt::StorageBoyMqtt(std::string name_, std::shared_ptr<StorageBoy> storageBoy_, std::shared_ptr<myMqtt::Client> client_):
        storageBoy(storageBoy_),
        MqttInterface(name_, client_)
    {

    }

    void StorageBoyMqtt::device_update()
    {
        _power = storageBoy->power;
        _dcWatt = storageBoy->dcWatt;

        if(abs(_power-_power_old)>3 || first_run){
            client->publish(base_topic+"power",std::to_string(_power),1,true);
            _power_old = _power;
        }

        if(abs(_dcWatt-_dcWatt_old)>3 || first_run){
            client->publish(base_topic+"dcWatt",std::to_string(_dcWatt),1,true);
            _dcWatt_old = _dcWatt;
        }
    }

    void StorageBoyMqtt::storageboy_update()
    {
        _soc = storageBoy->soc;
        _dischargeCurrent = storageBoy->dischargeCurrent;
        _chargeCurrent = storageBoy->chargeCurrent;
        _maxDischargeCurrent = storageBoy->maxDischargeCurrent;
        _maxChargeCurrent = storageBoy->maxChargeCurrent;
        // assert("return of modbus false" && ret == true);

        if(abs(_soc-_soc_old)>3 || first_run){
            client->publish(base_topic+"soc",std::to_string(_soc),1,true);
            _soc_old = _soc;
        }

        if(abs(_dischargeCurrent-_dischargeCurrent_old)>3 || first_run){
            client->publish(base_topic+"dischargeCurrent",std::to_string(_dischargeCurrent),1,true);
            _dischargeCurrent_old = _dischargeCurrent;
        }

        if(abs(_maxDischargeCurrent-_maxDischargeCurrent_old)>3 || first_run){
            client->publish(base_topic+"maxDischargeCurrent",std::to_string(_maxDischargeCurrent),1,true);
            _maxDischargeCurrent_old = _maxDischargeCurrent;
        }

        if(abs(_maxChargeCurrent-_maxChargeCurrent_old)>3 || first_run){
            client->publish(base_topic+"maxChargeCurrent",std::to_string(_maxChargeCurrent),1,true);
            _maxChargeCurrent_old = _maxChargeCurrent;
        }
        return;
    }

    void StorageBoyMqtt::update()
    {
        if(_send_mqtt)
        {
            update_base_topic();
            device_update();
            storageboy_update();
            if(first_run)
                first_run = false;
        }
    }
}
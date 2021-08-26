#include <SMAMqttInterface.h>


namespace SMA{
    MqttInterface::MqttInterface(std::string name_,  std::shared_ptr<myMqtt::Client> client_):
        Observer(name_),
        name(name_),
        client(client_)
    {
    }

    void MqttInterface::sending(bool send_status)
    {
        _send_mqtt = send_status;
    }

    void MqttInterface::update()
    {
        return;
    }
}
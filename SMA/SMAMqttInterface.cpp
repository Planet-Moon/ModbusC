#include <SMAMqttInterface.h>


namespace SMA{
    MqttInterface::MqttInterface(std::string name_, myMqtt::Client* client_):
        name(name_),
        client(client_)
    {
        thread = new std::thread(&MqttInterface::thread_task, this);
    }
    MqttInterface::~MqttInterface()
    {
        run_thread_task = false;
        thread->join();
    }

    void MqttInterface::thread_task()
    {
        while(run_thread_task)
        {
            std::this_thread::sleep_for(period_time);
        }
        return;
    }

    void MqttInterface::sending(bool send_status)
    {
        _send_mqtt = send_status;
    }
}
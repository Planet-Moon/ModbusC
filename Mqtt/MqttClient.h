#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <thread>
#include <atomic>
#include <chrono>
#include <cstring>
#include <mqtt/async_client.h>
#include <map>
#include <memory>

namespace myMqtt{
    class action_listener : public virtual mqtt::iaction_listener
    {
    protected:
        void on_failure(const mqtt::token& tok) override;

        void on_success(const mqtt::token& tok) override;
    };

    class Client;
    class callback : public virtual mqtt::callback,
                     public virtual mqtt::iaction_listener
    {
    public:
        callback(Client* cli);
        int nretry_;
        const int N_RETRY_ATTEMPTS{5};
        Client* cli_;

        void reconnect();

        // Re-connection failure
	    void on_failure(const mqtt::token& tok) override;
        void on_success(const mqtt::token& tok) override;
        void connected(const std::string& cause) override;
        void connection_lost(const std::string& cause) override;
        void message_arrived(mqtt::const_message_ptr msg) override;
        void delivery_complete(mqtt::delivery_token_ptr tok) override;

    };

    class delivery_action_listener : public action_listener
    {
        bool done_;
        void on_failure(const mqtt::token& tok) override;
        void on_success(const mqtt::token& tok) override;

    public:
        delivery_action_listener() : done_(false) {}
        bool is_done() const;
    };

    class subTopic{
    public:
        subTopic(action_listener* callbackHandler, int qos = 1);
        subTopic();
        ~subTopic() = default;
        int qos = 1;
        action_listener* callbackHandler;
    };

    class Client{
    public:
        explicit Client(const std::string& serverURI, const std::string& clientURI);
        explicit Client(const Client& other) = delete;
        ~Client();
        void connect(const std::string& serverURI, const std::string& clientURI, mqtt::connect_options connOpts);
        void disconnect();
        void publish(std::string topic, std::string message, int qos = 0, bool retain = false);
        void subscribe(std::string topic, int qos);
        void resubscribeToAll();
        void unsubscribe(std::string topic);
        std::string serverURI;
        std::string clientURI;
        mqtt::connect_options connectOptions;
        std::string lastWillTopic = "lastwill";
        std::string lastWillPayload = "Last will and testament.";
        int lastWillQos = 1;
        int qos = 1;

    private:
        std::unique_ptr<mqtt::async_client> client_ = nullptr;
        callback* cb;
        const std::chrono::seconds TIMEOUT = std::chrono::seconds(10);
        std::map<std::string, int> subscribed_topics;
    };
}

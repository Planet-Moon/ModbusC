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
    /**
     * @brief Callback class
     *
     */
    class action_listener : public virtual mqtt::iaction_listener
    {
    protected:
        void on_failure(const mqtt::token& tok) override;

        void on_success(const mqtt::token& tok) override;
    };

    class Client;
    /**
     * @brief Callback class
     *
     */
    class callback : public virtual mqtt::callback,
                     public virtual mqtt::iaction_listener
    {
    public:
        /**
         * @brief Construct a new callback object
         *
         * @param cli MqttClient object
         */
        callback(Client* cli);
        /// Retry counts
        int nretry_;
        /// Times to retry to reconnect
        const int N_RETRY_ATTEMPTS{5};
        /// MqttClient object
        Client* cli_;

        /**
         *  Try to reconnect to Mqtt broker
         */
        void reconnect();

        void on_failure(const mqtt::token& tok) override;
        void on_success(const mqtt::token& tok) override;
        virtual void connected(const std::string& cause) override;
        /**
         *  This method is called when the connection to the server is lost.
         */
        virtual void connection_lost(const std::string& cause) override;
        /**
         *  This method is called when a message arrives from the server.
         */
        virtual void message_arrived(mqtt::const_message_ptr msg) override;
        /**
         * Called when delivery for a message has been completed, and all
         * acknowledgments have been received.
         */
        virtual void delivery_complete(mqtt::delivery_token_ptr tok) override;

    };

    /**
     * @brief Mqtt client
     *
     */
    class Client{
    public:
        /**
         * @brief Construct a new Client object
         *
         * @param serverURI Mqtt broker address
         * @param clientURI Client name
         */
        explicit Client(const std::string& serverURI, const std::string& clientURI);
        explicit Client(const Client& other) = delete;
        ~Client();
        /**
         * @brief Connect to Mqtt broker
         *
         * @param serverURI Mqtt broker address
         * @param clientURI Client name
         * @param connOpts Connection options object
         */
        void connect(const std::string& serverURI, const std::string& clientURI, mqtt::connect_options connOpts);
        /**
         * @brief Disconnect from Mqtt broker
         *
         */
        void disconnect();
        /**
         * @brief Publish a message
         *
         * @param topic Topic to publish to
         * @param message Message to publish
         * @param qos Qos of the published message
         * @param retain Retain the message (Broker will store the message until a new one is publish on the same topic)
         */
        void publish(std::string topic, std::string message, int qos = 0, bool retain = false);
        /**
         * @brief Subscribe to topic
         *
         * @param topic Topic name
         * @param qos Qos of the messages to be received
         */
        void subscribe(std::string topic, int qos);
        /**
         * @brief Resubscribe to all previously subscribed topics of #subscribed_topics
         *
         */
        void resubscribeToAll();
        /**
         * @brief Unsubscribe from Topic
         *
         * @param topic Topic to unsubscribe
         */
        void unsubscribe(std::string topic);
        /**
         * @brief Mqtt broker address
         *
         */
        std::string serverURI;
        /**
         * @brief Client name (ID)
         *
         */
        std::string clientURI;
        /**
         * @brief Options object for connecting to the broker
         *
         */
        mqtt::connect_options connectOptions;
        /**
         * @brief Last will topic to publish #lastWillPayload to when Client gets disconnected
         *
         */
        std::string lastWillTopic = "lastwill";
        /**
         * @brief Last will message to be published to #lastWillTopic when Client gets disconnected
         *
         */
        std::string lastWillPayload = "Last will and testament.";
        /**
         * @brief Qos of the last will message
         *
         */
        int lastWillQos = 1;

    private:
        /**
         * @brief Async client object
         *
         * Created after connecting
         *
         */
        std::unique_ptr<mqtt::async_client> client_ = nullptr;
        /**
         * @brief Callback object used by #client_
         *
         */
        callback* cb;
        /**
         * @brief Timeout duration after publishing message
         *
         * After this time an error is returned
         *
         */
        const std::chrono::seconds TIMEOUT = std::chrono::seconds(10);
        /**
         * @brief Map of subscribed topics
         *
         * - first: Name
         * - second: Qos
         *
         */
        std::map<std::string, int> subscribed_topics;
    };
}

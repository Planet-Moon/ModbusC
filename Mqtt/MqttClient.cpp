#include <MqttClient.h>


namespace myMqtt {

    callback::callback(Client* cli): nretry_(0), cli_(cli)
    {

    }

    void callback::reconnect()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(2500));
        try {
            cli_->connect(cli_->serverURI,cli_->clientURI,cli_->connectOptions);
        }
        catch (const mqtt::exception& exc) {
            std::cerr << "Error: " << exc.what() << std::endl;
            exit(1);
        }
    }

    void callback::on_failure(const mqtt::token& tok)
    {
        #ifdef DEBUG
        std::cout << "Connection attempt failed" << std::endl;
        #endif // DEBUG
        if (++nretry_ > N_RETRY_ATTEMPTS)
            exit(1);
        reconnect();
    }

    void callback::on_success(const mqtt::token& tok)
    {
        #ifdef DEBUG
        std::cout << "Connection successful" << std::endl;
        #endif // DEBUG
    }

    void callback::connected(const std::string& cause)
    {
        #ifdef DEBUG
        std::cout << "Connection success" << std::endl;
        #endif // DEBUG
    }

    void callback::connection_lost(const std::string& cause)
    {
        #ifdef DEBUG
        std::cout << "\nConnection lost" << std::endl;
        #endif // DEBUG
        if (!cause.empty())
        {
            #ifdef DEBUG
            std::cout << "\tcause: " << cause << std::endl;
            #endif // DEBUG
        }
    }

    void callback::message_arrived(mqtt::const_message_ptr msg)
    {
        #ifdef DEBUG
        std::cout << "Message arrived topic: "+msg->get_topic()+", payload: "+msg->to_string()<< ", qos: " << msg->get_qos() << ", retain: " << msg->is_retained() << std::endl;
        #endif // DEBUG
    }

    void callback::delivery_complete(mqtt::delivery_token_ptr tok)
    {
        #ifdef DEBUG
        std::cout << "\tDelivery complete for token: " << (tok ? tok->get_message_id() : -1) << std::endl;
        #endif // DEBUG
    }



    void action_listener::on_failure(const mqtt::token& tok)
    {
        #ifdef DEBUG
        std::cout << "\tListener failure for token: " << tok.get_message_id() << std::endl;
        #endif // DEBUG
    }

    void action_listener::on_success(const mqtt::token& tok)
    {
        #ifdef DEBUG
        std::cout << "\tListener success for token: " << tok.get_message_id() << std::endl;
        #endif // DEBUG
    }

    Client::Client(const std::string& serverURI, const std::string& clientURI)
    {
        connectOptions = mqtt::connect_options_builder()
            .clean_session(false)
            .will(mqtt::message(lastWillTopic.c_str(), lastWillPayload.c_str(), lastWillQos))
            .finalize();
        connect(serverURI, clientURI, connectOptions);
    }

    void Client::connect(const std::string& serverURI_, const std::string& clientURI_, mqtt::connect_options connOpts)
    {
        if(client_)
            client_.reset();
        serverURI = serverURI_;
        clientURI = clientURI_;
        client_ = std::make_unique<mqtt::async_client>(serverURI, clientURI);
        cb = new callback(this);
        client_->set_callback(*cb);
        mqtt::token_ptr conntok = client_->connect(connOpts);
        #ifdef DEBUG
        std::cout << "Waiting for the connection..." << std::endl;
        #endif // DEBUG
        conntok->wait();
        #ifdef DEBUG
        std::cout << "  ...OK" << std::endl;
        #endif // DEBUG
    }

    void Client::publish(std::string topic, std::string message, int qos /* = 0 */, bool retain /* = false */)
    {
        #ifdef DEBUG
        std::cout << "Sending message {\"topic\":\""+topic+"\",\"message\":\""+message+"\", \"qos\":"<<qos<<", \"retain\":"<<retain<<"}" << std::endl;
        #endif // DEBUG
        mqtt::message_ptr pubmsg = mqtt::make_message(topic.c_str(), message.c_str(), qos, retain);
        mqtt::delivery_token_ptr pubtok = client_->publish(pubmsg);
        int message_id = pubtok->get_message_id();
        size_t message_size = pubtok->get_message()->get_payload().size();
        pubtok->wait_for(TIMEOUT);
        #ifdef DEBUG
        std::cout << "\t...OK" << std::endl;
        #endif // DEBUG
    }

    void Client::disconnect()
    {
        #ifdef DEBUG
        std::cout << "\nDisconnecting..." << std::endl;
        #endif // DEBUG
        client_->disconnect()->wait();
        #ifdef DEBUG
        std::cout << "  ...OK" << std::endl;
        #endif // DEBUG
    }

    void Client::subscribe(std::string topic, int qos)
    {
        auto result = subscribed_topics.find(topic);
        if(result == subscribed_topics.end())
        {
            #if DEBUG
            std::cout << "Subscribing to topic '" << topic << "'\n\tfor client " << clientURI << " using QoS" << qos << std::endl;
            #endif // DEBUG
            client_->subscribe(topic.c_str(), qos, nullptr, *cb)->wait();
            subscribed_topics[topic] = qos;
        }
    }

    void Client::resubscribeToAll()
    {
        for(auto& topic : subscribed_topics)
        {
            client_->subscribe(topic.first.c_str(), topic.second, nullptr, *cb)->wait();
        }
    }

    void Client::unsubscribe(std::string topic)
    {
        auto result = subscribed_topics.find(topic);
        if(result != subscribed_topics.end())
        {
            client_->unsubscribe(topic.c_str())->wait();
            subscribed_topics.erase(result);
        }
    }

    Client::~Client()
    {
        disconnect();
        client_.reset();
    }
}

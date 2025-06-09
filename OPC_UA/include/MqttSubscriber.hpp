#pragma once 
#include "../include/OpcUaServer.hpp"
#include <mqtt/async_client.h>
#include <mqtt/callback.h>
#include <mqtt/connect_options.h>
#include <mqtt/message.h>
#include <open62541/server.h>
#include <nlohmann/json.hpp>
#include <string>

using namespace std;
class OpcUaServer;

class MqttSubscriber : public virtual mqtt::callback {

    public:
        MqttSubscriber(const string&address, const string clientId, OpcUaServer* opcServer );
        void start();
        void message_arrived(mqtt::const_message_ptr msg)override;
        
    private:
        mqtt::async_client client;
        mqtt::connect_options connOpts;
        OpcUaServer* opcServer;
};


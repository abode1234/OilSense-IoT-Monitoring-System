#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <mqtt/async_client.h>

using json = nlohmann::json;

class MqttClient {
    
public:
    MqttClient(const std::string& serverAddress, const std::string& clientId, const std::string& topic) ;
    bool connect();
    bool publishData(const json& msg);
    void disconnect();
private:
    std::string m_topic;
    mqtt::async_client m_client;
    mqtt::connect_options m_connOpts;

}; 

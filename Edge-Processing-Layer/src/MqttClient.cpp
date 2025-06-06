#include "../include/MqttClient.hpp"
#include <iostream>
#include <chrono>
#include <thread>

MqttClient::MqttClient(const std::string& serverAddress, const std::string& clientId, const std::string& topic)
    : m_client(serverAddress, clientId), m_topic(topic)
{
    m_connOpts.set_clean_session(true);
}

bool MqttClient::connect() {
    int attempts = 0;
    const int maxAttempts = 5;
    while (attempts < maxAttempts) {
        try {
            std::cout << "Connecting to MQTT Broker..." << std::endl;
            m_client.connect(m_connOpts)->wait();
            std::cout << "Connected." << std::endl;
            return true;
        }
        catch (const mqtt::exception& e) {
            std::cerr << "Connection failed: " << e.what() << std::endl;
            attempts++;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
    return false;
}

void MqttClient::disconnect() {
    try {
        m_client.disconnect()->wait();
        std::cout << "Disconnected from MQTT Broker." << std::endl;
    }
    catch (const mqtt::exception& e) {
        std::cerr << "Disconnect failed: " << e.what() << std::endl;
    }
}

bool MqttClient::publishData(const json& message) {
    try {
        std::string payload = message.dump();
        auto pubmsg = mqtt::make_message(m_topic, payload);
        pubmsg->set_qos(1);
        m_client.publish(pubmsg)->wait_for(std::chrono::seconds(10));
        std::cout << "Published: " << payload << std::endl;
        return true;
    }
    catch (const mqtt::exception& e) {
        std::cerr << "Publish failed: " << e.what() << std::endl;
        return false;
    }
}


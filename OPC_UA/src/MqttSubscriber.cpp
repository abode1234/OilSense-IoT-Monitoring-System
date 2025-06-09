#include "../include/MqttSubscriber.hpp"
#include "../include/MqttSubscriber.hpp"
#include <chrono>
#include <iostream>
#include <mqtt/exception.h>
#include <thread>

using namespace std;

MqttSubscriber::MqttSubscriber(const string&address, const string clientId, OpcUaServer* opcServer )
:client(address, clientId), opcServer(opcServer) {
   
    client.set_callback(*this);
    connOpts.set_clean_session(true);
}


void MqttSubscriber::start() {
    try {
        client.connect(connOpts)->wait();
        client.subscribe("oilSense/sensors", 1)->wait();
        while (true) {
            this_thread::sleep_for(chrono::seconds(1));
        
        }
    } catch (const mqtt::exception& e) {
            cerr << "MQTT connection error: " << e.what();
    }
}

void MqttSubscriber::message_arrived(mqtt::const_message_ptr msg) {
    try {
        auto data = nlohmann::json::parse(msg->get_payload());
        if (data.contains("temperature"))
            opcServer->uopdateVariable("temperature", data["temperature"].get<double>());
        if (data.contains("pressure"))
            opcServer->uopdateVariable("pressure", data["pressure"].get<double>());
        if (data.contains("vibration"))
            opcServer->uopdateVariable("vibration", data["vibration"].get<double>());
        if (data.contains("energy_consumption"))
            opcServer->uopdateVariable("energy_consumption", data["energy_consumption"].get<double>());
        std::cout << "OPC-UA variables updated from MQTT." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "MQTT message parsing error: " << e.what() << std::endl;
    }
}








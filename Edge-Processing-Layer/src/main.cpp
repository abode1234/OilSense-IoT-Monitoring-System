#include <iostream>
#include <thread>
#include <chrono>

#include "../include/jsonReader.hpp"
#include "../include/MqttClient.hpp"

int main() {
    const std::string filename = "data.json";
    const std::string serverAddress = "tcp://localhost:1883";
    const std::string clientId = "EdgeProcessorClient";
    const std::string topic = "oilSense/sensors";

    JsonReader reader(filename);
    std::vector<nlohmann::json> data = reader.readAll();
    if (data.empty()) {
        std::cerr << "No data to publish." << std::endl;
        return 1;
    }

    MqttClient mqttClient(serverAddress, clientId, topic);
    if (!mqttClient.connect()) {
        std::cerr << "Failed to connect to MQTT Broker." << std::endl;
        return 1;
    }

    for (const auto& item : data) {
        mqttClient.publishData(item);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    mqttClient.disconnect();

    return 0;
}


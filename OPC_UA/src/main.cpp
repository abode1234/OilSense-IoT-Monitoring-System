#include "../include/OpcUaServer.hpp"
#include "../include/MqttSubscriber.hpp"

int main() {

    OpcUaServer opcServer;
    opcServer.addVariable();


    MqttSubscriber mqttSub("tcp://localhost:1883", "OPCUA_MQTT_Subscriber", &opcServer);

    std::thread mqttThread(&MqttSubscriber::start, &mqttSub);

    opcServer.run();

    mqttThread.join();

    return 0;
}


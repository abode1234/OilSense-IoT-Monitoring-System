#pragma once
#include <mutex>
#include <open62541/server.h>

class OpcUaServer {

    public:
        OpcUaServer();
        ~OpcUaServer();

        void addVariable();
         void uopdateVariable(const std::string& name, double value);
        void run();

    private:
    UA_Server *server;
    UA_ServerConfig *config;
    std::mutex serverMutex;
};

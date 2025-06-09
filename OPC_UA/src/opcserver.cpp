#include "../include/OpcUaServer.hpp"
#include <mutex>
#include <open62541/server_config_default.h>
#include <open62541/plugin/log_stdout.h>
#include <open62541/server.h>
#include <iostream>
#include <open62541/types.h>



OpcUaServer::OpcUaServer() {
  server = UA_Server_new();
  config = UA_Server_getConfig(server);
    
}

OpcUaServer::~OpcUaServer() {
    UA_Server_delete(server);
}

void OpcUaServer::addVariable() {
 UA_Server* server = this->server;
    struct {
        const char *name;
        double initialValue ;
    } vars[] = {
        {"pressure", 0},
        {"temperature", 0},
        {"vibration", 0},
        {"energy_consumption", 0}
    };
    
    for (auto& v : vars) {
        UA_NodeId nodeId = UA_NODEID_STRING(1, const_cast<char*>(v.name));
        UA_VariableAttributes attr = UA_VariableAttributes_default;
        UA_Variant_setScalar(&attr.value, &v.initialValue, &UA_TYPES[UA_TYPES_DOUBLE]);
        attr.description = UA_LOCALIZEDTEXT("en-US", const_cast<char*>(v.name));
        attr.displayName = UA_LOCALIZEDTEXT("en-US", const_cast<char*>(v.name));
        attr.dataType = UA_TYPES[UA_TYPES_DOUBLE].typeId;

        UA_Server_addVariableNode(server, nodeId,
            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
            UA_QUALIFIEDNAME(1, const_cast<char*>(v.name)),
            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
            attr, nullptr, nullptr);
    }
}


void OpcUaServer::uopdateVariable(const std::string& name, double value) {
    
 std::lock_guard<std::mutex> lock(serverMutex);
    UA_Variant var;
    UA_Variant_setScalar(&var, &value, &UA_TYPES[UA_TYPES_DOUBLE]);

    UA_StatusCode status = UA_Server_writeValue(server, UA_NODEID_STRING(1, const_cast<char*>(name.c_str())), var);

    
    if (status != UA_STATUSCODE_GOOD)
        std::cerr << "Failed to update OPC-UA variable: " << name << std::endl;
}



void OpcUaServer::run() {

    UA_Boolean running = true;
        UA_StatusCode status = UA_Server_run(server, &running);
        if (status != UA_STATUSCODE_GOOD)
            std::cerr << "Failed to run OPC-UA server: " << status << std::endl;
        else
            std::cout << "OPC-UA server is running." << std::endl;
}


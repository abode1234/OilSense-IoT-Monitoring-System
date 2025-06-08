#include <open62541/server.h>
#include <open62541/server_config_default.h>
#include <open62541/plugin/log_stdout.h>

static void addVariable(UA_Server *server) {
    UA_NodeId currentNodeId = UA_NODEID_STRING(1, const_cast<char*>("temperature"));
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    double initialValue = 25.0;
    UA_Variant_setScalar(&attr.value, &initialValue, &UA_TYPES[UA_TYPES_DOUBLE]);
    char locale[] = "en-US";
    char text[] = "Temperature";

    attr.description = UA_LOCALIZEDTEXT(locale, text);
    attr.displayName = UA_LOCALIZEDTEXT(locale, text);

    attr.dataType = UA_TYPES[UA_TYPES_DOUBLE].typeId;
    UA_Server_addVariableNode(server, currentNodeId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                              UA_QUALIFIEDNAME(1, const_cast<char*>("Temperature")),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                              attr, nullptr, nullptr);
}

int main() {
    UA_Server *server = UA_Server_new();
    UA_ServerConfig_setDefault(UA_Server_getConfig(server));
    addVariable(server);

    UA_Boolean running = true;
    UA_StatusCode status = UA_Server_run(server, &running);
    UA_Server_delete(server);
    return status == UA_STATUSCODE_GOOD ? 0 : 1;
}


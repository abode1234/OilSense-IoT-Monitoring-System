#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class JsonReader {
public:
    explicit JsonReader(const std::string& filename);
    std::vector<json> readAll();

private:
    std::string m_filename;
};


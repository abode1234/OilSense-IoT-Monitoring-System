#include "../include/jsonReader.hpp"
#include <fstream>
#include <iostream>

JsonReader::JsonReader(const std::string& filename) : m_filename(filename) {}

std::vector<json> JsonReader::readAll() {
    std::ifstream file(m_filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << m_filename << std::endl;
        return {};
    }

    json dataArray;
    file >> dataArray;

    if (!dataArray.is_array()) {
        std::cerr << "JSON root is not an array." << std::endl;
        return {};
    }

    std::vector<json> result;
    for (const auto& item : dataArray) {
        result.push_back(item);
    }

    return result;
}


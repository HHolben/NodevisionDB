#include "GraphDB.hpp"
#include <algorithm>

// Node operations
void GraphDB::createNode(int id, const std::string& path, const std::string& type) {
    nodes[id] = {id, path, type};
}

void GraphDB::deleteNode(int id) {
    nodes.erase(id);
}

void GraphDB::editNode(int id, const std::string& newPath, const std::string& newType) {
    if (nodes.find(id) != nodes.end()) {
        nodes[id].path = newPath;
        nodes[id].type = newType;
    }
}

// Edge operations
void GraphDB::createEdge(int source, int target, const std::string& type) {
    edges.push_back({source, target, type});
}

void GraphDB::deleteEdge(int source, int target) {
    edges.erase(std::remove_if(edges.begin(), edges.end(),
                   [&](const Edge& e) { return e.source == source && e.target == target; }),
                edges.end());
}

// Graph persistence
void GraphDB::saveGraph() {
    json j;
    for (const auto& [id, node] : nodes) {
        j["nodes"].push_back({{"id", node.id}, {"path", node.path}, {"type", node.type}});
    }
    for (const auto& edge : edges) {
        j["edges"].push_back({{"source", edge.source}, {"target", edge.target}, {"type", edge.type}});
    }
    std::ofstream file(jsonFile);
    file << j.dump(4);
}

void GraphDB::loadGraph() {
    std::ifstream file(jsonFile);
    if (!file) return;
    json j;
    file >> j;
    for (auto& node : j["nodes"]) {
        createNode(node["id"], node["path"], node["type"]);
    }
    for (auto& edge : j["edges"]) {
        createEdge(edge["source"], edge["target"], edge["type"]);
    }
}

// Table persistence
void GraphDB::saveTable(const std::vector<std::vector<std::string>>& tableData) {
    std::ofstream file(csvFile);
    for (const auto& row : tableData) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) file << ",";
        }
        file << "\n";
    }
}

std::vector<std::vector<std::string>> GraphDB::loadTable() {
    std::vector<std::vector<std::string>> tableData;
    std::ifstream file(csvFile);
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        tableData.push_back(row);
    }
    return tableData;
}

// Object operations
void GraphDB::createObject(const CustomObject& obj) {
    objects[obj.id] = obj;
    saveObject(obj);
}

void GraphDB::deleteObject(int id) {
    objects.erase(id);
    std::string filename = "objects/object_" + std::to_string(id) + ".json";
    std::remove(filename.c_str());
}

void GraphDB::editObject(int id, const std::string& newName, const std::string& newDescription) {
    if (objects.find(id) != objects.end()) {
        objects[id].name = newName;
        objects[id].description = newDescription;
        saveObject(objects[id]);
    }
}

void GraphDB::saveObject(const CustomObject& obj) {
    std::string filename = "objects/object_" + std::to_string(obj.id) + ".json";
    std::ofstream file(filename);
    if (file.is_open()) {
        json j = obj;
        file << j.dump(4);
        file.close();
    } else {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
    }
}

CustomObject GraphDB::loadObject(int id) {
    std::string filename = "objects/object_" + std::to_string(id) + ".json";
    std::ifstream file(filename);
    if (file.is_open()) {
        json j;
        file >> j;
        file.close();
        return j.get<CustomObject>();
    } else {
        std::cerr << "Unable to open file for reading: " << filename << std::endl;
        return {};
    }
}

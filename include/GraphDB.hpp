#ifndef NODEVISION_DB_HPP
#define NODEVISION_DB_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <cstdio>  // for std::remove
#include "json.hpp"  // nlohmann JSON

using json = nlohmann::json;

// Structure for a Node (file)
struct Node {
    int id;
    std::string path;
    std::string type;
};

// Structure for an Edge (link)
struct Edge {
    int source;
    int target;
    std::string type;
};

// Structure for a Custom Object
struct CustomObject {
    int id;
    std::string name;
    std::string description;
};

// JSON serialization for CustomObject
inline void to_json(json& j, const CustomObject& obj) {
    j = json{{"id", obj.id}, {"name", obj.name}, {"description", obj.description}};
}

inline void from_json(const json& j, CustomObject& obj) {
    j.at("id").get_to(obj.id);
    j.at("name").get_to(obj.name);
    j.at("description").get_to(obj.description);
}

// Graph Database Class
class GraphDB {
private:
    std::unordered_map<int, Node> nodes;
    std::vector<Edge> edges;
    std::unordered_map<int, CustomObject> objects;
    std::string jsonFile = "graph.json";
    std::string csvFile = "tables.csv";  // Now defined

public:
    // Node operations
    void createNode(int id, const std::string& path, const std::string& type);
    void deleteNode(int id);
    void editNode(int id, const std::string& newPath, const std::string& newType);

    // Edge operations
    void createEdge(int source, int target, const std::string& type);
    void deleteEdge(int source, int target);

    // Graph persistence
    void saveGraph();
    void loadGraph();

    // Table persistence
    void saveTable(const std::vector<std::vector<std::string>>& tableData);
    std::vector<std::vector<std::string>> loadTable();

    // Object operations
    void createObject(const CustomObject& obj);
    void deleteObject(int id);
    void editObject(int id, const std::string& newName, const std::string& newDescription);
    void saveObject(const CustomObject& obj);
    CustomObject loadObject(int id);
};

#endif // NODEVISION_DB_HPP

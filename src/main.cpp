#include "GraphDB.hpp"

int main() {
    GraphDB db;
    db.createNode(1, "notes/idea.md", "markdown");
    db.createEdge(1, 2, "internal");
    db.saveGraph();
    
    std::vector<std::vector<std::string>> table = {{"ID", "Name", "Type"}, {"1", "Idea", "Markdown"}};
    db.saveTable(table);
    
    CustomObject obj1{1, "Sample Object", "This is a sample object."};
    db.createObject(obj1);
    
    return 0;
}

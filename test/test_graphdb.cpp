#include "GraphDB.hpp"
#include <gtest/gtest.h>

class GraphDBTest : public ::testing::Test {
protected:
    GraphDB db;

    void SetUp() override {
        db.createNode(1, "notes/idea.md", "markdown");
        db.createNode(2, "notes/project.txt", "text");
        db.createEdge(1, 2, "internal");
    }
};

TEST_F(GraphDBTest, SaveAndLoadGraph) {
    db.saveGraph();
    GraphDB db2;
    db2.loadGraph();
    
    // Here you would compare expected node/edge counts, etc.
    // (For example purposes, this is just a placeholder test.)
    SUCCEED();
}

TEST_F(GraphDBTest, SaveAndLoadTable) {
    std::vector<std::vector<std::string>> table = {{"ID", "Name"}, {"1", "Idea"}, {"2", "Project"}};
    db.saveTable(table);

    auto loadedTable = db.loadTable();
    EXPECT_EQ(loadedTable.size(), table.size());
}

TEST_F(GraphDBTest, SaveAndLoadObject) {
    CustomObject obj1{1, "Sample Object", "Test object"};
    db.saveObject(obj1);
    
    CustomObject loadedObj = db.loadObject(1);
    EXPECT_EQ(loadedObj.id, 1);
    EXPECT_EQ(loadedObj.name, "Sample Object");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

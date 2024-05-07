/*
Test data is located in tests/data/
tests_1.json - Two films, no relation.
tests_2.json - One film, no data.
tests_3.json - Five films, eight actors/directors, some relations.
tests_4.json - see tests_4_dijkstra_paths.txt for more info.
tests_non_english.json - Some relations, with foreign languages (for parsing).

*/
#include "../cs225/catch/catch.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../graph.h"
#include "../BFS.h"
#include "../BFS.cpp"

using namespace std;

NetflixGraph test1("tests/data/tests_1.json");
NetflixGraph test2("tests/data/tests_2.json");
NetflixGraph test3("tests/data/tests_3.json");
//NetflixGraph test5("tests/data/tests_5.json");
NetflixGraph nonenglish("tests/data/tests_non_english.json");

NetflixGraph test4("tests/data/tests_4.json");


TEST_CASE("Correct amount of vertices (actors) are made", "[deserialize]") {
    REQUIRE(test1.getVertices().size() == 4);
    REQUIRE(test2.getVertices().size() == 0);
    REQUIRE(test3.getVertices().size() == 8);
    //REQUIRE(test5.getVertices().size() == 2);
}

TEST_CASE("deserialize() parses foreign languages", "[deserialize]") {
    REQUIRE(nonenglish.getVertices().size() == 18);
}

TEST_CASE("Correct amount of edges (relations) are made", "[deserialize]") {
    REQUIRE(test1.getEdges().size() == 2);
    REQUIRE(test2.getEdges().size() == 0);
    REQUIRE(test4.getEdges().size() == 10);
    // REQUIRE(test5.getEdges().size() == 4);
}

TEST_CASE("Dijkstra path greater than 1", "[dijkstra]") {
    const string a1 = "Al Capone", a2 = "Claude Monet";
    vector<string> path = test3.dijkstra(a1, a2);
    REQUIRE(path.size() == 2);
    REQUIRE(path == vector<string>{"Red", "Green"});
}

TEST_CASE("Dijkstra path length 1", "[dijskstra]") {
    const string a1 = "Matthew Novelli", a2 = "Adam Urish";
    vector<string> path = test1.dijkstra(a1, a2);
    REQUIRE(path.size() == 1);
    REQUIRE(path == vector<string>{"Coders"});
}

TEST_CASE("Dijkstra no path between 2 valid actors", "[dijkstra]") {
    const string a1 = "Jason Zou", a2 = "Adam Urish";
    vector<string> path = test1.dijkstra(a1, a2);
    REQUIRE(path.size() == 0);
    REQUIRE(path == vector<string>());
}

TEST_CASE("Dijkstra one actor is not in the data set", "[dijkstra]") {
    const string a1 = "Jeff Kim", a2 = "Raising Canes";
    vector<string> path = test1.dijkstra(a1, a2);
    REQUIRE(path.size() == 0);
    REQUIRE(path == vector<string>());
}

TEST_CASE("Dijkstra both actors are not in the data set", "[dijkstra]") {
    const string a1 = "Doge Coin", a2 = "Raising Canes";
    vector<string> path = nonenglish.dijkstra(a1, a2);
    REQUIRE(path.size() == 0);
    REQUIRE(path == vector<string>());
}

TEST_CASE("Dijkstra non-english", "[dijkstra]") {
    const string a1 = "СУКА БЛЯДЬ", a2 = "Maëlle";
    vector<string> path = nonenglish.dijkstra(a1, a2);
    REQUIRE(path.size() == 2);
    REQUIRE(path == vector<string>{"СУКА", "Jäger"});
}

TEST_CASE("All_paths returns the correct amount of paths", "[all_paths]") {
    vector<vector<string>> vanceMatt = test1.findpaths("Vance Ursiny", "Matthew Novelli", -1);
    vector<vector<string>> vanceJason = test1.findpaths("Vance Ursiny", "Jason Zou", -1);
    vector<vector<string>> jerry = test3.findpaths("Jerry Seinfeld", "Claude Monet", -1);
    REQUIRE(vanceMatt.size() == 0);
    REQUIRE(vanceJason.size() == 1);
    REQUIRE(jerry.size() == 3);
}
TEST_CASE("All_paths handles blank inputs", "[all_paths]") {
    vector<vector<string>> blank = test2.findpaths("", "", -1);
    REQUIRE(blank.size() == 0);
}

TEST_CASE("All_paths handles actors not in the dataset", "[all_paths]") {
    vector<vector<string>> wildgoosechase = test3.findpaths("Gungo", "Bopulous", -1);
    REQUIRE(wildgoosechase.size() == 0);
}
TEST_CASE("All_paths handles one actor not in the dataset", "[all_paths]") {
    vector<vector<string>> wildgoosechase = test3.findpaths("Carl Evans", "Bopulous", -1);
    REQUIRE(wildgoosechase.size() == 0);
}
TEST_CASE("All_paths returns a complex amount of paths", "[all_paths]") {
    vector<vector<string>> complex = test4.findpaths("8", "1", -1);
    vector<vector<string>> complex2 = test4.findpaths("8", "6", -1);

    REQUIRE(complex.size() == 4);    
    REQUIRE(complex2.size() == 6);
}

TEST_CASE("Test operator++ on sample.json", "[traversal]") {
    NetflixGraph testn("data/sample.json");
    vector<NetflixGraph::GraphEdge*> edges=testn.getEdges();
    vector<NetflixGraph::GraphVertex*> vertices=testn.getVertices();

    if(vertices.size()!=0)
    {
        NetflixGraph::GraphVertex* start=vertices[0];
        BFS bfs(testn, start);
        int count=0;
        for(BFS::Iterator i=bfs.begin(); i!=bfs.end(); ++i)
        {
            count++;
        }
        int size=(int)(vertices.size());
        REQUIRE(count==size);
    }
}

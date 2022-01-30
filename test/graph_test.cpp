#include <catch2/catch_test_macros.hpp>
#include "../shared.h"

TEST_CASE("graph class test", "[graph]") {
    SECTION("empty-graph", "") {
        graph g;
        REQUIRE(g.size == 0);
    }
    SECTION("graph-constructor", "") {
        int n = 3;
        std::vector<std::pair<int, int> > edges;
        std::vector<std::pair<double, double> > positions;
        edges.push_back({0, 1});
        edges.push_back({1, 2});
        positions.push_back({0, 0});
        positions.push_back({0, 1});
        positions.push_back({0, 2});
        graph g(n, edges, positions);
        REQUIRE(g.size == 3);
        REQUIRE(g.edges.size() == 2);
        REQUIRE(g.positions.size() == 3);
        for (int i = 0; i < edges.size(); i++)
            REQUIRE(g.edges[i] == edges[i]);
        for (int i = 0; i < positions.size(); i++)
            REQUIRE(g.positions[i] == positions[i]);
        
        graph g2(g);
        REQUIRE(g.size == g2.size);
        REQUIRE(g.edges.size() == g.edges.size());
        REQUIRE(g.positions.size() == g.positions.size());
        for (int i = 0; i < g.edges.size(); i++)
            REQUIRE(g.edges[i] == g2.edges[i]);
        for (int i = 0; i < g.positions.size(); i++)
            REQUIRE(g.positions[i] == g2.positions[i]);
    }
    SECTION("graph-edges-positions", "") {
        graph g;
        REQUIRE(g.edges.size() == 0);
        REQUIRE(g.positions.size() == 0);
        g.setEdges({
            {0, 1}, 
            {1, 2}
        });
        REQUIRE(g.edges.size() == 2);
        g.setPositions({
            {0, 0},
            {0, 1},
            {0, 2}
        });
        REQUIRE(g.positions.size() == 3);
    }
    SECTION("graph-neighbours") {
        graph g(
            3,
            {
                {0, 1}, 
                {1, 2}
            },
            {
                {0, 0},
                {0, 1},
                {0, 2}
            }
        );
        std::vector<char> vec = g.getNeighbours(0);
        REQUIRE(vec.size() == 3);
        REQUIRE(vec[0] == 0);
        REQUIRE(vec[1] == 1);
        REQUIRE(vec[2] == 0);
    }
}
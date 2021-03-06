#include <catch2/catch_test_macros.hpp>
#include "../shared.h"
#include "../graphIO.h"
#include <sstream>

TEST_CASE("graph class test", "[graph]") {
    SECTION("empty-graph", "") {
        graph g;
        REQUIRE(g.size == 0);
    }
    SECTION("graph-constructor", "") {
        int n = 3;
        std::vector<std::pair<int, int> > edges;
        std::vector<std::pair<double, double> > positions;
        edges.push_back({ 0, 1 });
        edges.push_back({ 1, 2 });
        positions.push_back({ 0, 0 });
        positions.push_back({ 0, 1 });
        positions.push_back({ 0, 2 });
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

TEST_CASE("graph io test", "[graph-io]") {
    SECTION("read_normal without positions", "") {
        std::istringstream str("3 2\n0 1\n1 2\n");
        graph g = graphIO::read_graph(str, false, false);
        REQUIRE(g.size == 3);
        REQUIRE(g.positions.size() == 0);
        REQUIRE(g.edges.size() == 2);
        REQUIRE(g.edges[0].first == 0);
        REQUIRE(g.edges[0].second == 1);
        REQUIRE(g.edges[1].first == 1);
        REQUIRE(g.edges[1].second == 2);
    }
    SECTION("read_normal with positions", "") {
        std::istringstream str("3 2\n0 0 0\n1 0 1\n2 0 2\n0 1\n1 2\n");
        graph g = graphIO::read_graph(str, false, true);
        REQUIRE(g.size == 3);
        REQUIRE(g.positions.size() == 3);
        REQUIRE(g.positions[0].first == 0);
        REQUIRE(g.positions[0].second == 0);
        REQUIRE(g.positions[1].first == 0);
        REQUIRE(g.positions[1].second == 1);
        REQUIRE(g.positions[2].first == 0);
        REQUIRE(g.positions[2].second == 2);
        REQUIRE(g.edges.size() == 2);
        REQUIRE(g.edges[0].first == 0);
        REQUIRE(g.edges[0].second == 1);
        REQUIRE(g.edges[1].first == 1);
        REQUIRE(g.edges[1].second == 2);
    }
    SECTION("read_json without positions", "") {
        std::istringstream str(
            "{\"edges\": [[0, 1], [1, 2]],"
            "\"size\": 3}"
        );
        graph g = graphIO::read_graph(str, true, false);
        REQUIRE(g.size == 3);
        REQUIRE(g.positions.size() == 0);
        REQUIRE(g.edges.size() == 2);
        REQUIRE(g.edges[0].first == 0);
        REQUIRE(g.edges[0].second == 1);
        REQUIRE(g.edges[1].first == 1);
        REQUIRE(g.edges[1].second == 2);
    }
    SECTION("read_json with positions", "") {
        std::istringstream str(
            "{\"edges\": [[0, 1], [1, 2]],"
            "\"size\": 3,"
            "\"positions\": [[0, 0], [0, 1], [0, 2]]}"
        );
        graph g = graphIO::read_graph(str, true, true);
        REQUIRE(g.size == 3);
        REQUIRE(g.positions.size() == 3);
        REQUIRE(g.positions[0].first == 0);
        REQUIRE(g.positions[0].second == 0);
        REQUIRE(g.positions[1].first == 0);
        REQUIRE(g.positions[1].second == 1);
        REQUIRE(g.positions[2].first == 0);
        REQUIRE(g.positions[2].second == 2);
        REQUIRE(g.edges.size() == 2);
        REQUIRE(g.edges[0].first == 0);
        REQUIRE(g.edges[0].second == 1);
        REQUIRE(g.edges[1].first == 1);
        REQUIRE(g.edges[1].second == 2);
    }
    SECTION("write_normal", "") {
        std::istringstream str1("3 2\n0 0 0\n1 0 1\n2 0 2\n0 1\n1 2\n");
        graph g = graphIO::read_graph(str1, false, true);
        std::ostringstream str2("");
        graphIO::write_graph(str2, g, "normal");
        REQUIRE("3 2\n0 0 0\n1 0 1\n2 0 2\n" == str2.str());
    }
    SECTION("write_json", "") {
        std::istringstream str1("3 2\n0 0 0\n1 0 1\n2 0 2\n0 1\n1 2\n");
        graph g = graphIO::read_graph(str1, false, true);
        std::ostringstream str2("");
        graphIO::write_graph(str2, g, "json");
        const char* res = R"({
    "edges": [
        [
            0,
            1
        ],
        [
            1,
            2
        ]
    ],
    "positions": [
        [
            0.0,
            0.0
        ],
        [
            0.0,
            1.0
        ],
        [
            0.0,
            2.0
        ]
    ],
    "size": 3
}
)";
        REQUIRE(res == str2.str());
    }
    SECTION("write_tikz", "") {
        std::istringstream str1("3 2\n0 0 0\n1 0 1\n2 0 2\n0 1\n1 2\n");
        graph g = graphIO::read_graph(str1, false, true);
        std::ostringstream str2("");
        graphIO::write_graph(str2, g, "tikz");
        const char* res = R"(\documentclass[border=5mm]{standalone}
\usepackage[utf8]{inputenc}
\usepackage{tikz}
\begin{document}
\begin{tikzpicture}
\begin{scope}[every node/.style={circle,thick,draw}]
\node (0) at (0, 0) {0};
\node (1) at (0, 20) {1};
\node (2) at (0, 40) {2};
\end{scope}

\begin{scope}[every node/.style={fill=white,circle}, every edge/.style={draw=red,very thick}]
\draw [-] (0) -- (1);
\draw [-] (1) -- (2);
\end{scope}
\end{tikzpicture}
\end{document}
)";
        REQUIRE(res == str2.str());
    }
}
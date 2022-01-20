#pragma once
#include <vector>
#include <cstddef>
#include <random>

/* better randomization */

int getRand(int x);
double getRand01();

const int INF = 1e9 + 1337;

enum OutType: unsigned short {
    normal_t = 1,
    json_t = 2,
    tikz_t = 4
};

class graph {
    public:
    std::vector<std::pair<int, int>> edges;
    std::vector<std::pair<double,double>> positions;
    
    size_t size;

    graph();
    graph(size_t, const std::vector<std::pair<int, int>>&, const std::vector<std::pair<double,double>>&);
    graph(const graph&);

    void setEdges(const std::vector<std::pair<int, int>>&);
    void setPositions(const std::vector<std::pair<double, double>>&);
    void setRandomPositions();
    std::vector<char> getNeighbours(int v);
};

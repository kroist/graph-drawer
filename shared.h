#pragma once
#include <vector>

class graph {
    public:
    std::vector<std::pair<int, int>> mem;
    std::vector<std::pair<double,double>> positions;
    size_t size;

    graph();
    graph(size_t, const std::vector<std::pair<int, int>>&, const std::vector<std::pair<double,double>>&);
    graph(const graph&);

    void setMem(const std::vector<std::pair<int, int>>&);
    void setPositions(const std::vector<std::pair<double, double>>&);


};
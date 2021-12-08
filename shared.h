#pragma once
#include <vector>

class graph {
    public:
    std::vector<std::pair<int, int>> mem;
    std::vector<std::pair<double,double>> positions;
    size_t size;

    graph(size_t = 0, std::vector<std::pair<int, int>> = {}, std::vector<std::pair<double,double>> = {});
    graph(const graph&);
};
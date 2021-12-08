#include "shared.h"

graph::graph(size_t size, std::vector<std::pair<int, int>> mem, std::vector<std::pair<double,double>> positions) {
    this->mem = mem;
    this->size = size;
    this->positions = positions;
}

graph::graph(const graph& rhs) {
    this->mem = rhs.mem;
    this->size = rhs.size;
    this->positions = positions;
}

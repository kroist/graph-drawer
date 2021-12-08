#include "shared.h"

graph::graph() {
    size = 0;
}

graph::graph(size_t size, const std::vector<std::pair<int, int>>& mem, const std::vector<std::pair<double,double>>& positions) {
    this->mem = mem;
    this->size = size;
    this->positions = positions;
}

graph::graph(const graph& rhs) {
    this->mem = rhs.mem;
    this->size = rhs.size;
    this->positions = positions;
}

void graph::setMem(const std::vector<std::pair<int, int>>& mem) {
    this->mem = mem;
}

void graph::setPositions(const std::vector<std::pair<double, double>>& positions) {
    this->positions = positions;
}

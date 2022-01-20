#include "shared.h"

graph::graph() {
    size = 0;
}

graph::graph(size_t size, const std::vector<std::pair<int, int>>& edges, const std::vector<std::pair<double,double>>& positions) {
    this->edges = edges;
    this->size = size;
    this->positions = positions;
}

graph::graph(const graph& rhs) {
    this->edges = rhs.edges;
    this->size = rhs.size;
    this->positions = positions;
}

void graph::setEdges(const std::vector<std::pair<int, int>>& edges) {
    this->edges = edges;
}

void graph::setPositions(const std::vector<std::pair<double, double>>& positions) {
    this->positions = positions;
}

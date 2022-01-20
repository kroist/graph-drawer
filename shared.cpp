#include "shared.h"

std::mt19937 my_rnd(time(nullptr));
// return random number from [0, x)
int getRand(int x) {
    return my_rnd() % x;
}

double getRand01() {
    return getRand(INF + 1) / (double)INF;
}

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
    this->positions = rhs.positions;
}

void graph::setEdges(const std::vector<std::pair<int, int>>& edges) {
    this->edges = edges;
}

void graph::setPositions(const std::vector<std::pair<double, double>>& positions) {
    this->positions = positions;
}

void graph::setRandomPositions() {
    for(int i = 0; i < this->size; i++) {
        this->positions[i] = { getRand01(), getRand01() }; 
    }
}

std::vector<char> graph::getNeighbours(const int v) {
    std::vector<char> is_neighbour(this->size, 0);
    for (int i = 0; i < this->edges.size(); i++) {
        if (this->edges[i].first == v)
            is_neighbour[this->edges[i].second] = 1;
        if (this->edges[i].second == v)
            is_neighbour[this->edges[i].first] = 1;
    }
    return is_neighbour;
}

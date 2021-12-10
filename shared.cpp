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

graph::graph(size_t size, const std::vector<std::pair<int, int>>& mem, const std::vector<std::pair<double,double>>& positions) {
    this->mem = mem;
    this->size = size;
    this->positions = positions;
}

graph::graph(const graph& rhs) {
    this->mem = rhs.mem;
    this->size = rhs.size;
    this->positions = rhs.positions;
}

void graph::setMem(const std::vector<std::pair<int, int>>& mem) {
    this->mem = mem;
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
    for (int i = 0; i < this->mem.size(); i++) {
        if (this->mem[i].first == v)
            is_neighbour[this->mem[i].second] = 1;
        if (this->mem[i].second == v)
            is_neighbour[this->mem[i].first] = 1;
    }
    return is_neighbour;
}

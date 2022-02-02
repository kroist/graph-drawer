#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>

#include "algo.h"
#include <omp.h>

const double cRep = 2;
const double cSpring = 10;
const double sLen = 1;

const int MAXRAND = 1000;
const int ITER = 10000;
const double rate = 0.0001;

const double EPS = 1e-6;

struct pnt {
    double x, y;
    pnt() {}
    pnt(double _x, double _y): x(_x), y(_y) {}
    pnt(std::pair<double, double> pr): x(pr.first), y(pr.second) {}
};

double dist(pnt a, pnt b) {
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );
}

pnt vec(pnt a, pnt b) {
    pnt res;
    res.x = b.x-a.x;
    res.y = b.y-a.y;
    return res;
}

double fRep(pnt a, pnt b) {
    return cRep / (dist(a, b));
}

double fSpring(pnt a, pnt b) {
    return cSpring * std::log(dist(a, b)/sLen);
}

pnt displacement(int v, int n, graph& g) {
    pnt res;
    res.x = res.y = 0;

    /* get neigbours of v */
    auto is_neighbour = g.getNeighbours(v);

    for (int i = 0; i < n; i++) {
        if (i == v)
            continue;
        if (is_neighbour[i] == 1) {
            double k = fSpring(pnt(g.positions[i]), pnt(g.positions[v]));
            pnt cur = vec(pnt(g.positions[v]), pnt(g.positions[i]));
            res.x += cur.x*k;
            res.y += cur.y*k;
        }
        else {
            double k = fRep(pnt(g.positions[i]), pnt(g.positions[v]));
            pnt cur = vec(pnt(g.positions[i]), pnt(g.positions[v]));
            res.x += cur.x*k;
            res.y += cur.y*k;
        }
    }
    return res;
}

pnt get_projection(pnt a, pnt b, pnt p){
    pnt ap(p.x - a.x, p.y - a.y);
    pnt ab(b.x - a.x, b.y - a.y);
    double cf = (ap.x * ab.x + ap.y * ab.y) / (ab.x * ab.x + ab.y * ab.y);
    return pnt(a.x + ab.x * cf, a.y + ab.y * cf);
}

bool infit(pnt a, pnt b, pnt p){
    return (p.x >= std::min(a.x, b.x) && p.x <= std::max(a.x, b.x)) && (p.y >= std::min(a.y, b.y) && p.y <= std::max(a.y, b.y));
}

pnt edge_displacement(int v, int n, graph& g){
    pnt res;
    res.x = res.y = 0;

    for (auto edge : g.edges){
        if (edge.first == v || edge.second == v)continue;
        pnt proj = get_projection(g.positions[edge.first], g.positions[edge.second], g.positions[v]);
        if (!infit(g.positions[edge.first], g.positions[edge.second], proj))continue;
        double k = fRep(proj, pnt(g.positions[v]));
        pnt cur = vec(proj, pnt(g.positions[v]));
        res.x += cur.x*k;
        res.y += cur.y*k;
    }
    return res;
}

double area(const pnt& a, const pnt& b, const pnt& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool intersect_1(double a, double b, double c, double d) {
    if (a > b) std::swap(a, b);
    if (c > d) std::swap(c, d);
    return std::min(a, c) <= std::min(b, d);
}

bool intersect(const pnt& a, const pnt& b, const pnt& c, const pnt& d) {
    return intersect_1(a.x, b.x, c.x, d.x) && intersect_1(a.y, b.y, c.y, d.y)
        && area(a, b, c) * area(a, b, d) < EPS && area(c, d, a) * area(c, d, b) < EPS;
}

void algo::applySprings(graph& g, int iterations) {
    int n = g.size;
    std::vector<pnt> dsp(n);
    std::vector<pnt> edge_dsp(n);
    for (int iter = 0; iter < iterations; iter++) {
        #pragma omp parallel for num_threads(8)
        for (int i = 0; i < n; i++) {
            dsp[i] = displacement(i, n, g);
            edge_dsp[i] = edge_displacement(i, n, g);
        }
        #pragma omp parallel for num_threads(8)
        for (int i = 0; i < n; i++) {
            g.positions[i].first += rate*dsp[i].x;
            g.positions[i].second += rate*dsp[i].y;

            g.positions[i].first += rate * edge_dsp[i].x;
            g.positions[i].second += rate * edge_dsp[i].y;
        }
    }
}

int getIntersectionNumber(const graph& g) {
    int result = 0;
    for (int i = 0; i < g.edges.size(); i++) {
        for (int j = i + 1; j < g.edges.size(); j++) {
            result += intersect(pnt(g.positions[g.edges[i].first]), pnt(g.positions[g.edges[i].second]), 
            pnt(g.positions[g.edges[j].first]), pnt(g.positions[g.edges[j].second]));
        }
    }
    return result;
}

graph intersectionTransform(graph g) {
    int n = g.size;
    while (true) {
        /* init new positions */
        auto new_positions = g.positions;
        /* flag to check if points are converged */
        bool is_converged = true;
        for (int v = 0; v < n; v++) {
            /* get neigbours of v */
            auto is_neighbour = g.getNeighbours(v);
            int number_of_neighbours = 0;
            /* init by zeros */
            new_positions[v] = {0, 0};
            for (int u = 0; u < n; u++) {
                if (is_neighbour[u]) {
                    new_positions[v].first += g.positions[u].first;
                    new_positions[v].second += g.positions[u].second;
                    number_of_neighbours++;
                }
            }
            /* TODO: handle 0 */
            if (number_of_neighbours > 0) {
                new_positions[v].first /= (double)number_of_neighbours;
                new_positions[v].second /= (double)number_of_neighbours;
                if (abs(new_positions[v].first - g.positions[v].first) > EPS) {
                    is_converged = false;
                } else if (abs(new_positions[v].second - g.positions[v].second) > EPS) {
                    is_converged = false;
                }
            }
        }
        /* update to new positions */
        g.positions = new_positions;
        /* break condition */
        if (is_converged) {
            break;
        }
    }
    return g;
}

void algo::applyIntersections(graph& g, int max_iterations) {
    bool stop_flag = false;
    int iterations = 0, answer = INF;
    graph answer_g;
    for(int it = 0; it < max_iterations; it++) {
        g.setRandomPositions();
        graph new_g = intersectionTransform(g);
        int result = getIntersectionNumber(new_g);
        if (result == answer) {
            iterations++;
        } else if (result < answer) {
            answer = result;
            answer_g = new_g;
            iterations = 0;
        }
        if (iterations == max_iterations) break;
    }
    g = answer_g;
}


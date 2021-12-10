#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>

#include "algo.h"

const double cRep = 2;
const double cSpring = 10;
const double sLen = 1;

const int MAXRAND = 1000;
const int ITER = 10000;
const double rate = 0.0001;

struct pnt {
    double x, y;
    pnt() {}
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
    return cRep / (dist(a, b)*dist(a, b));
}

double fSpring(pnt a, pnt b) {
    return cSpring * std::log(dist(a, b)/sLen);
}

pnt displacement(int v, int n, graph& g) {
    pnt res;
    res.x = res.y = 0;

    /* get neigbours of v */
    std::vector<char> is_neighbour(n, 0);
    for (int i = 0; i < g.mem.size(); i++) {
        if (g.mem[i].first == v)
            is_neighbour[g.mem[i].second] = 1;
        if (g.mem[i].second == v)
            is_neighbour[g.mem[i].first] = 1;
    }

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

void algo::applySprings(graph& g, int iterations) {

    int n = g.size;
    std::vector<pnt> dsp(n);
    for (int iter = 0; iter < iterations; iter++) {
        for (int i = 0; i < n; i++) {
            dsp[i] = displacement(i, n, g);
        }
        for (int i = 0; i < n; i++) {
            g.positions[i].first += rate*dsp[i].x;
            g.positions[i].second += rate*dsp[i].y;
        }
    }
}


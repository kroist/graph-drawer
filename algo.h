#include "shared.h"

const double cRep = 2;
const double cSpring = 10;
const double sLen = 1;

const int MAXRAND = 1000;
const int ITER = 10000;
const double rate = 0.0001;

const double EPS = 1e-6;

namespace algo {
    void applySprings(graph& g, int iterations);
    void applyIntersections(graph& g, int max_iterations);

    bool drawPlanar(graph& g);
};


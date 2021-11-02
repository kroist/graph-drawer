#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>

const double cRep = 2;
const double cSpring = 10;
const double sLen = 1;

const int MAXRAND = 1000;
const int ITER = 10000;
const double rate = 0.0001;

struct pnt {
    double x, y;
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

pnt displacement(int v, int n, std::vector<std::vector<char> > matr, std::vector<pnt> coords) {
    pnt res;
    res.x = res.y = 0;
    for (int i = 0; i < n; i++) {
        if (i == v)
            continue;
        if (matr[v][i] == 1) {
            double k = fSpring(coords[i], coords[v]);
            pnt cur = vec(coords[v], coords[i]);
            res.x += cur.x*k;
            res.y += cur.y*k;
        }
        else {
            double k = fRep(coords[i], coords[v]);
            pnt cur = vec(coords[i], coords[v]);
            res.x += cur.x*k;
            res.y += cur.y*k;
        }
    }
    return res;
}

int main(int argc, char* argv[]) {
    srand(time(nullptr));
    if (argc < 2) {
        std::cout << "Please specify filename" << std::endl;
        return 1;
    }
    std::ifstream ifs(argv[1]);
    if (ifs.fail()) {
        std::cout << "File " << argv[1] << " does not exist" << std::endl;
        return 1;
    }

    int n, m;
    ifs >> n >> m;


    std::vector<std::vector<char> > matr(n, std::vector<char>(n, 0));
    std::vector<std::pair<int, int> > edges;

    for (int i = 0; i < m; i++) {
        int u, v;
        ifs >> u >> v;
        edges.push_back({u, v});
        matr[u][v] = matr[v][u] = 1;
    }
    ifs.close();

    std::vector<pnt> coords(n);


    for (int i = 0; i < n; i++) {
        coords[i].x = rand()%MAXRAND;
        coords[i].y = rand()%MAXRAND;
    }


    for (int iter = 0; iter < ITER; iter++) {
        pnt dsp[n];
        for (int i = 0; i < n; i++) {
            dsp[i] = displacement(i, n, matr, coords);
        }
        for (int i = 0; i < n; i++) {
            coords[i].x += rate*dsp[i].x;
            coords[i].y += rate*dsp[i].y;
        }
    }

    std::string s(argv[1]);
    s = "out" + s;

    std::ofstream ofs(s);

    ofs << n << std::endl;
    for (int i = 0; i < n; i++) {
        ofs << std::fixed << std::setprecision(5) << coords[i].x << ' ' << coords[i].y << std::endl;
    }
    ofs << m << std::endl;
    for (int i = 0; i < m; i++) {
        ofs << edges[i].first << ' ' << edges[i].second << std::endl;
    }

    ofs.close();

}

#include <iostream>
#include <string>
#include <fstream>


int main(int argc, char* argv[]) {
    std::string s;
    int n;
    srand(time(nullptr));

    if (argc > 1)
        s = argv[1];
    else {
        s = "tree";
    }
    if (argc > 2) {
        n = atoi(argv[2]);
    }
    else n = rand()%30+2;

    std::ofstream ofs("graph.txt");

    if (s == "tree") {
        ofs << n << ' ' << n-1 << std::endl;
        for (int i = 1; i < n; i++) {
            int j = rand()%i;
            ofs << j << ' ' << i << std::endl;
        }

    }
    else if (s == "complete") {
        ofs << n << ' ' << n*(n-1)/2 << std::endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++)
                ofs << i << ' ' << j << std::endl;
        }
    } else if (s == "bipartite") {
        ofs << 2 * n << ' ' << n * n << std::endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ofs << i << ' ' << j + n << std::endl;
            }
        }
    } else if (s == "star") {
        ofs << n << ' ' << n - 1 << std::endl;
        for (int i = 1; i < n; i++) {
            ofs << 0 << ' ' << i << std::endl;
        }
    }

    ofs.close();
}

#include <iostream>
#include <string>
#include <fstream>
#include <vector>


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
        std::vector<std::pair<int, int> > vec;
        ofs << n << ' ' << n-1 << std::endl;
        for (int i = 1; i < n; i++) {
            int j = rand()%i;
            ofs << j << ' ' << i << std::endl;
        }

    }
    else if (s == "complete") {
        std::vector<std::pair<int, int> > vec;
        ofs << n << ' ' << n*(n-1)/2 << std::endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++)
                ofs << i << ' ' << j << std::endl;
        }
    }

    ofs.close();
}

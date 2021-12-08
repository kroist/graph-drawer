#include "graphIO.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// conversion from graph to json
void to_json(json& j, const graph& p) {
    if(p.positions.size())
        j = json{{"size", p.size}, {"edges", p.mem}, {"positions", p.positions}};
    else {
        j = json{{"size", p.size}, {"edges", p.mem}};
    }
}

bool load_positions = false;

// conversion from json to graph
void from_json(const json& j, graph& p) {
    j.at("size").get_to(p.size);
    j.at("edges").get_to(p.mem);
    if(load_positions) {
        j.at("positions").get_to(p.positions);
    }
}

static graph read_normal(std::istream& stream) {
    size_t size, m;
    stream >> size >> m;
    std::vector<std::pair<double,double>> positions;
    if(load_positions) {
        positions.reserve(size);
        for(size_t i = 0; i < size; i++) {
            int n; stream >> n; // node number
            double x, y;
            stream >> x >> y;
            positions[n-1] = {x, y};
        }
    }

    std::vector<std::pair<int,int>> edges;
    edges.reserve(m);

    for(size_t i = 0; i < m; i++) {
        int l, r;
        stream >> l >> r;
        edges.push_back({ l, r });
    }
    return graph(size, edges, positions);
}

graph graphIO::read_graph(std::istream& stream, bool use_json, bool with_positions) {
    load_positions = with_positions;
    if(use_json) {
        json j;
        stream >> j;
        return j;
    }
    else {
        return read_normal(stream);
    }
}

static void write_normal(std::ostream& stream, graph& g) {
    stream << g.size << ' ' << g.mem.size() << '\n';
    for(int i = 1; i <= g.size; i++) {
        stream << i << ' ' << g.positions[i-1].first << ' ' << g.positions[i-1].second << '\n';
    }
    for(auto p : g.mem) {
        stream << p.first << ' ' << p.second << '\n';
    }
}

void graphIO::write_graph(std::ostream& stream, graph& g, bool use_json) {
    if(use_json) {
        json j = g;
        stream << j.dump(4) << '\n';
    }
    else {
        write_normal(stream, g);
    }
}
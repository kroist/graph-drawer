#include "graphIO.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// conversion from graph to json
void to_json(json& j, const graph& p) {
    if(p.positions.size())
        j = json{{"size", p.size}, {"edges", p.edges}, {"positions", p.positions}};
    else {
        j = json{{"size", p.size}, {"edges", p.edges}};
    }
}

bool load_positions = false;
// conversion from json to graph
void from_json(const json& j, graph& p) {
    j.at("size").get_to(p.size);
    j.at("edges").get_to(p.edges);
    if(load_positions) {
        j.at("positions").get_to(p.positions);
    }
}

static graph read_json(std::istream& stream) {
    json j;
    stream >> j;
    return j;
}

static graph read_normal(std::istream& stream) {
    size_t size, m;
    stream >> size >> m;
    std::vector<std::pair<double,double>> positions;
    if(load_positions) {
        positions.reserve(size);
        for(size_t i = 0; i < size; i++) {
            int node; // node number
            stream >> node;
            double x, y;
            stream >> x >> y;
            positions[node-1] = {x, y};
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
    // set global var for from_json() conversion function
    load_positions = with_positions;

    if(use_json) {
        return read_json(stream);
    }
    else {
        return read_normal(stream);
    }
}

static void write_normal(std::ostream& stream, graph& g) {
    stream << g.size << ' ' << g.edges.size() << '\n';
    for(int i = 1; i <= g.size; i++) {
        stream << i << ' ' << g.positions[i-1].first << ' ' << g.positions[i-1].second << '\n';
        // stream << g.positions[i-1].first << ", " << g.positions[i-1].second << '\n';
    }
    // for(auto p : g.edges) {
    //     stream << p.first << ' ' << p.second << '\n';
    // }
}

static void write_tikz(std::ostream& stream, graph& g) {
    stream << "\\documentclass{article}\n\\usepackage[utf8]{inputenc}\n\\usepackage{tikz}\n\\begin{document}\n\\begin{tikzpicture}\n\\begin{scope}[every node/.style={circle,thick,draw}]\n";
    for(int i = 0; i < g.size; i++) {
        stream << "\\node (" << i + 1 << ") at (" << 10 * g.positions[i].first << ", " << 10 * g.positions[i].second << ") {" << i + 1 << "};\n";
    }
    stream << "\\end{scope}\n\n";
    stream << "\\begin{scope}[every node/.style={fill=white,circle}, every edge/.style={draw=red,very thick}]\n";
    for (auto p : g.edges) {
        stream << "\\draw [-] (" << p.first << ") -- (" << p.second << ");\n";
    }
    stream << "\\end{scope}\n\\end{tikzpicture}\n\\end{document}\n";
}

void graphIO::write_graph(std::ostream& stream, graph& g, unsigned short out_type) {
    if(out_type & OutType::normal_t) {
        write_normal(stream, g);
    }
    if(out_type & OutType::json_t) {
        json j = g;
        stream << j.dump(4) << '\n';
    }
    if(out_type & OutType::tikz_t) {
        write_tikz(stream, g);
    }
}
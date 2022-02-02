#include "algo.h"
#include <lemon/planarity.h>
#include <lemon/math.h>
#include <lemon/graph_to_eps.h>
#include <lemon/list_graph.h>

#include <vector>

using namespace lemon;

bool algo::drawPlanar(graph& g) {
    if (g.size < 3) {
        return false;
    }

    typedef ListGraph::Node Node;

    ListGraph lgraph;
    std::vector<Node> nodes;
    for (int i = 0; i < g.size; i++) {
        nodes.push_back(lgraph.addNode());
    }
    for (auto edge : g.edges) {
        lgraph.addEdge(nodes[edge.first], nodes[edge.second]);
    }

    PlanarEmbedding<ListGraph> embedding(lgraph);

    if (!embedding.run(false)) {
        return false;
    }

    PlanarDrawing<ListGraph> drawing(lgraph);
    drawing.run(embedding.embeddingMap());

    for (int i = 0; i < g.size; i++) {
        double x = drawing[nodes[i]].x;
        double y = drawing[nodes[i]].y;
        g.positions[i] = { x, y };
    }
    return true;
}

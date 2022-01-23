#include "shared.h"
#include <lemon/planarity.h>

#include <lemon/math.h>

#include<lemon/graph_to_eps.h>
#include<lemon/list_graph.h>

#include <vector>

using namespace lemon;

bool maybe_draw_planar(graph& g) {
    if(g.size < 3) {
        return true;
    }

    // g is assumed to be simple
    typedef ListGraph::Node Node;

    ListGraph lgraph;
    std::vector<Node> nodes;
    for(int i = 0; i < g.size; i++) {
        nodes.push_back(lgraph.addNode());
    }
    for(auto edge : g.edges) {
        lgraph.addEdge(nodes[edge.first-1], nodes[edge.second-1]);
    }
    
    lemon::PlanarEmbedding<ListGraph> embedding(lgraph);
    
    embedding.run(false);

    lemon::PlanarDrawing<ListGraph> drawing(lgraph);
    drawing.run(embedding.embeddingMap());
    
    for(int i = 0; i < g.size; i++) {
        double x = drawing[nodes[i]].x;
        double y = drawing[nodes[i]].y;
        g.positions[i] = {x, y};
    }
    return true;
}

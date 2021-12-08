#include <iostream>
#include "shared.h"

namespace graphIO {
    graph read_graph(std::istream& stream, bool use_json, bool with_positions);
    void write_graph(std::ostream& stream, graph& g, bool use_json);
};
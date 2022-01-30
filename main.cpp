#include <gflags/gflags.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

#include "shared.h"
#include "graphIO.h"
#include "algo.h"
#include "planar.h"

bool user_provided(const char* flag_name) {
    return !gflags::GetCommandLineFlagInfoOrDie(flag_name).is_default;
}

DEFINE_bool(in_json, false, "Treat input as json object");
DEFINE_bool(in_coords, false, "Assume that input contains coordinates");
DEFINE_bool(skip_planar, false, "Skip planarity checking & drawing");

DEFINE_string(in_file, "", "Name of the input file");
DEFINE_string(out_file, "", "Name of the output file");
DEFINE_string(transform, "full", "Choose transformation type (allowed full, intersections, springs)");
DEFINE_string(out_type, "normal", "Set output type (allowed normal, json, tikz)");

DEFINE_int32(iterations, 10000, "Number of iterations");

bool handle_flags(int argc, char* argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    // check if transform was correct
    if (!(FLAGS_transform == "full" || FLAGS_transform == "intersections" || FLAGS_transform == "springs")) {
        std::cerr << "Unrecognised transform option " << FLAGS_transform << ", allowed are: full, intersections, springs" << std::endl;
        return false;
    }
    // check if return type was correct
    if(!(FLAGS_out_type == "normal" || FLAGS_out_type == "json" || FLAGS_out_type == "tikz")) {
        std::cerr << "Unrecognised output type option " << FLAGS_out_type << ", allowed are: normal, json, tikz" << std::endl;
        return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    if(!handle_flags(argc, argv)) {
        return 1;
    }

    std::ifstream rstream;
    if (user_provided("in_file")) {
        rstream.open(FLAGS_in_file, std::ifstream::in);
    }
    
    graph g = graphIO::read_graph(user_provided("in_file") ? rstream : std::cin, FLAGS_in_json, FLAGS_in_coords);
    
    // apply transformations
    g.positions.resize(g.size);
    if (!FLAGS_in_coords) {
        g.setRandomPositions();
    }

    if(!FLAGS_skip_planar && maybe_draw_planar(g)) {

    }
    else if (FLAGS_transform == "full") {
        //algo::applyIntersections(g, FLAGS_iterations);
        algo::applySprings(g, FLAGS_iterations);
    } else if (FLAGS_transform == "intersections") {
        algo::applyIntersections(g, FLAGS_iterations);
    } else if (FLAGS_transform == "springs") {
        algo::applySprings(g, FLAGS_iterations);
    }

    g.scaleToUnitSquare();

    // save output
    std::ofstream wstream;
    if (user_provided("out_file")) {
        wstream.open(FLAGS_out_file, std::ofstream::trunc | std::ofstream::out);
    }
    graphIO::write_graph(user_provided("out_file") ? wstream : std::cout, g, FLAGS_out_type);
}

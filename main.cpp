#include <gflags/gflags.h>
#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <cstring>

#include "shared.h"
#include "graphIO.h"
#include "algo.h"

/*
flag defines
*/
bool user_provided(const char* flag_name) {
    return !gflags::GetCommandLineFlagInfoOrDie(flag_name).is_default;
}

DEFINE_string(in_file, "", "Name of the input file");
DEFINE_bool(in_json, false, "Treat input as json object");
DEFINE_bool(in_coords, false, "Assume that input contains coordinates");

DEFINE_string(out_file, "", "Name of the output file");
DEFINE_string(transform, "full", "Choose transformation type (allowed full, intersections, springs)");

DEFINE_string(out_type, "normal", "Set output type (allowed any combination of: normal, json, tikz)");

unsigned short handle_out_type() {
    unsigned short result = 0;
    std::vector<std::string> options;
    boost::algorithm::split(options, FLAGS_out_type, boost::is_any_of(","));
    if(options.size() == 0) {
        return 1;
    }
    else if(options.size() > 3) {
        std::cerr << "Flag out_type contains too many options!" << std::endl;
        return 0;
    }
    else {
        for(std::string& opt : options) {
            if(opt == "normal") {
                result |= OutType::normal_t;
            }
            else if(opt == "json") {
                result |= OutType::json_t;
            }
            else if(opt == "tikz") {
                result |= OutType::tikz_t;
            }
            else {
                std::cerr << "Option " << opt << " for flag out_type is unrecognised." << std::endl;
                return 0;
            }
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    // check if transform was correct
    if (!(FLAGS_transform == "full" || FLAGS_transform == "intersections" || FLAGS_transform == "springs")) {
        std::cerr << "Unrecognised transform option " << FLAGS_transform << ", allowed are: full, intersections, springs" << std::endl;
        return 1;
    }
    unsigned short out_type = handle_out_type();
    if(out_type == 0) {
        return 1;
    }

    std::ifstream rstream;
    if (user_provided("in_file")) {
        rstream.open(FLAGS_in_file, std::ifstream::in);
    }
    
    graph g = graphIO::read_graph(user_provided("in_file") ? rstream : std::cin, FLAGS_in_json, FLAGS_in_coords);
    
    // apply transformations
    g.positions.resize(g.size);
    g.setRandomPositions();

    if (FLAGS_transform == "full") {
        //algo::applyIntersections(g);
        algo::applySprings(g, 10000);
    } else if (FLAGS_transform == "intersections") {
        algo::applyIntersections(g);
    } else if (FLAGS_transform == "springs") {
        algo::applySprings(g, 10000);
    }

    g.scaleToUnitSquare();

    // save output
    std::ofstream wstream;
    if (user_provided("out_file")) {
        wstream.open(FLAGS_out_file, std::ofstream::trunc | std::ofstream::out);
    }
    graphIO::write_graph(user_provided("out_file") ? wstream : std::cout, g, out_type);
}

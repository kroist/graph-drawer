#include <gflags/gflags.h>
#include <iostream>
#include <fstream>
#include <cstring>

#include "shared.h"
#include "graphIO.h"

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
DEFINE_bool(out_json, false, "Save output as json object");
DEFINE_string(transform, "full", "Choose transformation type (allowed full, intersections, springs)");

int main(int argc, char* argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    // check if transform was correct
    if(!(FLAGS_transform == "full" || FLAGS_transform == "intersections" || FLAGS_transform == "springs")) {
        std::cerr << "Unrecognised transform option " << FLAGS_transform << ", allowed are: full, intersections, springs" << std::endl;
        return 1;
    }
    //
    std::ifstream rstream;
    if(user_provided("in_file")) {
        rstream.open(FLAGS_in_file, std::ifstream::in);
    }
    
    graph g = graphIO::read_graph(user_provided("in_file") ? rstream : std::cin, FLAGS_in_json, FLAGS_in_coords);
    // apply transformations
    if(true) {
        srand(time(NULL));
        g.positions.resize(g.size);
        for(int i = 0; i < g.size; i++) {
            g.positions[i] = { (double)rand() / RAND_MAX, (double)rand() / RAND_MAX }; 
        }
    }
    if(FLAGS_transform == "full") {

    }
    else if(FLAGS_transform == "intersections") {

    }
    else if(FLAGS_transform == "springs") {

    }
    //

    // save output
    std::ofstream wstream;
    if(user_provided("out_file")) {
        wstream.open(FLAGS_out_file, std::ofstream::trunc | std::ofstream::out);
    }
    graphIO::write_graph(user_provided("out_file") ? wstream : std::cout, g, FLAGS_out_json);
}
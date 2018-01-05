#include "ams562_cvhull.h"
#include <vector>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace ams562;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "You must pass in the testing file\n";
        return EXIT_FAILURE;
    }
    std::string filename = argv[1];

    CvHullBase *method = nullptr;

    // split method
    if (argc > 3) {
        // if you have other method, handle here
        // since currently we only have graham scan
        method = new GrahamScan();
    }
    else
        method = new GrahamScan();

    std::vector<Point2D> pc;
    std::vector<Point2D> ch;

    //
    // Estimate the size of pc and ch by using reserve!

    pc.reserve(300);
    ch.reserve(50);

    loadtxt("./test/"+filename, pc);
    compute_cvhull(pc, ch, *method);
    write2txt("res_"+filename, ch);

    std::cout << "\nThe result has been written to [res_" << filename << "]\n\n";
    /*
    for (int i = 0; i < pc.size(); i++){
        std::cout << pc[i] << '\n';
    }
    */
    if (method)
        delete method;
}

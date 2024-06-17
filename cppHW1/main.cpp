#include <iostream>
#include <fstream>
#include "Simulation.h"

using namespace std;

int main(int argc, char* argv[]) {


    Simulation s1 = Simulation(argv[1], argv[2]);
    s1.read_config();
    s1.read_firstGen();
    s1.run_sim();


    return 0;
}

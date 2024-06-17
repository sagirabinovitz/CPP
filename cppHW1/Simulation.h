
#ifndef CPPHW1_SIMULATION_H
#define CPPHW1_SIMULATION_H

#include "Virus.h"
#include "XBB.h"
#include "BQ.h"
#include "CH.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Simulation {
private:
    int dim;
    string target;
    int num_iter;
    string configFileName;
    string firstGenFileName;
    vector<Virus*> population;
    vector<Ancestor*> ancestors;
    Virus* fittest;
    int populationSize;

public:
    Simulation(string config,string first_generation); //constructor
    void read_config(); //reads the config.dat file
    void read_firstGen(); //reads the first_generation.dat file
    void run_sim(); //runs the simulation
    void calc_similarity(); //calculates the similarities to the target virus among all the viruses in the population
    void indUp(); //individual update
    void groupUp(); //group update
    void print(); //prints the output as desired
    static bool compare(const Virus* v1,const Virus* v2); //compares simillarities between 2 viruses using the < operator that was created in Virus class
    Virus* create_vir(string val,const char &type, Ancestor* ancestor); //creates a new virus

};


#endif //CPPHW1_SIMULATION_H

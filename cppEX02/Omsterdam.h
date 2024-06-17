//
// Created by user on 12/03/2024.
//

#ifndef CPPEX02_OMSTERDAM_H
#define CPPEX02_OMSTERDAM_H

#include "DirectedGraph.h"
#include "FileNotFound.h"
#include <memory>
#include <iostream>
#include <queue>
#include <algorithm>
#include <stack>
#include <limits>
#include <unordered_map>

using namespace std;


class Omsterdam {
private:
    shared_ptr<DirectedGraph> graph;
    shared_ptr<DirectedGraph> rev_graph;

    map<string,int> waiting_times;
    map<string,int> transit_times;
    string out_file;

    void out_bound(DirectedGraph dg,const string& startNode,const string& type);

    void dijkstra(DirectedGraph dg, const string& start, const string& type, const string& target);
    double dijkstra_trans(DirectedGraph dg, const string &start, const string &target);

    string getStationType(const string& str);
    bool is_file_exist(const string &fileName);

public:
    //constructor
    Omsterdam();

    //reads  all the input files
    void read_files(const string& file);
    //reads the config.dat file
    void read_config(const string& file);
    //checks that the string is valid according to the ex instructions
    static bool validate(const string& str);
    //checks that a given char is digit
    static bool validate_integer(const string& str, const string& file);
    //write the output to a file and names it str
    void write_file(const string& str);
    //move the client to the "enter commands" state
    void user_interface();
    void setOutFile(const string &outFile);



};


#endif //CPPEX02_OMSTERDAM_H

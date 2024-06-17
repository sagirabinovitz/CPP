//
// Created by user on 12/03/2024.
//

#ifndef CPPEX02_DIRECTEDGRAPH_H
#define CPPEX02_DIRECTEDGRAPH_H

using namespace std;

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include <memory>
#include <fstream>


#include "Edge.h"


class DirectedGraph {
private:
    map<string, vector<shared_ptr<Edge>>> graph;

public:
    DirectedGraph();

    //Big Five
    DirectedGraph(const DirectedGraph &other);
    DirectedGraph &operator=(const DirectedGraph &other);
    ~DirectedGraph() = default;
    DirectedGraph(DirectedGraph &&rhs) noexcept ;
    DirectedGraph &operator=(DirectedGraph &&rhs) noexcept ;


    // Add a new vertex if none exists.
    void addVertex(const string& v);

    // Remove the vertex and its edges from the graph.
    void removeVertex(const string& v);

    // Add an edge to the graph
    void putEdge(const string& u, const string& v, double weight, string s);


    // Checks if the graph contains the vertex v.
    bool containVertex(const string& v);

    // Checks if the edge (u,v) exists.
    bool containEdge(const string& u, const string& v, const string& type);

    //returns all the neighbors of a given vertex
    vector<string> get_neighbors(const string& vertex);

    //returns all reachable vertices from a given vertex
    vector<string> get_neighbors_transport(const string& vertex,string s);

    //returns all the connected vertices of a given vertex
    vector<string> get_connected(const string& vertex);

    //prints the graph according to the ex instructions
    void print_graph(const string& outfile);

    //returns the size of the graph
    int getGraphSize() const;

    //graph getter
    const map<string, vector<shared_ptr<Edge>>> &getGraph() const;

    //returns all the edges of the neighbors of a given vertex
    vector<shared_ptr<Edge>> get_neighbors_edges(const string &vertex, string s);
    vector<shared_ptr<Edge>> get_neighbors_edges(const string &vertex);

};


#endif //CPPEX02_DIRECTEDGRAPH_H

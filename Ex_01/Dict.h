#include <string>
#ifndef EX_01_DICT_H
#define EX_01_DICT_H
using namespace std;
class Dict{

private:

    string * id ;
    double **obs;
    int cur;
    int max_size;
    int dim;
public:
    int getDim() const;


public:
    //constructor
    Dict(int n, int m);
    //returns true if obs_id exist already, otherwise returns false
    bool exist(const string& s);
    //returns the index of obs_id
    int index_of(const string& s);
    //start operation
    void menu();
    //insert new observation to the calculator
    void insert();
    //prints specific observation by its id
    void print_obs();
    //print the mean vector of the calculator
    void print_mean();
    //print the Covariance matrix of the calculator
    void print_mat();
    //resizes the calculator size
    void resize();
    //deconstructor
    ~Dict();
};

#endif

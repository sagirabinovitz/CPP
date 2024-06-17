
#ifndef CPPHW1_VIRUS_H
#define CPPHW1_VIRUS_H


#include <iostream>
#include <sstream>
#include <cstring>
#include "Ancestor.h"

using namespace std;

class Virus {
private:

    Ancestor* ancestor;
    string data;
    char type;
    double similarity;

public:

    //constructor
    Virus(string val,const char &type, Ancestor* ancestor);

    //big 3
    Virus(const Virus& vir);
    Virus& operator= (const Virus& vir);
    virtual ~Virus();

    //getters and setters
    double getSimilarity() const;
    char getType() const;
    void setSimilarity(double similarity);
    const string &getData() const;
    void setData(const string &data);
    Ancestor *getAncestor() const;


    virtual void update() {};//abstract method that will be implemented differently in the extends of this class

    bool operator<(const Virus& other) const;//operator < that will compare between the simallarities to the target virus between 2 viruses




};


#endif //CPPHW1_VIRUS_H

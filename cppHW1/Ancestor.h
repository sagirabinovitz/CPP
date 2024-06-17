//
// Created by user on 11/02/2024.
//

#ifndef CPPHW1_ANCESTOR_H
#define CPPHW1_ANCESTOR_H

#include <string>

using namespace std;


class Ancestor {
private:
    struct RC_Ancestor{
        int counter;
        RC_Ancestor();

    };
    string origin;
    RC_Ancestor* rc_data;
    char type;

public:
    //constructor
    Ancestor(string origin,char type);
    //big3
    Ancestor(const Ancestor& other);
    Ancestor& operator=(const Ancestor& other);
    ~Ancestor();

    //getters and setters
    const string &getOrigin() const;
    void setOrigin(const string &origin);
    RC_Ancestor *getRcData() const;
    void setRcData(RC_Ancestor *rcData);
    char getType() const;
    void setType(char type);


};


#endif //CPPHW1_ANCESTOR_H

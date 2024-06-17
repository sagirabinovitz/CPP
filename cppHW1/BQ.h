//
// Created by user on 05/02/2024.
//

#ifndef CPPHW1_BQ_H
#define CPPHW1_BQ_H

#include "Virus.h"

using namespace std;

class BQ : public Virus {
private:
    double pm;

public:
    BQ(string val, const char &type,Ancestor* anc);
    void update() override;


};


#endif //CPPHW1_BQ_H

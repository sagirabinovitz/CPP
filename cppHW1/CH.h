//
// Created by user on 05/02/2024.
//

#ifndef CPPHW1_CH_H
#define CPPHW1_CH_H

#include "Virus.h"

using namespace std;

class CH : public Virus {
private:
    double pm;

public:
    CH(string val, const char &type, Ancestor *anc);

    void update() override;

};


#endif //CPPHW1_CH_H

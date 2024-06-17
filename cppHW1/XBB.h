

#ifndef CPPHW1_XBB_H
#define CPPHW1_XBB_H


#include "Virus.h"

using namespace std;

class XBB : public Virus{
private:
    double pm;

public:
    XBB(string val, const char &type,Ancestor* anc);
    void update() override;

};


#endif //CPPHW1_XBB_H

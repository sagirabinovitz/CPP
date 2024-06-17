//
// Created by user on 05/02/2024.
//

#include "XBB.h"
#define PROB 0.25

XBB::XBB(string val, const char &type,Ancestor* anc) : Virus(std::move(val), type, anc) {
    pm = PROB;
}




void XBB::update() {
    double random = rand()/RAND_MAX;
    string data = getData();
    for(int i=0;i<this->getData().size();i++){
        if(random<=pm){
            switch (data[i]) {
                case 'A':{
                    data[i]='T';
                }
                case 'T':{
                    data[i]='A';
                }

            }
        }
        random = rand()/RAND_MAX;
    }
    setData(data);
}






//
// Created by user on 05/02/2024.
//

#include "CH.h"

CH::CH(string val, const char &type,Ancestor* anc) : Virus(std::move(val), type, anc) {
    pm = 1-(double)(1)/(double)getData().size();
}



void CH::update() {
    double random = rand()/RAND_MAX;
    string data = getData();
    for(int i=0;i<this->getData().size();i++){
        if(random<=pm){
            switch (data[i]) {
                case 'T':{
                    data[i]='A';
                }
                case 'C':{
                    data[i]='G';
                }
                case 'G':{
                    data[i]='C';
                }
            }
        }
        random = rand()/RAND_MAX;
    }
    setData(data);
}


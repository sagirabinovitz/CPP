//
// Created by user on 05/02/2024.
//

#include "BQ.h"

BQ::BQ(string val, const char &type,Ancestor* anc) : Virus(std::move(val), type, anc) {
    pm = (double)(1)/(double)getData().size();
}



void BQ::update() {
    double random = rand()/RAND_MAX;
    string data = getData();
    for(int i=0;i<data.size();i++){
        if(random<=pm){
            switch (data[i]) {
                case 'A':{
                    data[i]='T';
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

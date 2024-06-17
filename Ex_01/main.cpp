
#include "Dict.h"
#include <strstream>
#include <iostream>
using namespace std;

int main(int argc,char* argv[]) {
    if(argc!=3){
        cerr<<"invalid arguments"<<endl;
        exit(0);
    }
    strstream ss1;
    strstream ss2;
    int dim=0;
    int max_size=0;
    ss1<<argv[1];
    ss1>>dim;
    ss2<<argv[2];
    ss2>>max_size;
    Dict* d1 = new Dict(dim,max_size);
    d1->menu();
    return 0 ;
}

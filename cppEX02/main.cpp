#include <iostream>
#include "Omsterdam.h"


int main(int argc,char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: missing file!" << endl;
        exit(-1);
    }
    string s = argv[1];
    if(s!="-i"){
        cerr<<"wrong command lind format"<<endl;
        exit(-1);
    }

    shared_ptr<Omsterdam> om;
    om = make_shared<Omsterdam>();

    string output = "output.dat";
    string str = argv[argc-2];
    string config = "";

    int num_files = 0;

    if(str=="-o"){
        output = argv[argc-1];
        if((string)argv[argc-4]=="-c"){
            config = argv[argc-3];
            num_files = argc-6;
        }
        else{
            num_files = argc-4;
        }
    }
    else if(str=="-c"){
        config = argv[argc-1];
        num_files = argc-4;
    }
    else{
        num_files = argc-2;
    }

    if (num_files <= 0) {
        throw invalid_argument("Invalid number of files specified.");
    }

    for(int i=2;i<=num_files+1;i++){
        om->read_files(argv[i]);
    }

    if(config!=""){
        om->read_config(config);
    }
    if(output!="output.dat"){
        om->setOutFile(output);
    }

    om->user_interface();



    return 0;
}
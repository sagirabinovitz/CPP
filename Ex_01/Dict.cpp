
#include <iostream>
#include <cstring>
#include "Dict.h"
#include <sstream>


using namespace std;

Dict::Dict(int n,int m){
    max_size = m;
    cur = 0;
    dim = n;
    id = new string[max_size];
    obs = new double*[max_size];
    for(int i=0; i<m; i++){
        obs[i] = new double[dim];
    }
}


bool Dict::exist(const string& s) {
    for(int i=0;i<cur;i++){
        if(id[i]==s){
            return true;
        }
    }
    return false;
}



void Dict::insert() {
    bool flag;
    int x;
    if(cur>=max_size){
        resize();
    }
    string s1;
    string s2;
    stringstream ss;
    int spaces=0;
    cout<<"Enter observation name:"<<endl;
    cin>>s1;
    if(exist(s1)) {
        x = index_of(s1);
        flag=true;
    }
    else {
        x = cur;
        flag=false;
    }
    id[x] = s1;
    cin.ignore();
    cout << "Enter observation values:"<<endl;
    getline(cin, s2);
    ss << s2;
    for (char k: s2) {
        if ((k < '0' || k > '9') && k != ' ' && k != '.') {
            cerr << "string is not valid" << endl;

        }
        if (k == ' ') {
            spaces++;
        }
    }
    if((spaces)!=(dim-1)) {
        flag = true;
        id[cur] = "";
        cerr << "Invalid observation." << endl;
    }
    double num;
    int i = 0;
    while(ss>>num){
        obs[x][i]=num;
        i++;
    }
    if(!(flag)) {
        cur++;
    }
}


int Dict::index_of(const string& s) {
    if(!exist(s)){
        return -1;
    }
    for(int i=0;i<cur;i++){
        if(id[i]==s){
            return i;
        }
    }

}
Dict::~Dict(){
    delete [] id;
    for(int i = 0; i < cur ;i++){
        delete [] obs[i];
    }
    delete [] obs;
}


void Dict::menu() {
    std::cout<<"[1] New observation"<<endl;
    std::cout<<"[2] Print observation"<<endl;
    std::cout<<"[3] Expected value vector"<<endl;
    std::cout<<"[4] Covariance matrix"<<endl;
    std::cout<<"[5] Exit"<<endl;


   int pick;


    while(true) {
        cin>>pick;
        switch (pick) {
            case 1:
                insert();
                break;
            case 2:
                print_obs();
                break;
            case 3:
                print_mean();
                break;
            case 4:
                print_mat();
                break;
            case 5:
                exit(0);
            default:
                std::cerr << "Invalid option.\n" << endl;
                break;
        }
    }
}




void Dict::print_obs() {
    string s;
    bool flag = false;
    cout<<"Enter observation name:"<<endl;
    cin>>s;
    for(int i=0;i<max_size;i++){
        if(id[i]==s){
            flag= true;
            cout<<s<<" = [ ";
            for(int j=0;j<dim;j++){
                if(j==dim-1){
                    cout<<obs[i][j];
                }
                else {
                    cout << obs[i][j] << " ";
                }
            }
        }

    }
    if(flag) {
        cout << "]" << endl;
    } else{
        cerr<<"Invalid or nonexistent observation."<<endl;
    }

}

void Dict::print_mean() {
    if(cur==0){
        cerr<<"Empty calculator.\n";
        return;
    }
    cout<<"mean = [";
    int x = getDim();
    double sum=0;
    for(int i=0;i<x;i++){
        for(int j=0;j<cur;j++){
            sum+=obs[j][i];
        }
        cout<<" "<<sum/cur;
        sum=0;
    }
    cout<<"]"<<endl;
}

void Dict::print_mat() {
    if(cur==0){
        cerr<<"Empty calculator.\n";
        return;
    }
    int x = getDim();
    double arr[dim];
    double sum=0;
    float tempsum=0;
    for(int i=0;i<x;i++){
        for(int j=0;j<cur;j++){
            sum+=obs[j][i];
        }
        arr[i]=sum/cur;
        sum=0;
    }
    cout<<"cov = ["<<endl;
    for(int i=0;i<x;i++){
        for(int j=0;j<x;j++){
            tempsum=0;
            for(int k=0;k<cur;k++){
                tempsum+=(obs[k][i]-arr[i])*(obs[k][j]-arr[j]);
            }
            if(cur==1){
                cout<<" "<<(tempsum/cur);
            }
            else{
                cout<<" "<<(tempsum/(cur-1));
            }
        }
        cout<<"\n";
    }
    cout<<"]";

}

int Dict::getDim() const {
    return dim;
}

void Dict::resize() {
    int new_size = max_size+1;
    string * new_ids;
    double** new_mat;
    new_ids = new string[new_size];
    new_mat = new double*[new_size];
    for(int i=0;i<new_size;i++){
        new_mat[i]=new double[dim];
    }
    copy(id,cur+id,new_ids);
    memcpy(new_mat,obs,max_size*sizeof(double));
    delete[] id;
    delete[] obs;
    this->id=new_ids;
    this->obs=new_mat;
    max_size=new_size;
}



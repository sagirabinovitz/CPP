
#include "Simulation.h"

#include <utility>

using namespace std;

Simulation::Simulation(string config, string first_generation) {
    this->configFileName = std::move(config);
    this->firstGenFileName = std::move(first_generation);
    dim = 0;
    target = "";
    num_iter = 0;
    fittest = nullptr;
    populationSize = 0;
}

void Simulation::read_config() {
    ifstream file;
    file.open(configFileName);
    string line;

    getline(file, line);
    dim = stoi(line);


    getline(file, line);
    std::string::iterator end_pos = remove(line.begin(), line.end(), ' ');
    line.erase(end_pos, line.end());
    target = line;
    if(target.size()!=dim){
        cerr<<"target vector is not in the correct size";
        exit(-1);
    }


    getline(file, line);
    num_iter = stoi(line);


    file.close();
}

void Simulation::read_firstGen() {
    ifstream file;
    file.open(firstGenFileName);
    string line;

    getline(file, line);
    populationSize = stoi(line);


    while (!file.eof()) {
        getline(file, line);
        std::string::iterator end_pos = remove(line.begin(), line.end(), ' ');
        line.erase(end_pos, line.end());
        Virus *virus;
        char t = line[0];
        line.erase(0, 1);
        Ancestor *ancestor = new Ancestor(line, t);
        virus = create_vir(line,t,ancestor);

        ancestors.push_back(ancestor);
        population.push_back(virus);
    }
    calc_similarity();
    std::sort(population.begin(), population.end(), compare);
    if(population[populationSize-1]->getSimilarity()==1){
        print();
        exit(-1);
    }
    fittest = new Virus(*population[population.size() - 1]);
}

void Simulation::run_sim() {
    for (int i = 0; i < num_iter; i++) {
        groupUp();
        indUp();
        calc_similarity();
    }
    print();
}

void Simulation::calc_similarity() {
    int sum;
    for (int i = 0; i < this->populationSize; i++) {
        sum = 0;
        for (int j = 0; j < dim; j++) {
            if (population[i]->getData()[j] == target[j]) {
                sum++;
            }
        }
        population[i]->setSimilarity((double) sum / dim);
    }
}

void Simulation::indUp() {
    for (Virus *vir: population) {
        vir->update();
    }
}

void Simulation::groupUp() {
    int a = rand() % populationSize;
    int b = rand() % populationSize;
    while(a==b){
        a = rand() % populationSize;
        b = rand() % populationSize;
    }
    int s = rand() % (dim - 1);
    int t = rand() % (dim - 1) + 1;
    while (t < s + 1) {
        t = rand() % (dim - 1) + 1;
    }

    string str1 = ancestors[a]->getOrigin();
    string str2 = ancestors[b]->getOrigin();
    string str3 = "";
    string str4 = "";

    for (int i = 0; i < dim; i++) {
        if (i > s && i <= t) {
            str3 += str2[i];
            str4 += str1[i];
        } else {
            str3 += str1[i];
            str4 += str2[i];
        }
    }

    calc_similarity();
    std::sort(population.begin(), population.end(), compare);


    Virus* far1 = population[0];
    Virus* far2 = population[1];

    Virus *vir1 = create_vir(str3, ancestors[a]->getType(), ancestors[a]);
    Virus *vir2 = create_vir(str4, ancestors[b]->getType(), ancestors[b]);



    population[0] = vir1;
    population[1] = vir2;
    calc_similarity();

    if(vir1->getSimilarity()>fittest->getSimilarity()) {
        fittest = new Virus(*vir1);
    }
    if(vir2->getSimilarity()>fittest->getSimilarity()) {
        fittest = new Virus(*vir2);
    }
    delete far1;
    delete far2;

}

bool Simulation::compare(const Virus *v1, const Virus *v2) {
    return *v1 < *v2;
}

void Simulation::print() {
    for (int i = 0; i < populationSize; i++) {
        cout << population[i]->getType() << " ";
        for (int j = 0; j < dim; j++) {
            cout << population[i]->getData()[j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < populationSize; i++) {
        cout << ancestors[i]->getType() << " ";
        for (int j = 0; j < dim; j++) {
            cout << ancestors[i]->getOrigin()[j] << " ";
        }
        cout << ancestors[i]->getRcData()->counter - 1 << endl;
    }
    cout << endl;
    cout<<fittest->getAncestor()->getType()<<" ";
    for (int i = 0; i < dim; i++) {
        cout << fittest->getData()[i] << " ";
    }
}

Virus *Simulation::create_vir(string val, const char &type, Ancestor *ancestor) {
    Virus* virus;
    switch (type) {
        case 'x':
            virus = new XBB(val, 'x', new Ancestor(*ancestor));
            break;

        case 'b':
            virus = new BQ(val, 'b', new Ancestor(*ancestor));
            break;

        case 'c':
            virus = new CH(val, 'c', new Ancestor(*ancestor));
            break;

        default:
            cerr << "first_generation file is not valid" << endl;
            exit(-1);
    }
    return virus;
}

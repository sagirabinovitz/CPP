//
// Created by user on 04/02/2024.
//

#include "Virus.h"

#include <utility>

using namespace std;


Virus::Virus(string val, const char &type, Ancestor *ancestor) {
    data = std::move(val);
    this->type = type;
    similarity = 0;
    this->ancestor = ancestor;
}

Ancestor *Virus::getAncestor() const {
    return ancestor;
}

Virus::Virus(const Virus &vir) {
    ancestor = new Ancestor("", vir.type);
    data = vir.data;
    similarity = vir.similarity;
    this->type = vir.type;
    this->ancestor = vir.ancestor;
}

Virus &Virus::operator=(const Virus &vir) {
    if (this == &vir) {
        return *this;
    }
    delete ancestor;
    ancestor = new Ancestor("", vir.type);
    similarity = vir.similarity;
    data = vir.data;
    this->type = vir.type;
    this->ancestor = vir.ancestor;
    return *this;
}

Virus::~Virus() {
    delete ancestor;
}

const string &Virus::getData() const {
    return data;
}

double Virus::getSimilarity() const {
    return similarity;
}

void Virus::setSimilarity(double similarity) {
    Virus::similarity = similarity;
}

void Virus::setData(const string &data) {
    Virus::data = data;
}

bool Virus::operator<(const Virus &other) const {
    return this->similarity < other.similarity;
}

char Virus::getType() const {
    return type;
}

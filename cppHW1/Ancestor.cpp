//
// Created by user on 11/02/2024.
//

#include "Ancestor.h"

#include <utility>

Ancestor::Ancestor(string origin, char type) {
    this->origin=std::move(origin);
    this->type=type;
    rc_data = new RC_Ancestor();
}

Ancestor::Ancestor(const Ancestor &other) {
    origin=other.origin;
    type=other.type;
    rc_data=other.rc_data;
    rc_data->counter++;
}

Ancestor &Ancestor::operator=(const Ancestor &other) {
    if(this==&other || rc_data==other.rc_data){
        return *this;
    }
    if(--rc_data->counter==0){
        delete rc_data;
    }
    origin=other.origin;
    type=other.type;
    rc_data=other.rc_data;
    rc_data->counter++;
    return *this;

}

const string &Ancestor::getOrigin() const {
    return origin;
}

void Ancestor::setOrigin(const string &origin) {
    Ancestor::origin = origin;
}

Ancestor::RC_Ancestor *Ancestor::getRcData() const {
    return rc_data;
}

void Ancestor::setRcData(Ancestor::RC_Ancestor *rcData) {
    rc_data = rcData;
}

char Ancestor::getType() const {
    return type;
}

void Ancestor::setType(char type) {
    Ancestor::type = type;
}

Ancestor::~Ancestor() {
    if(--rc_data->counter==0) {
        delete rc_data;
    }
}

Ancestor::RC_Ancestor::RC_Ancestor() {
    counter=1;
}

//
// Created by Administrator on 2026/7/5.
//

#include "Animals.h"

Animals::Animals(const string &species, int id) : id(id), species(species) {
    total++;
}

Animals::Animals() {
}

Animals::~Animals() {
}

void Animals::printInfo() {
    cout << "New animal -> Species: " << this->species << ", ID: " << this->id << endl;
}

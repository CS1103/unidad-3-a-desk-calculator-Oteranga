//
// Created by Alejandro  Otero on 2019-10-29.
//

#ifndef DESKCALCULATOR_ERROR_H
#define DESKCALCULATOR_ERROR_H

#include <string>
#include <iostream>
using namespace std;

int no_of_errors;
double error(const string& error) {
    no_of_errors++;
    cerr<<"Error: "<<error<<endl;
    return 1;
}

#endif //DESKCALCULATOR_ERROR_H

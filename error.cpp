//
// Created by Alejandro  Otero on 2019-10-29.
//

#include "error.h"

int no_of_errors;
double error(const string& error) {
    no_of_errors++;
    cerr<<"Error: "<<error<<endl;
    return 1;
}

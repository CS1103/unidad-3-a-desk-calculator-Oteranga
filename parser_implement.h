//
// Created by Alejandro  Otero on 2019-10-29.
//

#ifndef DESKCALCULATOR_PARSER_IMPLEMENT_H
#define DESKCALCULATOR_PARSER_IMPLEMENT_H

#include "parser.h"
#include "error.h"
#include "lexer.h"

using Error:error;
using namespace Lexer;

namespace Parser{
    double prim(bool get);
    double term(bool get);
    double expr(bool get);
}

#endif //DESKCALCULATOR_PARSER_IMPLEMENT_H

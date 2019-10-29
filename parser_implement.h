//
// Created by Alejandro  Otero on 2019-10-29.
//

#ifndef DESKCALCULATOR_PARSER_IMPLEMENT_H
#define DESKCALCULATOR_PARSER_IMPLEMENT_H

#include "parser_implement.h"
#include "error.h"
#include "lexer.h"
#include <string>

using namespace std;

using namespace Lexer;

namespace Parser{
    double prim(bool get);
    double term(bool get);
    double expr(bool get);

    enum class Kind:char{
        name, number, end,
        plus = '+',
        minus = '-',
        mul = '*',
        div = '/',
        print = ';',
        assign = '=',
        lp = '(',
        rp = ')'
    };

    struct Token{
        Kind kind;
        string string_value;
    };
}



#endif //DESKCALCULATOR_PARSER_IMPLEMENT_H

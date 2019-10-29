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

namespace Parser {
    double prim(bool get);
    double term(bool get);
    double expr(bool get);

    double expr(bool get) {
        double left = term(get);
        while (true) {
            switch (ts.current().kind) {
                case Kind::plus:
                    left += term(true);
                    break;

                case Kind::minus:
                    left -= term(true);
                    break;
                default:
                    return left;
            }
        }
    }

    double term(bool get) {
        double left = prim(get);
        while (true) {
            switch (ts.current().kind) {
                case Kind::mul:
                    left *= prim(true);
                    break;
                case Kind::div:
                    if (auto d = prim(true)) {
                        left /= d;
                        break;
                    }
                    return error("divide by 0");
                default:
                    return left;
            }
        }
    }

    double prim(bool get) {
        if (get) ts.get(); // read next token
        switch (ts.current().kind) {
            case Kind::number: { // floating-point constant
                double v = ts.current().number_value;
                ts.get();
                return v;

            }
            case Kind::name: {
                double &v = Table::table[ts.current().string_value];
                if (ts.get().kind == Kind::assign)
                    v = expr(true);
                return v;
            }
            case Kind::minus:
                return -prim(true);
            case Kind::lp: {
                auto e = expr(true);
                if (ts.current().kind != Kind::rp)
                    return error("')' expected");
                ts.get();
                return e;
            }
            default:
                return error("primary expected");
        }
    }
}


#endif //DESKCALCULATOR_PARSER_IMPLEMENT_H

//
// Created by Alejandro  Otero on 2019-10-29.
//

#ifndef DESKCALCULATOR_LEXER_H
#define DESKCALCULATOR_LEXER_H

#include <string>
#include <iostream>

using namespace std;
namespace Lexer{
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

    class Token{
        Kind kind;
        std::string string_value;
        double number_value;
    };
    class Token_stream{
    public:
        Token_stream(istream &s) : ip{&s}, owns{false} {}

        Token_stream(istream* p) : ip{ p }, owns{ true } {}

        Token_stream() { close(); }

        Token get(); // read and return next token
        Token& current(); // most recently read token
        void set_input(istream &s) {
            close();
            ip = &s;
            owns = false;
        }

        void set_input(istream* p) {
            close();
            ip = p;
            owns = true;
        }
    private:
        void close() {
            if (owns)
                delete ip;
        }

        istream* ip;
        bool owns;
        Token ct{Kind::end};
    };
}

#endif //DESKCALCULATOR_LEXER_H

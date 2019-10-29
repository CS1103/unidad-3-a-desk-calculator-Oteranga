#include <iostream>
#include <sstream>
#include "parser.h"
#include "lexer.h"
#include "error.h"
#include "table.h"

using Table::table;

double expr(bool get)
{
    double left=term(get);
    while(true){
        switch (ts.current().kind){
            case Kind::plus:
                left=left+term(true);
                break;
            case Kind::minus:
                left=left-term(true);
                break;
            default:
                return left;
        }
    }
}

double term(bool get)
{
    double left=prim(get);
    while(true){
        switch (ts.current().kind){
            case Kind::mul:
                left=left*prim(true);
            case Kind::div:
                if(auto d=prim(true)){
                    left=left/d;
                    break;
                }
                return error("divide by 0");
            default:
                return left;
        }
    }
}

double prim(bool get)
{
    if(get)
        ts.get();
    switch (ts.current().kind){
        case Kind::number:
        {
            double v=ts.current().number_value;
            ts.get();
            return v;
        }
        case Kind::name:
        {
            double& v=table[ts.current().string_value];
            if(ts.get().kind==Kind::assign)
                v=expr(true);
            return v;
        }
        case Kind::minus:
            return -prim(true);
        case Kind::lp:
        {
            auto e=expr(true);
            if(ts.current().kind !=Kind::rp)
                return error(") expected");
            ts.get();
            return e;
        }
        default:
            return error("primary expected");
    }
}

Token Token_stream::get() {
    char ch=0;
    *ip>>ch;

    switch(ch){
        case 0:
            return ct={
                    Kind::end
            };
        case ';':
        case '*':
        case '/':
        case '+':
        case '-':
        case '(':
        case ')':
        case '=':
            return ct={
                static_cast<Kind>(ch)
            };
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '.':
            ip->putback(ch);
            *ip>>ct.number_value;
            ct.kind=Kind::number;
            return ct;
        default:
            if(isalpha(ch)){
                ip->putback(ch);
                *ip>>ct.string_value;
                ct.kind=Kind::name;
                return ct;
            }
            error("bad token");
            return ct={Kind::print};
    }


}

Token Token_stream::get() {
    char ch;
    do{
        if (!ip->get(ch))
            return ct={
                Kind::end
        };
    } while(ch!='\n'&& isspace(ch));

    switch (ch){
        case ';':
        case '\n':
            return ct={
                Kind::print
            };
        default:
            if(isalpha(ch)){
                string_value=ch;
                while(ip->get(ch)&&isalnum(ch))
                    string_value+=ch;
                ip->putback(ch);
                return ct={
                        Kind::name
                };
            }
    }
}

Token_stream ts{cin};

void calculate(){
    while (true){
        ts.get();
        if(ts.current().kind==Kind::end)
            break;
        if(ts.current().kind==Kind::print)
            continue;
        cout<<expr(false)<<'\n';
    }
}

namespace Driver{
    void calculate() {}
}

int main() {

    Table["pi"]=3.1415926535897932385;
    Table["e"]=2.7182818284590452354;
    calculate();

    return no_of_errors;

}
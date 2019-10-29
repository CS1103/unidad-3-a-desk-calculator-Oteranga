#include <iostream>
#include <sstream>
#include "lexer.h"
#include "error.h"
#include "table.h"
#include "parser_implement.h"

using namespace std;
using namespace Parser;

Lexer::Token_stream ts {cin};
void calculate(){
    while (true){
        ts.get();
        if(ts.current().kind==Lexer::Kind::end)
            break;
        if(ts.current().kind==Lexer::Kind::print)
            continue;
        cout<<expr(false)<<'\n';
    }
}

namespace Driver{
    void calculate() {}
}

int main(int argc, char* argv[]) {

    Table::table["pi"]=3.1415926535897932385;
    Table::table["e"]=2.7182818284590452354;
    calculate();

    return no_of_errors;

}
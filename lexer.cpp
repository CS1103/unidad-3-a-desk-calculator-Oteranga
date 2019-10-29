//
// Created by Alejandro  Otero on 2019-10-29.
//

#include "lexer.h"
#include "error.h"
#include <cctype>
#include <iostream>

Lexer::Token_stream ts;

Lexer::Token Lexer::Token_stream::get() {}
Lexer::Token&Lexer::Token_stream::current() {}
/*
    aksinha
    a03.l
    Assignment 03 - Regular expressions and flex

    Created by Atreya Sinha on 09/03/21.
    Copyright © 2021 Atreya Sinha. All rights reserved.
/*

/* definitions */
%option noyywrap

%{
    #include <iostream>
    using std::cout; 
%}

/* regexp action */
%%
[tT]he                            std::cout << "T_DEFINITE_ARTICLE";
quick|brown|lazy                  std::cout << "T_ADJECTIVE";
fox|dog|wall|liquid|bottles       std::cout << "T_NOUN";
jumped|see                        std::cout << "T_VERB";
[0-9]+                            std::cout << "T_INTEGER";
over|on|of                        std::cout << "T_PREPOSITION";
I                                 std::cout << "T_PRONOUN";
[.]                               std::cout << "T_PERIOD";
%%

/* user code */
int main() {
    yylex();
    return 0;
}
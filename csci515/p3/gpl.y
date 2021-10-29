//
// aksinha
// gpl.y
// P2: Second Project

// Created by Atreya Sinha on 10/01/21.
// Copyright © 2021 Atreya Sinha. All rights reserved.
//
// Mon Apr 27 16:03:16 PDT 2020
// bison syntax indicating C++ declarations required by both the parser and scanner
%code requires {
  #include <string>
  class Expression;
  class Variable;
  struct Parameter;
  class Statement;
  #ifndef P1
    #include "gpl_type.h"  //include in all projects except the first
  #endif
  #ifdef GRAPHICS
    #include "Window.h"
  #endif
}

// bison syntax to indicate the beginning of a C/C++ code section
%{

extern int yylex();  // prototype of function generated by flex
extern int yyerror(const char *); // used to print errors
extern int line_count;            // current line in the input; from record.l

#include "error.h"      // class for printing errors (used by gpl)
#include <iostream>
#include "gpl_type.h"
#include "Scope_manager.h"
#include "Expression.h"
#include "Constant.h"
#include "Variable.h"
// bison syntax indicating the end of a C/C++ code section
template <typename BINOP, Operator_type NM>
Expression *binary_exp(Expression *one, Expression *three, unsigned int valid_types)
{
  unsigned int lh_valid = one->type() & valid_types;
  unsigned int rh_valid = three->type() & valid_types;
  if(!lh_valid){
    Error::error(Error::INVALID_LEFT_OPERAND_TYPE, operator_to_string(NM));
  }
  if(!rh_valid){
    Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(NM));
  }
  if(lh_valid && rh_valid){
    return new BINOP(one, three);
  }
  else
  {
    delete one;
    delete three;
    return new Integer_constant(0);
  }
}

template <typename UNOP, Operator_type NM>
Expression *unary_exp(Expression *one, unsigned int valid_types) {
  
  unsigned int valid = one->type() & valid_types;
  if(!valid){
    Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(NM));
    delete one;
    return new Integer_constant(0);
  }
  else
    return new UNOP(one);
}
%} 


%destructor { delete $$; } <union_string>
// turn on verbose (longer) error messages
%define parse.error verbose

%union {
 int            union_int;
 std::string*   union_string;  // MUST be a pointer to a string
 double         union_double;
 Gpl_type       union_gpl_type;
 const Expression* 	union_expression_ptr;

};

// tokens declared here
%token T_INT                 "int"
%token T_DOUBLE              "double"
%token T_STRING              "string"
%token T_TRIANGLE            "triangle"
%token T_PIXMAP              "pixmap"
%token T_CIRCLE              "circle"
%token T_RECTANGLE           "rectangle"
%token T_TEXTBOX             "textbox"

%token T_FORWARD             "forward"
%token T_INITIALIZATION      "initialization"
%token T_TERMINATION         "termination"
%token T_ON                  "on"
%token T_ANIMATION           "animation"
%token T_IF                  "if"
%token T_FOR                 "for"
%token T_ELSE                "else"
%token <union_int> T_EXIT            "exit"  /* value is line number */
%token <union_int> T_PRINT           "print"  /* value is line number */
%token T_TRUE                "true"
%token T_FALSE               "false"

%token T_SPACE               "space"
%token T_LEFTARROW           "leftarrow"
%token T_RIGHTARROW          "rightarrow"
%token T_UPARROW             "uparrow"
%token T_DOWNARROW           "downarrow"
%token T_LEFTMOUSE_DOWN      "leftmouse_down"
%token T_MIDDLEMOUSE_DOWN    "middlemouse_down"
%token T_RIGHTMOUSE_DOWN     "rightmouse_down"
%token T_LEFTMOUSE_UP        "leftmouse_up"
%token T_MIDDLEMOUSE_UP      "middlemouse_up"
%token T_RIGHTMOUSE_UP       "rightmouse_up"
%token T_MOUSE_MOVE          "mouse_move"
%token T_MOUSE_DRAG          "mouse_drag"
%token T_F1                  "f1"
%token T_AKEY                "akey"
%token T_SKEY                "skey"
%token T_DKEY                "dkey"
%token T_FKEY                "fkey"
%token T_HKEY                "hkey"
%token T_JKEY                "jkey"
%token T_KKEY                "kkey"
%token T_LKEY                "lkey"
%token T_WKEY                "wkey"
%token T_ZKEY                "zkey"

%token T_LPAREN              "("
%token T_RPAREN              ")"
%token T_LBRACE              "{"
%token T_RBRACE              "}"
%token T_LBRACKET            "["
%token T_RBRACKET            "]"
%token T_SEMIC               ";"
%token T_COMMA               ","
%token T_PERIOD              "."

%token T_ASSIGN              "="
%token T_PLUS_ASSIGN         "+="
%token T_MINUS_ASSIGN        "-="
%token T_PLUS_PLUS           "++"
%token T_MINUS_MINUS         "--"

%token T_SIN                 "sin"
%token T_COS                 "cos"
%token T_TAN                 "tan"
%token T_ASIN                "asin"
%token T_ACOS                "acos"
%token T_ATAN                "atan"
%token T_SQRT                "sqrt"
%token T_ABS                 "abs"
%token T_FLOOR               "floor"
%token T_RANDOM              "random"

%token T_TOUCHES             "touches"
%token T_NEAR                "near"

%token T_MULTIPLY            "*"
%token T_DIVIDE              "/"
%token T_PLUS                "+"
%token T_MINUS               "-"
%token T_MOD                 "%"

%token T_LESS                "<"
%token T_GREATER             ">"
%token T_LESS_EQUAL          "<="
%token T_GREATER_EQUAL       ">="
%token T_EQUAL               "=="
%token T_NOT_EQUAL           "!="
%token T_NOT                 "!"
%token T_AND                 "&&"
%token T_OR                  "||"

%token <union_int> T_INT_CONSTANT         "int constant"
%token <union_double> T_DOUBLE_CONSTANT   "double constant"
%token <union_string> T_STRING_CONSTANT   "string constant"
%token <union_string> T_ID                "identifier"

 /* special token that does not match any production */
 /* used for characters that are not part of the language */
%token T_ERROR               "error"

%type <union_gpl_type> simple_type

%left T_MULTIPLY T_DIVIDE T_MOD
%left T_PLUS T_MINUS

%left T_LESS T_GREATER T_LESS_EQUAL T_GREATER_EQUAL
%left T_EQUAL T_NOT_EQUAL 

%left T_NEAR T_TOUCHES

%left T_OR
%left T_AND

%nonassoc T_UNARY_OPS
%nonassoc T_IF_NO_ELSE
%nonassoc T_ELSE

%type <union_expression_ptr> primary_expression
%type <union_expression_ptr> expression
%type <union_expression_ptr> optional_initializer 
%type <union_expression_ptr> variable


%%

// updated January 2019

//---------------------------------------------------------------------
program:
    declaration_list block_list
    ;

//---------------------------------------------------------------------
declaration_list:
    declaration_list declaration
    | empty
    ;

//---------------------------------------------------------------------
declaration:
    variable_declaration T_SEMIC
    | object_declaration T_SEMIC
    | forward_declaration T_SEMIC
    ;

//---------------------------------------------------------------------
variable_declaration:
    simple_type  T_ID  optional_initializer
    {
        Scope_manager& scopemgr = Scope_manager::instance();
        Expression* eptr = $3;
        Constant* cptr = (eptr==nullptr ? nullptr: eptr->evaluate());
        std::shared_ptr<Symbol> sym;
        switch($1){
            case INT:
            {
                int val;
                try{
                val=(cptr==nullptr)? 0 : cptr->as_int();
                }
                catch(Gpl_type thrown){
                Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, gpl_type_to_string(thrown), *$2, "int");
            }
                sym = std::make_shared<Symbol>(*$2, new int(val));
                break;
            }
            case DOUBLE:
            {
                double val;
                try{
                val=(cptr==nullptr)? 0.0 : cptr->as_double();
                }
            catch(Gpl_type thrown){
                Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, gpl_type_to_string(thrown), *$2, "double");
            }
            sym = std::make_shared<Symbol>(*$2, new double(val));
                break;
            }
            case STRING:
            {
                string val;
                try{
                val=(cptr==nullptr)? "" : cptr->as_string();
                }
            catch(Gpl_type thrown){
                Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, gpl_type_to_string(thrown), *$2, "string");
            }
            sym = std::make_shared<Symbol>(*$2, new std::string(val));
                break;
            }
        }
        if(scopemgr.defined_in_current_scope(*$2))
        {
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
            delete $2;
            delete $3;
            break;
        }
        scopemgr.insert(sym);
        delete $2;
        delete $3;
    }
    | simple_type  T_ID T_LBRACKET expression T_RBRACKET {
        scopemgr& scopemgr = scopemgr::instance();
        int index = 0;
        try{
            index = $4->evaluate()->as_int();
        }catch(Gpl_type thrown){
            switch(thrown){
            case DOUBLE:
            {
                Error::error(Error::ARRAY_SIZE_MUST_BE_AN_INTEGER, "double", *$2);
                break;
            }
            case STRING:
            {
                Error::error(Error::ARRAY_SIZE_MUST_BE_AN_INTEGER, "string", *$2);
                break;
            }
            }
            delete $2;
            delete $4;
            break;
        }
        if(index < 1) {
            Error::error(Error::INVALID_ARRAY_SIZE, *$2, $4->evaluate()->as_string());
            index=1;
        }
        std::shared_ptr<Symbol> sym;
        switch($1){
            case INT:
            {
                int* test = new int[index];
            for(int i = 0; i < index; i++)
                test[i] = 0;
                sym = std::make_shared<Symbol>(*$2, test, index);
                break;
            }
            case DOUBLE:
            {
            double* test = new double[index];
                for(int i = 0; i < index; i++)
                test[i] = 0.0;
                sym = std::make_shared<Symbol>(*$2, test, index);
            break;
            } 
            case STRING:
            {
                std::string* test = new std::string[index];
                for(int i = 0; i < index; i++)
                test[i] = "";
                sym = std::make_shared<Symbol>(*$2, test, index);
                break;
            }
        }
        if(scopemgr.defined_in_current_scope(*$2))
        {
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
            delete $2;
            delete $4;
            break;
        }
        scopemgr.insert(sym);
        delete $2;
        delete $4;
    }
    
    ;

//---------------------------------------------------------------------
simple_type:
    T_INT      {$$=INT;}
    | T_DOUBLE {$$=DOUBLE;}
    | T_STRING  {$$=STRING;}

//---------------------------------------------------------------------
optional_initializer:
    T_ASSIGN expression { $$ = $2; }
    | empty { $$ = NULL }
    ;

//---------------------------------------------------------------------
object_declaration:
    object_type T_ID T_LPAREN parameter_list_or_empty T_RPAREN {$2; /*change*/}
    | object_type T_ID T_LBRACKET expression T_RBRACKET {$2; /*change*/}
    ;

//---------------------------------------------------------------------
object_type:
    T_TRIANGLE
    | T_PIXMAP
    | T_CIRCLE
    | T_RECTANGLE
    | T_TEXTBOX
    ;

//---------------------------------------------------------------------
parameter_list_or_empty :
    T_LPAREN parameter_list T_RPAREN
    | T_LPAREN empty T_RPAREN
    | empty
    ;

//---------------------------------------------------------------------
parameter_list :
    parameter_list T_COMMA parameter
    | parameter
    ;

//---------------------------------------------------------------------
parameter:
    T_ID T_ASSIGN expression
    ;

//---------------------------------------------------------------------
block_list:
    block_list block
    | empty
    ;

//---------------------------------------------------------------------
block:
    initialization_block
    | termination_block
    | animation_block
    | on_block
    ;

//---------------------------------------------------------------------
initialization_block:
    T_INITIALIZATION statement_block
    ;

//---------------------------------------------------------------------
termination_block:
    T_TERMINATION statement_block
    ;

//---------------------------------------------------------------------
forward_declaration:
    T_FORWARD T_ANIMATION T_ID T_LPAREN animation_parameter T_RPAREN {$3; /*CHANGE*/}
    ;

//---------------------------------------------------------------------
animation_parameter:
    object_type T_ID {$2; /*CHANGE*/}
    | object_type
    ;

//---------------------------------------------------------------------
animation_block:
    animation_declaration statement_block
    ;

//---------------------------------------------------------------------
animation_declaration:
    T_ANIMATION T_ID T_LPAREN animation_parameter T_RPAREN T_LBRACE statement_list T_RBRACE {$2; /*CHANGE*/}
    ;

//---------------------------------------------------------------------
on_block:
    T_ON keystroke statement_block
    ;

//---------------------------------------------------------------------
keystroke:
    T_SPACE
    | T_UPARROW
    | T_DOWNARROW
    | T_LEFTARROW
    | T_RIGHTARROW
    | T_LEFTMOUSE_DOWN
    | T_MIDDLEMOUSE_DOWN
    | T_RIGHTMOUSE_DOWN
    | T_LEFTMOUSE_UP
    | T_MIDDLEMOUSE_UP
    | T_RIGHTMOUSE_UP
    | T_MOUSE_MOVE
    | T_MOUSE_DRAG
    | T_AKEY
    | T_SKEY
    | T_DKEY
    | T_FKEY
    | T_HKEY
    | T_JKEY
    | T_KKEY
    | T_LKEY
    | T_WKEY
    | T_ZKEY
    | T_F1
    ;

//---------------------------------------------------------------------
statement_or_block_of_statements:
    statement_block
    | statement
    ;

//---------------------------------------------------------------------
statement_block:
    T_LBRACE statement_list T_RBRACE
    | T_LBRACE T_RBRACE
    ;


//---------------------------------------------------------------------
statement_list:
    statement_list statement
    | statement
    ;

//---------------------------------------------------------------------
statement:
    if_statement
    | for_statement
    | assign_statement T_SEMIC
    | print_statement T_SEMIC
    | exit_statement T_SEMIC
    ;

//---------------------------------------------------------------------
if_statement:
    T_IF T_LPAREN expression T_RPAREN statement_or_block_of_statements %prec T_IF_NO_ELSE
    | T_IF T_LPAREN expression T_RPAREN statement_or_block_of_statements T_ELSE statement_or_block_of_statements
    ;

//---------------------------------------------------------------------
for_statement:
    T_FOR T_LPAREN assign_statement_or_empty T_SEMIC expression T_SEMIC assign_statement_or_empty T_RPAREN statement_or_block_of_statements
    ;

//---------------------------------------------------------------------
print_statement:
    T_PRINT T_LPAREN expression T_RPAREN
    ;

//---------------------------------------------------------------------
exit_statement:
    T_EXIT T_LPAREN expression T_RPAREN
    ;

//---------------------------------------------------------------------
assign_statement_or_empty:
    assign_statement
    | empty
    ;

//---------------------------------------------------------------------
assign_statement:
    variable T_ASSIGN expression
    | variable T_PLUS_ASSIGN expression
    | variable T_MINUS_ASSIGN expression
    | variable T_PLUS_PLUS
    | variable T_MINUS_MINUS
    ;

//---------------------------------------------------------------------
variable:
    T_ID {
        Scope_manager& scopemgr = Scope_manager::instance();
        if(!scopemgr.defined_in_current_scope(*$1))
        {
            Error::error(Error::UNDECLARED_VARIABLE, *$1);
            delete $1;
            $$ = new Integer_constant(0);
            break;
        }
        std::shared_ptr<Symbol> matching = scopemgr.lookup(*$1);
        if(matching->is_array()){
            Error::error(Error::VARIABLE_IS_AN_ARRAY, *$1);
            delete $1;
            $$ = new Integer_constant(0);
            break;
        }
        $$ = new Variable(matching);
        delete $1;
    }
    | T_ID T_LBRACKET expression T_RBRACKET {
        Scope_manager& scopemgr = Scope_manager::instance();
        if(!scopemgr.defined_in_current_scope(*$1))
        {
            Error::error(Error::UNDECLARED_VARIABLE, *$1+"[]");
            delete $1;
            delete $3;
            $$ = new Integer_constant(0);
            break;
        }
        std::shared_ptr<Symbol> matching = scopemgr.lookup(*$1);
        //if the symbol is not an array, throw an error
        if(!matching->is_array()){
            Error::error(Error::VARIABLE_NOT_AN_ARRAY, *$1);
            delete $1;
            delete $3;
            $$ = new Integer_constant(0);
            break;
        }
        Expression* expr = $3;
        switch(expr->type()){
            case DOUBLE:
            Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, *$1, "A double expression");
            delete $3;
            expr = new Integer_constant(0);
            break;
            case STRING:
            Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, *$1, "A string expression");
            delete $3;
            expr = new Integer_constant(0);
            break;
            case ANIMATION_BLOCK:
            Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, *$1, "An animation_block expression");
            delete $3;
            expr = new Integer_constant(0);
            break;
            case INT:
            break;
            default:
            //assert(false);
            std::cerr << "bad happen 12312\n";
        }
        $$ = new Variable(matching, expr);
        delete $1;
        //delete $3;
    }
    | T_ID T_PERIOD T_ID { $1; $3; /*CHANGE*/ }
    | T_ID T_LBRACKET expression T_RBRACKET T_PERIOD T_ID {$1; $6; /*CHANGE*/ }
    ;

//-------------------check this--------------------------------------------------
expression:
    primary_expression { $$ = $1; }
    | expression T_OR expression { $$ = binary_exp<Or, OR>($1, $3, INT | DOUBLE); }
    | expression T_AND expression { $$ = binary_exp<And, AND>($1, $3, INT | DOUBLE); }
    | expression T_LESS_EQUAL expression { $$ = binary_exp<Less_equal, LESS_EQUAL>($1, $3, INT | DOUBLE | STRING); }
    | expression T_GREATER_EQUAL  expression { $$ = binary_exp<Greater_equal, GREATER_EQUAL>($1, $3, INT | DOUBLE | STRING); }
    | expression T_LESS expression { $$ = binary_exp<Less_than, LESS_THAN>($1, $3, INT | DOUBLE | STRING); }
    | expression T_GREATER  expression { $$ = binary_exp<Greater_than, GREATER_THAN>($1, $3, INT | DOUBLE | STRING); }
    | expression T_EQUAL expression { $$ = binary_exp<Equal, EQUAL>($1, $3, INT | DOUBLE | STRING); }
    | expression T_NOT_EQUAL expression { $$ = binary_exp<Not_equal, NOT_EQUAL>($1, $3, INT | DOUBLE | STRING); }
    | expression T_PLUS expression { $$ = binary_exp<Plus, PLUS>($1, $3, INT | DOUBLE | STRING); }
    | expression T_MINUS expression { $$ = binary_exp<Minus, MINUS>($1, $3, INT | DOUBLE); }
    | expression T_MULTIPLY expression { $$ = binary_exp<Multiply, MULTIPLY>($1, $3, INT | DOUBLE); }
    | expression T_NEAR expression { $$ = NULL; }
    | expression T_TOUCHES expression { $$ = NULL; }
    | expression T_DIVIDE expression { 
        if(($3->type()&(INT|DOUBLE)) && ($3->evaluate()->as_double() == 0 )){
            Error::error(Error::DIVIDE_BY_ZERO_AT_PARSE_TIME);
            delete $3;
            delete $1;
            $$ = new Integer_constant(0);
        }else{
            $$ = binary_exp<Divide, DIVIDE>($1, $3, (INT|DOUBLE));
        }
    }
    | expression T_MOD expression { 
        f(($3->type()&(INT)) && ($3->evaluate()->as_int() == 0 )){
            Error::error(Error::MOD_BY_ZERO_AT_PARSE_TIME);
            delete $3;
            delete $1;
            $$ = new Integer_constant(0);
        }else{
            $$ = binary_exp<Mod, MOD>($1, $3, (INT));
        }
    }
    | T_MINUS  expression %prec T_UNARY_OPS { $$ = unary_exp<Unary_minus, UNARY_MINUS>($2, INT | DOUBLE); }
    | T_NOT  expression %prec T_UNARY_OPS { $$ = unary_exp<Not, NOT>($2, INT | DOUBLE); }
    | T_SIN T_LPAREN expression T_RPAREN { $$ = unary_exp<Sine, SIN>($3, (INT|DOUBLE));}
    | T_COS T_LPAREN expression T_RPAREN { $$ = unary_exp<Cosine, COS>($3, (INT|DOUBLE));}
    | T_TAN T_LPAREN expression T_RPAREN { $$ = unary_exp<Tan, TAN>($3, (INT|DOUBLE));}
    | T_ASIN T_LPAREN expression T_RPAREN { $$ = unary_exp<Asin, ASIN>($3, (INT|DOUBLE));}   
    | T_ACOS T_LPAREN expression T_RPAREN { $$ = unary_exp<Acos, ACOS>($3, (INT|DOUBLE));}
    | T_ATAN T_LPAREN expression T_RPAREN { $$ = unary_exp<Atan, ATAN>($3, (INT|DOUBLE));}
    | T_SQRT T_LPAREN expression T_RPAREN { $$ = unary_exp<Sqrt, SQRT>($3, (INT|DOUBLE));}
    | T_ABS T_LPAREN expression T_RPAREN { $$ = unary_exp<Abs, ABS>($3, (INT|DOUBLE));}
    | T_FLOOR T_LPAREN expression T_RPAREN { $$ = unary_exp<Floor, FLOOR>($3, (INT|DOUBLE));}
    | T_RANDOM T_LPAREN expression T_RPAREN { $$ = unary_exp<Random, RANDOM>($3, (INT|DOUBLE));}
    ;

//---------------------------------------------------------------------
primary_expression:
    T_LPAREN  expression T_RPAREN { $$ = $2; }
    | variable { $$ = 1; }
    | T_INT_CONSTANT { $$ = new Expression($1); }
    | T_TRUE { $$ = new Expression(1); }
    | T_FALSE { $$ = new Expression(0); }
    | T_DOUBLE_CONSTANT { $$ = new Expression($1); }
    | T_STRING_CONSTANT { $$ = new Expression(*$1); delete $1; }
    ;

//---------------------------------------------------------------------
empty:
    // empty goes to nothing so that you can use empty in productions
    // when you want a production to go to nothing
    ;

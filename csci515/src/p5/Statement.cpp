#include<iostream>
#include <cstdlib>
#include "Statement.h"
#include "Constant.h"
#ifdef P5
#include "Locator.h"
#endif
#include "Variable.h"
#include "Window.h"
#include "Event_manager.h"
void Statement::append_statement(Statement* atend)
{
  Statement* current=this;
  while(current->next != nullptr)
    current=current->next;
  current->next=atend;
}

//##
// NullStatement
//##
void NullStatement::execute() const
{
}

void Print::execute() const
{
    cout << "print[" << line_number << "]: ";
    cout << argument->evaluate()->as_string() << endl;
    if (next != nullptr)              next->execute();
}


Print::~Print() {
    delete argument;
}

void Assign::execute() const {
    std::shared_ptr<Locator> lhs_locator = lhs->modify();

    Gpl_type type = lhs_locator->type();

    switch (type){
        case INT:
            lhs_locator->mutate(rhs->evaluate()->as_int());
            break;
        case DOUBLE:
            lhs_locator->mutate(rhs->evaluate()->as_double());
            break;        
        case STRING:
            lhs_locator->mutate(rhs->evaluate()->as_string());
            break;
        
        default:
            assert(false);
            break;
    }
    if (next != nullptr)              next->execute();
}

Assign::~Assign() {
    delete lhs;
    delete rhs;
}

void Plus_assign::execute() const {
    std::shared_ptr<Locator> lhs_locator = lhs->modify();

    Gpl_type type = lhs_locator->type();

    switch (type){
        case INT:
            lhs_locator->mutate(lhs->evaluate()->as_int() + rhs->evaluate()->as_int());
            break;
        case DOUBLE:
            lhs_locator->mutate(lhs->evaluate()->as_double() + rhs->evaluate()->as_double());
            break;        
        case STRING:
            lhs_locator->mutate(lhs->evaluate()->as_string() + rhs->evaluate()->as_string());
            break;
        
        default:
            assert(false);
    }
    if (next != nullptr)              next->execute();
}

Plus_assign::~Plus_assign() {
    delete lhs;
    delete rhs;
}

void Minus_assign::execute() const {
    std::shared_ptr<Locator> lhs_locator = lhs->modify();

    Gpl_type type = lhs_locator->type();

    switch (type){
        case INT:
            lhs_locator->mutate(lhs->evaluate()->as_int() - rhs->evaluate()->as_int());
            break;
        case DOUBLE:
            lhs_locator->mutate(lhs->evaluate()->as_double() - rhs->evaluate()->as_double());
            break;  
        
        default:
            assert(false);
    }
    if (next != nullptr)              next->execute();
}

Minus_assign::~Minus_assign() {
    delete lhs;
    delete rhs;
}

void Plus_plus::execute() const {
    std::shared_ptr<Locator> lhs_locator = lhs->modify();

    Gpl_type type = lhs_locator->type();

    switch (type){
        case INT:
            lhs_locator->mutate(lhs->evaluate()->as_int() + 1);
            break;     
        
        default:
            assert(false);
    }
    if (next != nullptr)              next->execute();
}

Plus_plus::~Plus_plus() {
    delete lhs;
}

void Minus_minus::execute() const {
    std::shared_ptr<Locator> lhs_locator = lhs->modify();

    Gpl_type type = lhs_locator->type();

    switch (type){
        case INT:
            lhs_locator->mutate(lhs->evaluate()->as_int() - 1);
            break;     
        
        default:
            assert(false);
    }
    if (next != nullptr)              next->execute();
}

Minus_minus::~Minus_minus() {
    delete lhs;
}

void If::execute() const {
    if (exp->evaluate()->as_int())  s_if->execute();
    else {
        if (s_else) {
            s_else->execute();
        }
    }
    if (next != nullptr)              next->execute();
}

If::~If() {
    delete exp;
    delete s_if;
    delete s_else;
}

void For::execute() const {
    s_init->execute();
    
    while (s_cond->evaluate()->as_int()) {
        s_body->execute();
        s_inc->execute();
    }
    if (next != nullptr)              next->execute();
}

For::~For() {
    delete s_init;
    delete s_cond;
    delete s_inc;
    delete s_body;
}

void Exit::execute() const
{
    cout << "gpl[" << line_number << "]: exit(" << argument->evaluate()->as_int() << endl;
    exit(argument->evaluate()->as_int());
    if (next != nullptr)              next->execute();
}

Exit::~Exit() {
    delete argument;
}
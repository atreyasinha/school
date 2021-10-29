#include <iostream>

#include "Symbol.h"
    
//for double variable
Symbol::Symbol(const std::string& n, double* v):
    name(n), 
    value(value), 
    type(DOUBLE), 
    count(0) {}

//for double array
Symbol::Symbol(const std::string& n, double* v, int c):
    name(n), 
    value(value), 
    type(DOUBLE), 
    count(c) {}      

//for int variable
Symbol::Symbol(const std::string& n, int* v):
    name(n), 
    value(v), 
    type(INT), 
    count(0) {}                       

//for int array
Symbol::Symbol(const std::string& n, int* v, int c):
    name(n), 
    value(v), 
    type(INT), 
    count(c) {}             

//for string variable
Symbol::Symbol(const std::string& n, std::string* v):
    name(n), 
    value(v), 
    type(STRING), 
    count(0) {}            

//for string array
Symbol::Symbol(const std::string& n, std::string* v, int c):
    name(n), 
    value(v), 
    type(STRING), 
    count(c) {}      

Gpl_type Symbol::get_type() const {
    return type;
}

std::string Symbol::get_name() const {
    return name;
}

bool is_an_array() {
    return 0;
}

int Symbol::get_count(){
  if(type < 1024)
    return -1;
  return count;
}

int Symbol::int_at(int index){
  if(type < 1024)
    return *value.int_pointer;
  return value.int_pointer[index];
}
double Symbol::double_at(int index){
  if(type < 1024)
    return *value.double_pointer;
  return value.double_pointer[index];
}
std::string Symbol::string_at(int index){
  if(type < 1024)
    return *value.string_pointer;
  return value.string_pointer[index];
}

Symbol::~Symbol() {
    switch (type) {
        case INT:
            if (count == 0) delete value.int_pointer;
            else delete[] value.int_pointer;
            break;
        case DOUBLE:
            if (count == 0) delete value.double_pointer;
            else delete[] value.double_pointer;
            break;
        case STRING:
            if (count == 0) delete value.string_pointer;
            else delete[] value.double_pointer;
            break;
        
        default:
            break;
    }
}

std::ostream& operator<<(std::ostream& os, const Symbol& sb) {
    switch (sb.type) {
        case INT:
            os << "int " << sb.name << " = " << *sb.value.int_pointer << '\n'; 
            break;
        case DOUBLE:
            os << "double " << sb.name << " = " << *sb.value.double_pointer << '\n'; 
            break;
        case STRING:
            os << "string " << sb.name << " = \"" << *sb.value.string_pointer << "\"\n";
            break;
        default:
            break;
    }

    return os;
}


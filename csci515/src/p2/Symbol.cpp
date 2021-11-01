#include <iostream>

#include "Symbol.h"
    
//for double variable
Symbol::Symbol(const std::string& n, double* v):
    name(n), 
    value(v), 
    type(DOUBLE), 
    count(0) {}

//for double array
Symbol::Symbol(const std::string& n, double* v, int c):
    name(n), 
    value(v), 
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
            else delete[] value.string_pointer;
            break;
        default:
            break;
    }
}

std::ostream& operator<<(std::ostream& os, const Symbol& sb) {
    switch (sb.type) {
        case INT:
            if (sb.count == 0) os << gpl_type_to_string(sb.type) << " " << sb.name << " = " << *sb.value.int_pointer << '\n';
            else for (int i = 0; i < sb.count; i++) os << gpl_type_to_string(sb.type) << " " << sb.name << "[" << i << "]" << " = " << sb.value.int_pointer[i] << '\n';
            break;
        case DOUBLE:
            if (sb.count == 0) os << gpl_type_to_string(sb.type) << " " << sb.name << " = " << *sb.value.double_pointer << '\n';
            else for (int i = 0; i < sb.count; i++) os << gpl_type_to_string(sb.type) << " " << sb.name << "[" << i << "]" << " = " << sb.value.double_pointer[i] << '\n';
            break;
        case STRING:
            if (sb.count == 0) os << gpl_type_to_string(sb.type) << " " << sb.name << " = " << "\"" << *sb.value.string_pointer << "\"" << '\n';
            else for (int i = 0; i < sb.count; i++) os << gpl_type_to_string(sb.type) << " " << sb.name << "[" << i << "]" << " = " << "\"" << sb.value.string_pointer[i] << "\"" << '\n';
            break;
        default:
            break;
    }
    
    return os;
}
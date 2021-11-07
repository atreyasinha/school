#include <iostream>

#include "Symbol.h"
#include "error.h"

#include "Game_object.h"

#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "Pixmap.h"
#include "Textbox.h"
    
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



//for Rectangle variable
Symbol::Symbol(const std::string& n, Rectangle* v):
    name(n), 
    value(v), 
    type(RECTANGLE), 
    count(0) {}            

//for Rectangle array
Symbol::Symbol(const std::string& n, Rectangle* v, int c):
    name(n), 
    value(v), 
    type(RECTANGLE), 
    count(c) {} 

//for Circle variable
Symbol::Symbol(const std::string& n, Circle* v):
    name(n), 
    value(v), 
    type(CIRCLE), 
    count(0) {}            

//for Circle array
Symbol::Symbol(const std::string& n, Circle* v, int c):
    name(n), 
    value(v), 
    type(CIRCLE), 
    count(c) {} 
    
//for Triangle variable
Symbol::Symbol(const std::string& n, Triangle* v):
    name(n), 
    value(v), 
    type(TRIANGLE), 
    count(0) {}            

//for Triangle array
Symbol::Symbol(const std::string& n, Triangle* v, int c):
    name(n), 
    value(v), 
    type(TRIANGLE), 
    count(c) {} 
    
//for Pixmap variable
Symbol::Symbol(const std::string& n, Pixmap* v):
    name(n), 
    value(v), 
    type(PIXMAP), 
    count(0) {}            

//for Pixmap array
Symbol::Symbol(const std::string& n, Pixmap* v, int c):
    name(n), 
    value(v), 
    type(PIXMAP), 
    count(c) {} 

//for Textbox variable
Symbol::Symbol(const std::string& n, Textbox* v):
    name(n), 
    value(v), 
    type(TEXTBOX), 
    count(0) {}            

//for Textbox array
Symbol::Symbol(const std::string& n, Textbox* v, int c):
    name(n), 
    value(v), 
    type(TEXTBOX), 
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
        case RECTANGLE:
            if (count == 0) delete value.rectangle_pointer;
            else delete[] value.rectangle_pointer;
            break;
        case CIRCLE:
            if (count == 0) delete value.circle_pointer;
            else delete[] value.circle_pointer;
            break;
        case TRIANGLE:
            if (count == 0) delete value.triangle_pointer;
            else delete[] value.triangle_pointer;
            break;
        case PIXMAP:
            if (count == 0) delete value.pixmap_pointer;
            else delete[] value.pixmap_pointer;
            break;
        case TEXTBOX:
            if (count == 0) delete value.textbox_pointer;
            else delete[] value.textbox_pointer;
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
        case RECTANGLE:
            if (sb.count == 0) os << gpl_type_to_string(sb.type) << " " << sb.name << *sb.value.rectangle_pointer << '\n';
            else for (int i = 0; i < sb.count; i++) os << gpl_type_to_string(sb.type) << " " << sb.name << "[" << i << "]" << sb.value.rectangle_pointer[i] << '\n';
            break;
        case CIRCLE:
            if (sb.count == 0) os << gpl_type_to_string(sb.type) << " " << sb.name << *sb.value.circle_pointer << '\n';
            else for (int i = 0; i < sb.count; i++) os << gpl_type_to_string(sb.type) << " " << sb.name << "[" << i << "]" << sb.value.circle_pointer[i] << '\n';
            break;
        case TRIANGLE:
            if (sb.count == 0) os << gpl_type_to_string(sb.type) << " " << sb.name << *sb.value.triangle_pointer << '\n';
            else for (int i = 0; i < sb.count; i++) os << gpl_type_to_string(sb.type) << " " << sb.name << "[" << i << "]" << sb.value.triangle_pointer[i] << '\n';
            break;
        case PIXMAP:
            if (sb.count == 0) os << gpl_type_to_string(sb.type) << " " << sb.name << *sb.value.pixmap_pointer << '\n';
            else for (int i = 0; i < sb.count; i++) os << gpl_type_to_string(sb.type) << " " << sb.name << "[" << i << "]" << sb.value.pixmap_pointer[i] << '\n';
            break;
        case TEXTBOX:
            if (sb.count == 0) os << gpl_type_to_string(sb.type) << " " << sb.name << *sb.value.textbox_pointer << '\n';
            else for (int i = 0; i < sb.count; i++) os << gpl_type_to_string(sb.type) << " " << sb.name << "[" << i << "]" << sb.value.textbox_pointer[i] << '\n';
            break;

        default:
            break;
    }
    
    return os;
}

bool Symbol::is_array() {
    if (count) return true;
    return false;
}

const Constant* Symbol::as_constant() const {
    switch (type) {
        case INT:
            return new Integer_constant(*value.int_pointer);
        case DOUBLE:
            return new Double_constant(*value.double_pointer);
        case STRING:
            return new String_constant(*value.string_pointer);

        default:
            throw type;
    }
}

const Constant* Symbol::as_constant(int index) const {
    if (index < 0 || index > count - 1)     return NULL;

    switch (type) {
        case INT:
            return new Integer_constant(value.int_pointer[index]);
        case DOUBLE:
            return new Double_constant(value.double_pointer[index]);
        case STRING:
            return new String_constant(value.string_pointer[index]);

        default:
            throw type;
    }
}

const Constant* Symbol::as_constant(const std::string& attribute_name) const {
    switch (type) {
        case RECTANGLE:
            return new Game_attribute_constant(value.rectangle_pointer, attribute_name);
        case CIRCLE:
            return new Game_attribute_constant(value.circle_pointer, attribute_name);
        case TRIANGLE:
            return new Game_attribute_constant(value.triangle_pointer, attribute_name);
        case PIXMAP:
            return new Game_attribute_constant(value.pixmap_pointer, attribute_name);
        case TEXTBOX:
            return new Game_attribute_constant(value.textbox_pointer, attribute_name);

        default:
            throw type;
    }
}

const Constant* Symbol::as_constant(int index, const std::string& attribute_name) const {
    if (index < 0 || index > count - 1)     return NULL;

    switch (type) {
        case RECTANGLE:
            return new Game_attribute_constant(value.rectangle_pointer + index, attribute_name);
        case CIRCLE:
            return new Game_attribute_constant(value.circle_pointer + index, attribute_name);
        case TRIANGLE:
            return new Game_attribute_constant(value.triangle_pointer + index, attribute_name);
        case PIXMAP:
            return new Game_attribute_constant(value.pixmap_pointer + index, attribute_name);
        case TEXTBOX:
            return new Game_attribute_constant(value.textbox_pointer + index, attribute_name);

        default:
            throw type;
    }
}
//File: Constant.cpp
#include "Constant.h"

Gpl_type  Constant::type() const 
{ return intrinsic_type; }

const Constant* Constant::evaluate() const
{ return this; }

int Game_attribute_constant::as_int() const { 
    int init = 0;

    if (gop->attribute_type(attribute_name) == INT) {
        gop->read_attribute(attribute_name, init);    
        return init;
    }

    throw Constant::type();
}

double Game_attribute_constant::as_double() const { 
    double double_init = 0;
    if (gop->attribute_type(attribute_name) == DOUBLE) {
        gop->read_attribute(attribute_name, double_init);    
        return double_init;
    }

    int int_init = 0;
    if (gop->attribute_type(attribute_name) == INT) {
        gop->read_attribute(attribute_name, int_init);    
        return (double) int_init;
    }
 
    throw Constant::type();
}

std::string Game_attribute_constant::as_string() const { 
    std::string init = "";
    
    if (gop->attribute_type(attribute_name) == STRING) {
        gop->read_attribute(attribute_name, init);    
        return init;
    }

    double double_init = 0;
    if (gop->attribute_type(attribute_name) == DOUBLE) {
        gop->read_attribute(attribute_name, double_init);    
        return std::to_string(double_init);
    }

    int int_init = 0;
    if (gop->attribute_type(attribute_name) == INT) {
        gop->read_attribute(attribute_name, int_init);    
        return std::to_string(int_init);
    }
    
    throw Constant::type();
}
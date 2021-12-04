#include <iostream>
#include "Member_variable.h"
#include "error.h"

Member_variable::Member_variable(const std::string& symbol_name, const std::string& attribute_name): 
    Variable(symbol_name), attribute(attribute_name) {}

Member_variable::Member_variable(const std::string& symbol_name, const Expression* index_expr, const std::string& attribute_name): 
    Variable(symbol_name, index_expr), attribute(attribute_name) {}

Gpl_type Member_variable::type() const { 
    if (symbol_name.empty()) return INT;
    return symbol()->as_constant(attribute)->type();
}

std::string Member_variable::name() const { 
    return (symbol_name == "") ? "" : symbol_name + "." + attribute; 
}

const Constant* Member_variable::evaluate() const { 
    if (symbol_name.empty())                        return ret(new Game_attribute_constant(0, ""));

    if (array_index_expression) {
        int index_constant = array_index_expression->evaluate()->as_int();
        const Constant* ptr = symbol()->as_constant(index_constant, attribute);

        if (ptr)                                    return ret(ptr);

        Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, symbol()->get_name(), std::to_string(index_constant));
        return ret(symbol()->as_constant(0, attribute));
    } 
    
    return ret(symbol()->as_constant(attribute));  
}

std::shared_ptr<Locator> Member_variable::modify() const { 
    if (array_index_expression) {
        int index_constant = array_index_expression->evaluate()->as_int();
        std::shared_ptr<Locator> ptr = symbol()->as_lvalue(index_constant, attribute);

        if (ptr)                                    return ptr;

        Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, symbol()->get_name(), std::to_string(index_constant));
        return symbol()->as_lvalue(0, attribute);
    } 
    
    return symbol()->as_lvalue(attribute);
}
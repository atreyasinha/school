#include <iostream>

#include "Variable.h"
#include "Symbol.h"
#include "Constant.h"
#include "error.h"
#include <cassert>
#include <string>

Variable::Variable(const std::string& symbol_name): 
    symbol_name(symbol_name), array_index_expression(nullptr) {}

Variable::Variable(const std::string& symbol_name, const Expression* index_expr): 
    symbol_name(symbol_name), array_index_expression(index_expr) {}

Variable::~Variable() {
    delete array_index_expression;
}
    
Gpl_type Variable::type() const { 
    if (symbol_name.empty()) return INT;
    return symbol()->get_type();
}

const Constant* Variable::evaluate() const {
    if (symbol_name == "")          return ret(new Integer_constant(0));

    if (array_index_expression) {
        int index_constant = array_index_expression->evaluate()->as_int();
        const Constant* ptr = symbol()->as_constant(index_constant);

        if (ptr)                    return ret(ptr);

        Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, symbol()->get_name(), std::to_string(index_constant));
        return ret(symbol()->as_constant(0));
    }

    return ret(symbol()->as_constant());  
}


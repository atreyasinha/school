#include <iostream>
#include "error.h"
#include <string>
#include "Variable.h"
#include "Expression.h"
#include "Constant.h"

Variable::Variable(const std::string& symbol_name) 
    : symbol_name(symbol_name), array_index_expression(nullptr){

}

Variable::Variable(const std::string& symbol_name, const Expression* index_expr)
    : symbol_name(symbol_name), array_index_expression(index_expr){

}

const Constant *Variable::evaluate() const {
  if(symbol()->is_an_array()){
    const Constant *cindex = array_index_expression->evaluate();
    int index = 0;
    try{
      index = cindex->as_int();
    }catch(...){
      try{
        cindex->as_double();
        Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, symbol()->get_name(), "A double expression");
      }catch(...){
        Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, symbol()->get_name(), "A string expression");
      }
      return ret(new Integer_constant(0));
    }
    if(index < 0 || index > symbol()->get_count()-1){
      Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, symbol()->get_name() , std::to_string(index));
      delete array_index_expression;
      return ret(new Integer_constant(0));
    }
    delete array_index_expression;
    switch(symbol()->get_type() ^ 1024){
      case INT:
      {
        return ret(new Integer_constant(symbol()->int_at(index)));
      }
      case DOUBLE:
      {
        return ret(new Double_constant(symbol()->double_at(index)));
      }
      case STRING:
      {
        return ret(new String_constant(symbol()->string_at(index)));
      }
      default:
      {
        std::cerr << "Invalid variable type " << symbol()->get_type() << " detected\n";
        return ret(new Integer_constant(0));
      }
    }
  }else{
    switch(symbol()->get_type()){
      case INT:
      {
        return ret(new Integer_constant(symbol()->int_at(1)));
      }
      case DOUBLE:
      {
        return ret(new Double_constant(symbol()->double_at(1)));
      }
      case STRING:
      {
        return ret(new String_constant(symbol()->string_at(1)));
      }
      default:
      {
      }
    }
  }
  return ret(new Integer_constant(0));
}

Gpl_type Variable::type() const {
    return symbol()->get_type();
}
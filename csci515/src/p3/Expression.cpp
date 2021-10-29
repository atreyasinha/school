// File: Expression.cpp
#include "Expression.h"
#include "Constant.h"
#include "error.h"
#include<string>
#include <cmath>
using std::string;

Expression::~Expression(){delete evaluated_constant;}

// This wrapper ensures that Constant objects created by evaluate() are
// properly released when a subsequent call to evaluate() will otherwise
// overwrite the pointer.
const Constant* Expression::ret(const Constant* new_evald_constant) const
{
  delete evaluated_constant;
  return evaluated_constant=new_evald_constant;
}
/**********************************************/
/************* Other operators ****************/
/**********************************************/
Gpl_type Plus::type() const
{
  Gpl_type lht = lhs->type();
  Gpl_type rht = rhs->type();
  if (lht == STRING || rht == STRING) return STRING;
  if (lht == DOUBLE || rht == DOUBLE) return DOUBLE;
  return INT;
}

const Constant* Plus::evaluate() const
{
  Gpl_type lht = lhs->type();
  Gpl_type rht = rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if (lht == STRING || rht == STRING) return ret(new String_constant(lhs_constant->as_string() + rhs_constant->as_string()));
  if (lht == DOUBLE || rht == DOUBLE) return ret(new Double_constant(lhs_constant->as_double() + rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() + rhs_constant->as_int()));
}

Gpl_type Multiply::type() const
{
  Gpl_type lht = lhs->type();
  Gpl_type rht = rhs->type();
  if (lht == DOUBLE || rht == DOUBLE) return DOUBLE;
  return INT;
}

const Constant* Multiply::evaluate() const
{
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if (lhs->type() == DOUBLE || rhs->type() == DOUBLE) return ret(new Double_constant(lhs_constant->as_double() * rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() * rhs_constant->as_int()));
}



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

const Constant* Plus::evaluate() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==STRING || rht==STRING)
    return ret(new String_constant(lhs_constant->as_string() + //<--addition
                                   rhs_constant->as_string()));
  if(lht==DOUBLE || rht==DOUBLE)
    return ret(new Double_constant(lhs_constant->as_double() + //<--addition
                                   rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() +     //<--addition
                                  rhs_constant->as_int()));
}

Gpl_type Plus::type() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  if(lht==STRING || rht==STRING)
    return STRING;
  if(lht==DOUBLE || rht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* Minus::evaluate() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==DOUBLE || rht==DOUBLE)
    return ret(new Double_constant(lhs_constant->as_double() - //<--subtraction
                                   rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() -     //<--subtraction
                                  rhs_constant->as_int()));
}

Gpl_type Minus::type() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  if(lht==STRING || rht==STRING)
    return STRING;
  if(lht==DOUBLE || rht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* Multiply::evaluate() const
{
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lhs->type()==DOUBLE || rhs->type()==DOUBLE)
    return ret(new Double_constant(lhs_constant->as_double() * //<--multiply
                                   rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() *     //<--multiply
                                  rhs_constant->as_int()));
}

Gpl_type Multiply::type() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  if(lht==STRING || rht==STRING)
    return STRING;
  if(lht==DOUBLE || rht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* Divide::evaluate() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==DOUBLE || rht==DOUBLE)
    return ret(new Double_constant(lhs_constant->as_double() / //<--divide
                                   rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() /     //<--divide
                                  rhs_constant->as_int()));
}

Gpl_type Divide::type() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  if(lht==STRING || rht==STRING)
    return STRING;
  if(lht==DOUBLE || rht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* Mod::evaluate() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  return ret(new Integer_constant(lhs_constant->as_int() % rhs_constant->as_int()));
}

Gpl_type Mod::type() const
{
    Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  if(lht==STRING || rht==STRING)
    return STRING;
  if(lht==DOUBLE || rht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* And::evaluate() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==DOUBLE || rht==DOUBLE)
    return ret(new Double_constant(lhs_constant->as_double() && rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() && rhs_constant->as_int()));
}

Gpl_type And::type() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  if(lht==STRING || rht==STRING)
    return STRING;
  if(lht==DOUBLE || rht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* Or::evaluate() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==DOUBLE || rht==DOUBLE)
    return ret(new Double_constant(lhs_constant->as_double() || rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() || rhs_constant->as_int()));
}

Gpl_type Or::type() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  if(lht==STRING || rht==STRING)
    return STRING;
  if(lht==DOUBLE || rht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* Less_than::evaluate() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==DOUBLE || rht==DOUBLE)
    return ret(new Double_constant(lhs_constant->as_double() < rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() < rhs_constant->as_int()));
}

Gpl_type Less_than::type() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  if(lht==STRING || rht==STRING)
    return STRING;
  if(lht==DOUBLE || rht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* Greater_than::evaluate() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==DOUBLE || rht==DOUBLE)
    return ret(new Double_constant(lhs_constant->as_double() > rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() > rhs_constant->as_int()));
}

Gpl_type Greater_than::type() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  if(lht==STRING || rht==STRING)
    return STRING;
  if(lht==DOUBLE || rht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* Less_equal::evaluate() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==DOUBLE || rht==DOUBLE)
    return ret(new Double_constant(lhs_constant->as_double() <= rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() <= rhs_constant->as_int()));
}

Gpl_type Less_equal::type() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  if(lht==STRING || rht==STRING)
    return STRING;
  if(lht==DOUBLE || rht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* Greater_equal::evaluate() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==DOUBLE || rht==DOUBLE)
    return ret(new Double_constant(lhs_constant->as_double() >= rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() >= rhs_constant->as_int()));
}

Gpl_type Greater_equal::type() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  if(lht==STRING || rht==STRING)
    return STRING;
  if(lht==DOUBLE || rht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* Equal::evaluate() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==DOUBLE || rht==DOUBLE)
    return ret(new Double_constant(lhs_constant->as_double() == rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() == rhs_constant->as_int()));
}

Gpl_type Equal::type() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  if(lht==STRING || rht==STRING)
    return STRING;
  if(lht==DOUBLE || rht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* Not_Equal::evaluate() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==DOUBLE || rht==DOUBLE)
    return ret(new Double_constant(lhs_constant->as_double() != rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() != rhs_constant->as_int()));
}

Gpl_type Not_Equal::type() const
{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  if(lht==STRING || rht==STRING)
    return STRING;
  if(lht==DOUBLE || rht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* Not::evaluate() const
{
  Gpl_type lht=lhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  if(lht==DOUBLE)
    return ret(new Double_constant(!lhs_constant->as_double()));
  return ret(new Integer_constant(!lhs_constant->as_int()));
}

Gpl_type Not::type() const
{
  Gpl_type lht=lhs->type();
  if(lht==STRING)
    return STRING;
  if(lht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* Cosine::evaluate() const
{
  Gpl_type lht=lhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  if(lht==DOUBLE)
    return ret(new Double_constant(cos(lhs_constant->as_double()*M_PI/180)));
}

Gpl_type Cosine::type() const
{
  Gpl_type lht=lhs->type();
  if(lht==STRING)
    return STRING;
  if(lht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* Sine::evaluate() const
{
  Gpl_type lht=lhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  if(lht==DOUBLE)
    return ret(new Double_constant(sin(lhs_constant->as_double()*M_PI/180)));
}

Gpl_type Sine::type() const
{
  Gpl_type lht=lhs->type();
  if(lht==STRING)
    return STRING;
  if(lht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* Tan::evaluate() const
{
  Gpl_type lht=lhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  if(lht==DOUBLE)
    return ret(new Double_constant(tan(lhs_constant->as_double()*M_PI/180)));
}

Gpl_type Tan::type() const
{
  Gpl_type lht=lhs->type();
  if(lht==STRING)
    return STRING;
  if(lht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* Acos::evaluate() const
{
  Gpl_type lht=lhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  if(lht==DOUBLE)
    return ret(new Double_constant(acos(lhs_constant->as_double()*M_PI/180)));
}

Gpl_type Acos::type() const
{
  Gpl_type lht=lhs->type();
  if(lht==STRING)
    return STRING;
  if(lht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* Asin::evaluate() const
{
  Gpl_type lht=lhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  if(lht==DOUBLE)
    return ret(new Double_constant(asin(lhs_constant->as_double()*M_PI/180)));
}

Gpl_type Asin::type() const
{
  Gpl_type lht=lhs->type();
  if(lht==STRING)
    return STRING;
  if(lht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* Atan::evaluate() const
{
  Gpl_type lht=lhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  if(lht==DOUBLE)
    return ret(new Double_constant(atan(lhs_constant->as_double()*M_PI/180)));
}

Gpl_type Atan::type() const
{
  Gpl_type lht=lhs->type();
  if(lht==STRING)
    return STRING;
  if(lht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* Sqrt::evaluate() const
{
  Gpl_type lht=lhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  if(lht==DOUBLE)
    return ret(new Double_constant(sqrt(lhs_constant->as_double())));
}

Gpl_type Sqrt::type() const
{
  Gpl_type lht=lhs->type();
  if(lht==STRING)
    return STRING;
  if(lht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* Abs::evaluate() const
{
  Gpl_type lht=lhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  if(lht==DOUBLE)
    return ret(new Double_constant(fabs(lhs_constant->as_double())));
  return ret(new Integer_constant(abs(lhs_constant->as_int())));
}

Gpl_type Abs::type() const
{
  Gpl_type lht=lhs->type();
  if(lht==STRING)
    return STRING;
  if(lht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* Floor::evaluate() const
{
  Gpl_type lht=lhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  double value = lhs_constant->as_double();
  if(lht==DOUBLE)
    if (value < 0) {
      value--;
    }
    return ret(new Double_constant(value));
  return ret(new Integer_constant(value));
}

Gpl_type Floor::type() const
{
  Gpl_type lht=lhs->type();
  if(lht==STRING)
    return STRING;
  if(lht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* Random::evaluate() const
{
  Gpl_type lht=lhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  int value;

  try
  {
    value = lhs_constant->as_int();
  }
  catch(...)
  {
    value = floor(lhs_constant->as_double());
  }
  if(value < 2) {
    Error::error(Error::INVALID_ARGUMENT_FOR_RANDOM, lhs_constant->as_string());
    value = 2;
  }

  return ret(new Integer_constant(rand() % value));
}

Gpl_type Random::type() const
{
  Gpl_type lht=lhs->type();
  if(lht==STRING)
    return STRING;
  if(lht==DOUBLE)
    return DOUBLE;
  return INT;
}




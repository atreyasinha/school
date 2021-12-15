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
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();
  try{
    return ret(new Integer_constant(lhs_constant->as_int() + rhs_constant->as_int()));
    } catch(...) { 
      try {
        return ret(new Double_constant(lhs_constant->as_double() + rhs_constant->as_double()));
      } catch(...) {  
        return ret(new String_constant(lhs_constant->as_string() + rhs_constant->as_string()));
    }
  }
}

Gpl_type Plus::type() const
{
  Gpl_type lht = lhs->type();
  Gpl_type rht = rhs->type();
  if (lht == STRING || rht == STRING) return STRING;
  if (lht == DOUBLE || rht == DOUBLE) return DOUBLE;
  return INT;
}

// const Constant* Question::evaluate() const
// {
//   const Constant* lhs_constant = lhs->evaluate();
//   const Constant* rhs_constant = rhs->evaluate();
//   try{
//     return ret(new Integer_constant(lhs_constant->as_int()  rhs_constant->as_int()));
//     } catch(...) { 
//       try {
//         return ret(new Double_constant(lhs_constant->as_double()  rhs_constant->as_double()));
//       } catch(...) {  
//         return ret(new String_constant(lhs_constant->as_string()  rhs_constant->as_string()));
//     }
//   }
// }

// Gpl_type Question::type() const
// {
//   Gpl_type lht = lhs->type();
//   Gpl_type rht = rhs->type();
//   if (lht == STRING || rht == STRING) return STRING;
//   if (lht == DOUBLE || rht == DOUBLE) return DOUBLE;
//   return INT;
// }

const Constant* Minus::evaluate() const
{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();
  try {
    return ret(new Integer_constant(lhs_constant->as_int() - rhs_constant->as_int()));
  } catch(...) { 
    return ret(new Double_constant(lhs_constant->as_double() - rhs_constant->as_double()));
  }
}

Gpl_type Minus::type() const
{
  Gpl_type lht = lhs->type();
  Gpl_type rht = rhs->type();
  if (lht == STRING || rht == STRING) return STRING;
  if (lht == DOUBLE || rht == DOUBLE) return DOUBLE;
  return INT;
}

const Constant* Multiply::evaluate() const
{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();
  try {
    return ret(new Integer_constant(lhs_constant->as_int() * rhs_constant->as_int()));
  } catch(...) {
    return ret(new Double_constant(lhs_constant->as_double() * rhs_constant->as_double()));
  }
}

Gpl_type Multiply::type() const
{
  Gpl_type lht = lhs->type();
  Gpl_type rht = rhs->type();
  if (lht == STRING || rht == STRING) return STRING;
  if (lht == DOUBLE || rht == DOUBLE) return DOUBLE;
  return INT;
}

const Constant* Divide::evaluate() const
{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();
  try {
    return ret(new Integer_constant(lhs_constant->as_int() / rhs_constant->as_int()));
  } catch(...) {
    return ret(new Double_constant(lhs_constant->as_double() / rhs_constant->as_double()));
  }
}

Gpl_type Divide::type() const
{
  Gpl_type lht = lhs->type();
  Gpl_type rht = rhs->type();
  if (lht == STRING || rht == STRING) return STRING;
  if (lht == DOUBLE || rht == DOUBLE) return DOUBLE;
  return INT;
}

const Constant* Mod::evaluate() const
{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();
  return ret(new Integer_constant(lhs_constant->as_int() % rhs_constant->as_int()));
}

Gpl_type Mod::type() const
{
  Gpl_type lht = lhs->type();
  Gpl_type rht = rhs->type();
  if (lht == STRING || rht == STRING) return STRING;
  if (lht == DOUBLE || rht == DOUBLE) return DOUBLE;
  return INT;
}

const Constant* Less_Than::evaluate() const
{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();
  try {
    return ret(new Integer_constant(lhs_constant->as_int() < rhs_constant->as_int()));
  } catch(...) { 
      try {
        return ret(new Integer_constant(lhs_constant->as_double() < rhs_constant->as_double()));
      } catch (...) {  
        return ret(new Integer_constant(lhs_constant->as_string() < rhs_constant->as_string()));
      }
  }
}

Gpl_type Less_Than::type() const
{
  return INT;
}

const Constant* Greater_Than::evaluate() const
{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();
  try {
    return ret(new Integer_constant(lhs_constant->as_int() > rhs_constant->as_int()));
  } catch(...) {
      try { 
        return ret(new Integer_constant(lhs_constant->as_double() > rhs_constant->as_double()));
      } catch (...) { 
        return ret(new Integer_constant(lhs_constant->as_string() > rhs_constant->as_string()));
      }
  }
}

Gpl_type Greater_Than::type() const
{
  Gpl_type lht = lhs->type();
  Gpl_type rht = rhs->type();
  if (lht == STRING || rht == STRING) return STRING;
  if (lht == DOUBLE || rht == DOUBLE) return DOUBLE;
  return INT;
}

const Constant* Less_Equal::evaluate() const
{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();
  try{
    return ret(new Integer_constant(lhs_constant->as_int() <= rhs_constant->as_int()));
  }catch(...){ try{
    return ret(new Integer_constant(lhs_constant->as_double() <= rhs_constant->as_double()));
  }catch(...){
    return ret(new Integer_constant(lhs_constant->as_string() <= rhs_constant->as_string()));
  }
  }
}

Gpl_type Less_Equal::type() const
{
  Gpl_type lht = lhs->type();
  Gpl_type rht = rhs->type();
  if (lht == STRING || rht == STRING) return STRING;
  if (lht == DOUBLE || rht == DOUBLE) return DOUBLE;
  return INT;
}

const Constant* Greater_Equal::evaluate() const
{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();
  try {
    return ret(new Integer_constant(lhs_constant->as_int() >= rhs_constant->as_int()));
  } catch(...) { 
      try {
        return ret(new Integer_constant(lhs_constant->as_double() >= rhs_constant->as_double()));
      } catch(...) {
        return ret(new Integer_constant(lhs_constant->as_string() >= rhs_constant->as_string()));
    }
  } 
}

Gpl_type Greater_Equal::type() const
{
  Gpl_type lht = lhs->type();
  Gpl_type rht = rhs->type();
  if (lht == STRING || rht == STRING) return STRING;
  if (lht == DOUBLE || rht == DOUBLE) return DOUBLE;
  return INT;
}

const Constant* Not_Equal::evaluate() const
{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();
  try {
    return ret(new Integer_constant(lhs_constant->as_int() != rhs_constant->as_int()));
  } catch(...) { 
      try {
        return ret(new Integer_constant(lhs_constant->as_double() != rhs_constant->as_double()));
      } catch(...) {  
        return ret(new Integer_constant(lhs_constant->as_string() != rhs_constant->as_string()));
    }
  }
}

Gpl_type Not_Equal::type() const
{
  Gpl_type lht = lhs->type();
  Gpl_type rht = rhs->type();
  if (lht == STRING || rht == STRING) return STRING;
  if (lht == DOUBLE || rht == DOUBLE) return DOUBLE;
  return INT;
}


const Constant* Not::evaluate() const
{
  const Constant* rhs_constant = rhs->evaluate();
  try {
    return ret(new Integer_constant(!rhs_constant->as_int()));
  } catch(...) { 
    return ret(new Integer_constant(!rhs_constant->as_double()));
  }
}

Gpl_type Not::type() const
{
  Gpl_type rht = rhs->type();
  if (rht == STRING) return STRING;
  if (rht == DOUBLE) return DOUBLE;
  return INT;
}

const Constant* Cosine::evaluate() const
{
  const Constant* rhs_constant = rhs->evaluate();

  try {
    return ret(new Double_constant(cos(rhs_constant->as_int() * M_PI / 180)));
    } catch(...) {
    return ret(new Double_constant(cos(rhs_constant->as_double() * M_PI / 180)));
  }
}

Gpl_type Cosine::type() const
{
  Gpl_type rht = rhs->type();
  if (rht == STRING) return STRING;
  if (rht == DOUBLE) return DOUBLE;
  return INT;
}

const Constant* Sine::evaluate() const
{
  const Constant* rhs_constant = rhs->evaluate();
  try {
    return ret(new Double_constant(sin(rhs_constant->as_int()*M_PI/180)));
    } catch(...) {
    return ret(new Double_constant(sin(rhs_constant->as_double()*M_PI/180)));
  }
}

Gpl_type Sine::type() const
{
  Gpl_type rht = rhs->type();
  if (rht == STRING) return STRING;
  if (rht == DOUBLE) return DOUBLE;
  return INT;
}

const Constant* Tan::evaluate() const
{
  const Constant* rhs_constant = rhs->evaluate();
  try{
    return ret(new Double_constant(tan(rhs_constant->as_int()*M_PI/180)));
    } catch (...) {
    return ret(new Double_constant(tan(rhs_constant->as_double()*M_PI/180)));
  }
}

Gpl_type Tan::type() const
{
  Gpl_type rht = rhs->type();
  if (rht == STRING) return STRING;
  if (rht == DOUBLE) return DOUBLE;
  return INT;
}

const Constant* Acos::evaluate() const
{
  const Constant* rhs_constant = rhs->evaluate();
  try {
    return ret(new Double_constant(acos(rhs_constant->as_int())*180/M_PI));
    } catch(...) {
    return ret(new Double_constant(acos(rhs_constant->as_double())*180/M_PI));
  }
}

Gpl_type Acos::type() const
{
  Gpl_type rht = rhs->type();
  if (rht == STRING) return STRING;
  if (rht == DOUBLE) return DOUBLE;
  return INT;
}

const Constant* Asin::evaluate() const
{
  const Constant* rhs_constant = rhs->evaluate();
  try {
    return ret(new Double_constant(asin(rhs_constant->as_int())*180/M_PI));
    } catch(...) {
    return ret(new Double_constant(asin(rhs_constant->as_double())*180/M_PI));
  }
}

Gpl_type Asin::type() const
{
  Gpl_type rht = rhs->type();
  if (rht == STRING) return STRING;
  if (rht == DOUBLE) return DOUBLE;
  return INT;
}

const Constant* Atan::evaluate() const
{
  const Constant* rhs_constant = rhs->evaluate();
  try {
    return ret(new Double_constant(atan(rhs_constant->as_int())*180/M_PI));
    } catch(...) {
    return ret(new Double_constant(atan(rhs_constant->as_double())*180/M_PI));
  }
}

Gpl_type Atan::type() const
{
  Gpl_type rht = rhs->type();
  if (rht == STRING) return STRING;
  if (rht == DOUBLE) return DOUBLE;
  return INT;
}

const Constant* Sqrt::evaluate() const
{
  const Constant* rhs_constant = rhs->evaluate();
  return ret(new Double_constant(sqrt(rhs_constant->as_double())));
}

Gpl_type Sqrt::type() const
{
  Gpl_type rht = rhs->type();
  if (rht == STRING) return STRING;
  if (rht == DOUBLE) return DOUBLE;
  return INT;
}

const Constant* Abs::evaluate() const
{
  const Constant* rhs_constant = rhs->evaluate();
  try {
    return ret(new Integer_constant(abs(rhs_constant->as_int())));
  } catch(...) {
    return ret(new Double_constant(fabs(rhs_constant->as_double())));
  }
}

Gpl_type Abs::type() const
{
  Gpl_type rht = rhs->type();
  if (rht == STRING) return STRING;
  if (rht == DOUBLE) return DOUBLE;
  return INT;
}

const Constant* Floor::evaluate() const
{
  const Constant* rhs_constant = rhs->evaluate();
  try {
    return ret(new Integer_constant(floor(rhs_constant->as_int())));
  } catch(...) {
    return ret(new Integer_constant(floor(rhs_constant->as_double())));
  }
}

Gpl_type Floor::type() const
{
  Gpl_type rht = rhs->type();
  if (rht == STRING) return STRING;
  if (rht == DOUBLE) return DOUBLE;
  return INT;
}

const Constant* Random::evaluate() const
{
  const Constant* rhs_constant = rhs->evaluate();
  int value;

  try
  {
    value = rhs_constant->as_int();
  }
  catch(...)
  {
    value = floor(rhs_constant->as_double());
  }
  if(value < 2) {
    Error::error(Error::INVALID_ARGUMENT_FOR_RANDOM, rhs_constant->as_string());
    value = 2;
  }

  return ret(new Integer_constant(rand() % value));
}

Gpl_type Random::type() const
{
  return INT;
}

const Constant* Unary_minus::evaluate() const
{
  const Constant* rhs_constant = rhs->evaluate();
  try {
    return ret(new Integer_constant(-rhs_constant->as_int()));
  } catch(...){ 
    return ret(new Double_constant(-rhs_constant->as_double()));
  }
}

Gpl_type Unary_minus::type() const
{
  Gpl_type rht = rhs->type();
  if (rht == STRING) return STRING;
  if (rht == DOUBLE) return DOUBLE;
  return INT;
}

Gpl_type Equal::type() const
{
  return INT;
}

const Constant* Equal::evaluate() const
{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();
  try {  
    return ret(new Integer_constant(lhs_constant->as_int() == rhs_constant->as_int()));
  } catch(...) { 
      try {
        return ret(new Integer_constant(lhs_constant->as_double() == rhs_constant->as_double()));
      } catch(...) {  
        return ret(new Integer_constant(lhs_constant->as_string() == rhs_constant->as_string()));
    }
  }
}

Gpl_type And::type() const
{
  return INT;
}

const Constant* And::evaluate() const
{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();
  try {
    return ret(new Integer_constant(lhs_constant->as_int() && rhs_constant->as_int()));
  } catch(...) { 
    return ret(new Integer_constant(lhs_constant->as_double() && rhs_constant->as_double()));
  }
}

Gpl_type Or::type() const
{
  return INT;
}

const Constant* Or::evaluate() const
{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();
  try {
    return ret(new Integer_constant(lhs_constant->as_int() || rhs_constant->as_int()));
  } catch(...) { 
    return ret(new Integer_constant(lhs_constant->as_double() || rhs_constant->as_double()));
  }
}

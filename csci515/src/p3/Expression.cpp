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
  return nullptr; //REPLACE THIS. Here to suppress errors.
}

Gpl_type Plus::type() const
{
  return NO_TYPE; //REPLACE THIS. Here to suppress errors.
}

const Constant* Multiply::evaluate() const
{
  return nullptr; //REPLACE THIS. Here to suppress errors.
}

Gpl_type Multiply::type() const
{
  return NO_TYPE; //REPLACE THIS. Here to suppress errors.
}

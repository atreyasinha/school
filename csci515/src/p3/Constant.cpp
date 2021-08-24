//File: Constant.cpp
#include "Constant.h"

Gpl_type  Constant::type() const 
{ return intrinsic_type; }

const Constant* Constant::evaluate() const
{ return this; }

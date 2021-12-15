//File: Expression.h
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "gpl_type.h"
class Constant;
class Expression {
  public:
    Expression():evaluated_constant(nullptr) {}
    virtual const Constant* evaluate() const=0;
    virtual Gpl_type type() const=0;
    virtual ~Expression();
    Expression(const Expression&) = delete;
    Expression& operator=(const Expression&) = delete;
  protected:
    //a wrapper around returned constants
    const Constant* ret(const Constant* new_evald_constant) const;
  private:
    //pointer to evaluate()'s created constant so it can be released
    mutable const Constant* evaluated_constant;
};

class Binary_operator : public Expression {
  public:
    Binary_operator(const Expression* lhs, const Expression* rhs) :lhs(lhs), rhs(rhs) {}
    virtual const Constant* evaluate() const=0;
    virtual ~Binary_operator() { delete lhs; delete rhs; }
  protected:
    const Expression* lhs;
    const Expression* rhs;
};

class Unary_operator : public Expression {
  public:
    Unary_operator(const Expression* rhs) : rhs(rhs) {}
    virtual const Constant* evaluate() const=0;
    virtual ~Unary_operator() { delete rhs; }
  protected:
    const Expression* rhs;
};

class Plus : public Binary_operator {
  public:
    Plus(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Question : public Binary_operator {
  public:
    Question(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Colon : public Binary_operator {
  public:
    Colon(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Multiply : public Binary_operator {
  public:
    Multiply(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Minus : public Binary_operator {
  public:
    Minus(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Divide : public Binary_operator {
  public:
    Divide(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Mod : public Binary_operator {
  public:
    Mod(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class And : public Binary_operator {
  public:
    And(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Or : public Binary_operator {
  public:
    Or(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Less_Than : public Binary_operator {
  public:
    Less_Than(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Greater_Than : public Binary_operator {
  public:
    Greater_Than(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Less_Equal : public Binary_operator {
  public:
    Less_Equal(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Greater_Equal : public Binary_operator {
  public:
    Greater_Equal(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Equal : public Binary_operator {
  public:
    Equal(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Not_Equal : public Binary_operator {
  public:
    Not_Equal(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Not : public Unary_operator {
  public:
    Not(const Expression* rhs) : Unary_operator(rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Cosine : public Unary_operator {
  public:
    Cosine(const Expression* rhs) : Unary_operator(rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Sine : public Unary_operator {
  public:
    Sine(const Expression* rhs) : Unary_operator(rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Tan : public Unary_operator {
  public:
    Tan(const Expression* rhs) : Unary_operator(rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Acos : public Unary_operator {
  public:
    Acos(const Expression* rhs) : Unary_operator(rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Asin : public Unary_operator {
  public:
    Asin(const Expression* rhs) : Unary_operator(rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Atan : public Unary_operator {
  public:
    Atan(const Expression* rhs) : Unary_operator(rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Sqrt : public Unary_operator {
  public:
    Sqrt(const Expression* rhs) : Unary_operator(rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Abs : public Unary_operator {
  public:
    Abs(const Expression* rhs) : Unary_operator(rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Floor : public Unary_operator {
  public:
    Floor(const Expression* rhs) : Unary_operator(rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Random : public Unary_operator {
  public:
    Random(const Expression* rhs) : Unary_operator(rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Unary_minus : public Unary_operator {
  public:
    Unary_minus(const Expression* rhs) : Unary_operator(rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

#endif

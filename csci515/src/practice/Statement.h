#ifndef STATEMENT_H
#define STATEMENT_H

class Expression;
class Variable;
class Statement {
  public:
    void append_statement(Statement* atend);
    Statement():next(nullptr) {}
    virtual void execute() const=0;
    virtual ~Statement() {delete next;}
  protected:
    Statement* next;
};

//##
// NullStatement
//##
class NullStatement : public Statement {
  public:
    NullStatement(){}
    virtual void execute() const;
};

class Print : public Statement {
  public:
    Print(int line_number, const Expression* argument) : line_number(line_number), argument(argument){}
    virtual void execute() const;
    ~Print();
  private:
    int line_number;
    const Expression* argument;
};

class Assign : public Statement {
  public:
    Assign(const Variable* lhs, const Expression* rhs) : lhs(lhs), rhs(rhs){}
    virtual void execute() const;
    virtual ~Assign();
  private:
    const Variable* lhs;
    const Expression* rhs;
};

class Plus_assign : public Statement {
  public:
    Plus_assign(const Variable* lhs, const Expression* rhs) : lhs(lhs), rhs(rhs){}
    virtual void execute() const;
    virtual ~Plus_assign();
  private:
    const Variable* lhs;
    const Expression* rhs;
};

class Minus_assign : public Statement {
  public:
    Minus_assign(const Variable* lhs, const Expression* rhs) : lhs(lhs), rhs(rhs){}
    virtual void execute() const;
    virtual ~Minus_assign();
  private:
    const Variable* lhs;
    const Expression* rhs;
};

class Plus_plus : public Statement {
  public:
    Plus_plus(const Variable* lhs) : lhs(lhs){}
    virtual void execute() const;
    virtual ~Plus_plus();
  private:
    const Variable* lhs;
};

class Minus_minus : public Statement {
  public:
    Minus_minus(const Variable* lhs) : lhs(lhs){}
    virtual void execute() const;
    virtual ~Minus_minus();
  private:
    const Variable* lhs;
    const Expression* rhs;
};

class If : public Statement {
  public:
    If(const Expression* exp, const Statement* s_if, const Statement* s_else) : exp(exp), s_if(s_if), s_else(s_else){}
    virtual void execute() const;
    virtual ~If();
  private:
    const Expression* exp;
    const Statement* s_if; 
    const Statement* s_else;
};

class For : public Statement {
  public:
    For(const Statement* s_init, const Expression* s_cond, const Statement* s_inc, const Statement* s_body) 
        : s_init(s_init), s_cond(s_cond), s_inc(s_inc), s_body(s_body){}
    virtual void execute() const;
    virtual ~For();
  private:
    const Statement* s_init;
    const Expression* s_cond;
    const Statement* s_inc;
    const Statement* s_body;
};

class Exit : public Statement {
  public:
    Exit(int line_number, const Expression* argument) : line_number(line_number), argument(argument){}
    virtual void execute() const;
    ~Exit();
  private:
    int line_number;
    const Expression* argument;
};

class Repeat : public Statement {
  public:
    Repeat(const Statement* s_body, const Expression* s_cond) : s_cond(s_cond), s_body(s_body){}
    virtual void execute() const;
    virtual ~Repeat();
  private:
    const Expression* s_cond;
    const Statement* s_body;
};

#endif

#ifndef MEMBER_VARIABLE_H
#define MEMBER_VARIABLE_H

#include "Variable.h"

class Member_variable : public Variable {
    private:
        std::string attribute;
    public:
        Member_variable(const std::string& symbol_name, const std::string& attribute_name);
        Member_variable(const std::string& symbol_name, const Expression* index_expr, const std::string& attribute_name);

        virtual const Constant* evaluate() const override;
        virtual std::shared_ptr<Locator> modify() const override;
        virtual Gpl_type type() const override;
};

#endif
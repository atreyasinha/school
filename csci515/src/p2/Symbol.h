#ifndef SYMBOL_H
#define SYMBOL_H

#include <iostream>
#include "gpl_type.h"

class Symbol {
    private:
        /* data */
        union symbol_type {
            double* double_pointer;
            int* int_pointer;
            std::string* string_pointer;

            //constructors to ease initialization of union variables
            symbol_type(double* val) : double_pointer(val){}
            symbol_type(int* val) : int_pointer(val){}
            symbol_type(std::string* val) : string_pointer(val){}
        };
        std::string name;   //the name of the variable
        symbol_type value;  //the contents of the variable
        Gpl_type type;      //the type of the variable. See gpl_type.h
        int count;          //used to store the size if the variable is an array
    public:
        Symbol(const std::string& name, double* value);                 //for double variable
        Symbol(const std::string& name, double* value, int count);      //for double array
        Symbol(const std::string& name, int* value);                      //for int variable
        Symbol(const std::string& name, int* value, int count);           //for int array
        Symbol(const std::string& name, std::string* value);              //for string variable
        Symbol(const std::string& name, std::string* value, int count);   //for string array

        Gpl_type get_type() const;
        std::string get_name() const;
        virtual ~Symbol();
        friend std::ostream& operator<<(std::ostream& os, const Symbol&);

        //prevent compiler from generating these functions
        Symbol(const Symbol&) = delete;
        Symbol& operator=(const Symbol&) = delete;
};

#endif

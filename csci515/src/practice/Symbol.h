#ifndef SYMBOL_H
#define SYMBOL_H

#include <iostream>
#include "gpl_type.h"
#include "Constant.h"
#include "Locator.h"

class Rectangle;
class Circle;
class Triangle;
class Pixmap;
class Textbox;

class Symbol {
    private:
        /* data */
        union symbol_type {
            double* double_pointer;
            int* int_pointer;
            std::string* string_pointer;

            Rectangle* rectangle_pointer;
            Circle* circle_pointer;
            Triangle* triangle_pointer;
            Pixmap* pixmap_pointer;
            Textbox* textbox_pointer;

            //constructors to ease initialization of union variables
            symbol_type(double* val) : double_pointer(val){}
            symbol_type(int* val) : int_pointer(val){}
            symbol_type(std::string* val) : string_pointer(val){}

            symbol_type(Rectangle* val) : rectangle_pointer(val){}
            symbol_type(Circle* val) : circle_pointer(val){}
            symbol_type(Triangle* val) : triangle_pointer(val){}
            symbol_type(Pixmap* val) : pixmap_pointer(val){}
            symbol_type(Textbox* val) : textbox_pointer(val){}
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

        Symbol(const std::string& name, Rectangle* value);              //for Rectangle variable
        Symbol(const std::string& name, Rectangle* value, int count);   //for Rectangle array
        Symbol(const std::string& name, Circle* value);              //for Circle variable
        Symbol(const std::string& name, Circle* value, int count);   //for Circle array
        Symbol(const std::string& name, Triangle* value);              //for Triangle variable
        Symbol(const std::string& name, Triangle* value, int count);   //for Triangle array
        Symbol(const std::string& name, Pixmap* value);              //for Pixmap variable
        Symbol(const std::string& name, Pixmap* value, int count);   //for Pixmap array
        Symbol(const std::string& name, Textbox* value);              //for Textbox variable
        Symbol(const std::string& name, Textbox* value, int count);   //for Textbox array

        // Symbol(const std::string& name, Game_object* value);              //for game_object variable
        // Symbol(const std::string& name, Game_object* value, int count);   //for game_object array
        

        Gpl_type get_type() const;
        std::string get_name() const;
        virtual ~Symbol();
        friend std::ostream& operator<<(std::ostream& os, const Symbol&);

        //prevent compiler from generating these functions
        Symbol(const Symbol&) = delete;
        Symbol& operator=(const Symbol&) = delete;

        bool is_array();
        const Constant* as_constant() const;          //Symbol value is not an array
        const Constant* as_constant(int index) const; //Symbol value is an array

        const Constant* as_constant(const std::string& attribute_name) const;               // non-arrays
        const Constant* as_constant(int index, const std::string& attribute_name) const;    // arrays

        //non-array: int, double, or string
        std::shared_ptr<Locator> as_lvalue() const;

        //array element: int, double, or string
        std::shared_ptr<Locator> as_lvalue(int index) const;

        //non-array: game object
        std::shared_ptr<Locator> as_lvalue(const std::string& attribute_name) const;

        //array element: game object
        std::shared_ptr<Locator> as_lvalue(int index, const std::string& attribute_name) const;
        
};

#endif

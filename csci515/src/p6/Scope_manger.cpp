#include <iostream>
#include <stdexcept>
#include "Scope_manager.h"
#include "error.h"

Scope_manager& Scope_manager::instance() {
    static Scope_manager sm_instance;
    return sm_instance;
}

void Scope_manager::push_table() {
    tables.push_back(std::make_shared<Symbol_table>());
}

void Scope_manager::pop_table() {   
    if (tables.size() > 0) tables.pop_back();
    else throw std::underflow_error("Can't pop global symbol table");
}

bool Scope_manager::add_to_current_scope(std::shared_ptr<Symbol> sym) {
    if (tables.size() > 0) return tables[(int) tables.size() - 1]->insert(sym);
    else std::cerr << "error in handler insert\n";
    return false;
}

std::shared_ptr<Symbol> Scope_manager::lookup(const std::string& name) {
    for (int i = (int) tables.size() - 1; i >= 0; i--)  if (tables[i]->lookup(name)) return tables[i]->lookup(name);
    return nullptr;
}

bool Scope_manager::defined_in_current_scope(const std::string& name){
    if (tables.back()->lookup(name)) return true; 
    return false;
}

std::ostream& operator<<(std::ostream& os, const Scope_manager& sh) {
    for (int i = (int) sh.tables.size() - 1; i >= 0; i--) {
        os << *sh.tables[i];
    }
    return os;
}

void Scope_manager::erase(const std::string& name) {
    for (int i = (int) tables.size() - 1; i >= 0; i--)  if (tables[i]->lookup(name)) tables[i]->erase(name);
}
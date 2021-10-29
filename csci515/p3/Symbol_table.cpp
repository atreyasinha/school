#include <iostream>
#include <vector>
#include <algorithm>
#include "Symbol_table.h"

std::shared_ptr<Symbol> Symbol_table::lookup (const std::string& name) {
    if (symbols.find(name) == symbols.end()) return nullptr;
    return symbols.find(name)->second;
}

bool Symbol_table::insert(std::shared_ptr<Symbol> sym) {
    if (symbols.find(sym->get_name()) != symbols.end()) return false;
    symbols[sym->get_name()] = sym;
    return true;
}

std::ostream& operator<<(std::ostream& os, const Symbol_table& st) {
    for (auto i = st.symbols.begin(); i != st.symbols.end(); i++) {
        os << *i->second << std::endl;
    }
    return os;
}

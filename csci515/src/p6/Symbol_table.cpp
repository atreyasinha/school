#include "Symbol_table.h"
#include "vector"
#include "string"
#include <algorithm>

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
    std::vector<std::string> v;
    for (auto i: st.symbols)    v.push_back(i.first);

    sort(v.begin(), v.end());

    for(int i = 0; i < (int)    v.size(); i++) os << *st.symbols.at(v[i]);
    
    return os;
}

void Symbol_table::erase(const std::string& name) {
    symbols.erase(name);
}
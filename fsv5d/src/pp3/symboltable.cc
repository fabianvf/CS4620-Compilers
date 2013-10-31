/* File: symboltable.h
 * ----------- 
 * This class contains the Symbol table header file
 *
 */




#include "symboltable.h"

SymbolTable::SymbolTable(){
//    context = new std::vector<std::vector<Decl*> >;
//    context.push_back(new std::vector<Decl*>);
}

int SymbolTable::toParentScope(int scope_level){
    return 0;
}

void SymbolTable::enter_scope(){
    std::vector<Decl*> scope;
    context.push_back(scope);
    cur_scope_level = (context.size() - 1);
}

void SymbolTable::exit_scope(){
//    return;
}

Decl* SymbolTable::lookup(Identifier* x){
    return context[0][0];
}

Decl* SymbolTable::local_lookup(Identifier* x){
    return context[0][0];
}

bool SymbolTable::add(Decl* x){
    return true;
}


   




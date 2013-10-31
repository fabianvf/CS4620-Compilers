/* File: symboltable.h
 * ----------- 
 * This class contains the Symbol table header file
 *
 */




#include "symboltable.h"

SymbolTable::SymbolTable(){

}

int SymbolTable::toParentScope(int scope_level){
    return 0;
}

void SymbolTable::enter_scope(){
    return;
}

void SymbolTable::exit_scope(){
    return;
}

Decl* SymbolTable::lookup(Identifier* x){
    return new Decl;
}

Decl* SymbolTable::local_lookup(Identifier* x){
    return new Decl;
}

bool SymbolTable::add(Decl* x){
    return true;
}


   




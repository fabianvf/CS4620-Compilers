/* File: symboltable.cc
 * ----------- 
 * This class contains the Symbol table implementation
 *
 * The data structure that stores the symbol table is a vector of maps.
 *
 * The maps map identifiers to declarations
 *
 * Exiting a scope does not destroy any information, but that map index
 * is put on an ignore list so that searching for a parent scope will 
 * never open a closed scope. 
 * 
 * The ignore list is implemented as a set, so finding the next scope
 * is very quick. 
 *
 * The index of the current scope is always tracked.
 */




#include "symboltable.h"


// Constructor, nothing needs to happen here
SymbolTable::SymbolTable(){

}

// A private functions that goes to the next non-closed scope (which is 
// guaranteed to be the parent scope
int SymbolTable::toParentScope(int scope_level){
    while((scope_level != 0) && (ignore.find(scope_level) != ignore.end())){
        scope_level--;
    }
    return scope_level;
}

// This simply adds a new empty map onto the list of scopes, and updates the scope index
void SymbolTable::enter_scope(){
    std::map<Identifier*, Decl*> new_scope;
    context.push_back(new_scope);
    cur_scope_level = (context.size() - 1);
}

// This adds the current scope to the ignore list/set, and sets the current scope index 
// to the parent scope
void SymbolTable::exit_scope(){
    ignore.insert(cur_scope_level);
    cur_scope_level = toParentScope(cur_scope_level);
}

// Returns the declaration an identifier belongs to if it is found. Will search all open
// scopes. Returns NULL if the id is not found.
Decl* SymbolTable::lookup(Identifier* x){
    int i = cur_scope_level;
    std::map<Identifier*, Decl*>::iterator it = context[i].find(x);

    while(it == context[i].end()){
        if (i > 0){
            i = toParentScope(i);
            it = context[i].find(x);
        }
        else{
            return NULL;
        }
    }    
    return it->second;
}

// Returns the declaration an identifer belongs to if it is found within the current scope.
// Returns NULL if the id is not in the current scope.
Decl* SymbolTable::local_lookup(Identifier* x){
    std::map<Identifier*, Decl*>::iterator it = context[cur_scope_level].find(x);
    if (it == context[cur_scope_level].end()){
        return NULL;
    }
    return it->second;
}

// Adds an (Identifier*, Decl*) pair to the map. Returns false if the identifier is already 
// mapped to a value in the current scope, and true otherwise.
bool SymbolTable::add(Decl* x){
    if(local_lookup(x->id) != NULL){
        return false;
    }
    context[cur_scope_level][x->id] = x;
    return true;
    
}

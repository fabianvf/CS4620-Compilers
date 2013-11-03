/* File: symboltable.cc
 * ----------- 
 * This class contains the Symbol table implementation
 *
 * The data structure that stores the symbol table is a vector of maps.
 *
 * The maps map identifier names to declarations
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
    while((scope_level > 0) && (ignore.find(scope_level) != ignore.end())){
        scope_level--;
    }
    return scope_level;
}
int SymbolTable::toNextChildScope(int scope_level){
    while((scope_level < context.size()) && (ignore.find(scope_level) != ignore.end())){
        scope_level++;
    }
    return scope_level;
}

std::map<std::string,Decl*>& new_scope(){
    static std::map<std::string, Decl*>* new_scope= new std::map<std::string, Decl*>();
    return *new_scope;
}
// This simply adds a new empty map onto the list of scopes, and updates the scope index
void SymbolTable::add_scope(){
//  std::map<std:string, Decl*> new_scope;
    context.push_back(new_scope());
    cur_scope_level = (context.size() - 1);
}

void SymbolTable::enter_scope(){
    cur_scope_level;
    cur_scope_level = toNextChildScope(cur_scope_level+1);
}
// This adds the current scope to the ignore list/set, and sets the current scope index 
// to the parent scope
void SymbolTable::exit_scope(){
    ignore.insert(cur_scope_level);
    cur_scope_level = toParentScope(cur_scope_level);
}

// Returns the declaration an identifier belongs to if it is found. Will search all open
// scopes. Returns NULL if the id is not found.
Decl* SymbolTable::lookup(char* x){ 
//    std::cerr << "in SymbolTable.lookup(char* x), looking for: " << x << std::endl;
    int tmp = cur_scope_level;
    Decl* res = NULL;
    for (int j = 0; j < context.size() - ignore.size(); j++){
//        std::cerr << "\t at scope index: " << cur_scope_level << std::endl;
        res = local_lookup(x);
        if (res != NULL){
            cur_scope_level = tmp;
            return res;
        }
        cur_scope_level = toParentScope(cur_scope_level-1);
   }
    cur_scope_level = tmp;
    return NULL;
}

// Returns the declaration an identifer belongs to if it is found within the current scope.
// Returns NULL if the id is not in the current scope.
Decl* SymbolTable::local_lookup(char* x){
    std::string name(x);
    if (context[cur_scope_level].size() == 0){
        return NULL;
    }
    std::map<std::string, Decl*>::iterator it = context[cur_scope_level].find(name);
    if (it == context[cur_scope_level].end()){
        return NULL;
    }
    return it->second;
}

// Adds an (Char*, Decl*) pair to the map. Returns false if the identifier is already 
// mapped to a value in the current scope, and true otherwise.
bool SymbolTable::add(Decl* x){
    std::string name (x->GetName());
    if(local_lookup(x->GetName()) != NULL){
        return false;
    }
    return (context[cur_scope_level].insert(std::make_pair(name, x)).second);    
}
 
// Sets the SymbolTable up for the second pass, by opening all scopes back up and going to
// the highest parent scope
void SymbolTable::setForPass2(){
    cur_scope_level = -1;
    ignore.clear();
}

int SymbolTable::get_scope_level(){
    return cur_scope_level;
}

void SymbolTable::print_contents()
{
    std::cout << "******** Symbol Table ******** " << std::endl;
    int i = 0;
    for(std::vector<std::map<std::string, Decl*> >::iterator it = context.begin(); it != context.end(); it++, i++){
        std::cout << "Bindings at level " << i <<  ":" << std::endl;
        std::map<std::string, Decl*> & cur = *it;
        for(std::map<std::string, Decl*>::iterator it2 = cur.begin(); it2 != cur.end(); it2++) {
            std::cout << "\t" << it2->first << "   -> " << it2->second->GetPrintNameForNode() << std::endl;
        }

    }
    std::cout << "Closed Scopes: \n";
    std::set<int>::iterator iter;
    for(iter=ignore.begin(); iter!=ignore.end(); iter++){
        std::cout<<"\t" << (*iter)<<std::endl;
    }
    std::cout << "******** ********* ******** " << std::endl;
}

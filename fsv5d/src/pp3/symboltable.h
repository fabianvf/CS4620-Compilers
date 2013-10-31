/* File: symboltable.h
 * ----------- 
 * This class contains the Symbol table header file
 *
 */


#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

class Decl;
class Identifier;

#include <stdlib.h>   // for NULL
#include "ast_decl.h"
#include "list.h"
#include <vector>

class SymbolTable
{
  protected:
    std::vector<std::vector<Decl*> > context;
    std::vector<int> ignore;
    int cur_scope_level;
    int toParentScope(int scope_level);
  public:
    SymbolTable();
    void enter_scope();
    void exit_scope();
    Decl* lookup(Identifier* x);
    Decl* local_lookup(Identifier* x);
    bool add(Decl* x);

};
   
#endif


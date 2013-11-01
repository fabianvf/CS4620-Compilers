/* File: symboltable.h
 * ----------- 
 * This class contains the Symbol table header file
 *
 */


#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_


class Identifier;
class Decl;

#include <stdlib.h>   // for NULL
#include "ast_decl.h"
#include "ast.h"
#include "list.h"
#include <vector>
#include <map>
#include <set>
#include <string>

class SymbolTable
{
  protected:
    std::vector<std::map<std::string, Decl*> > context;
    std::set<int> ignore;
    int cur_scope_level;
    int toParentScope(int scope_level);
  public:
    SymbolTable();
    void add_scope();
    void enter_scope();
    void exit_scope();
    Decl* lookup(char* x);
    Decl* local_lookup(char* x);
    bool add(Decl* x);
    void setForPass2();
};
   
#endif


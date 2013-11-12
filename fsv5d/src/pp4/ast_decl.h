/* File: ast_decl.h
 * ----------------
 * In our parse tree, Decl nodes are used to represent and
 * manage declarations. There are 4 subclasses of the base class,
 * specialized for declarations of variables, functions, classes,
 * and interfaces.
 */
 
#ifndef _H_ast_decl
#define _H_ast_decl

#include <iostream>
#include "ast.h"
#include "list.h"
#include "symboltable.h"

class Type;
class NamedType;
class Identifier;
class Stmt;
class SymbolTable;

class Decl : public Node 
{
  friend class SymbolTable;
  protected:
    Identifier *id;
  
  public:
    Decl(Identifier *name);
    friend std::ostream& operator<< (std::ostream& o, Decl *decl){return o << decl->id->GetName();}
    char *GetName();
    virtual bool Check(SymbolTable *SymbolTable){return true;}
    virtual bool Check2(SymbolTable *SymbolTable){return true;}
    static const int kind= 0;
    virtual int getScopeIndex(){return 0;}
};

class VarDecl : public Decl 
{
  protected:
    Type *type;
    
  public:
    VarDecl(Identifier *name, Type *type);
    const char *GetPrintNameForNode() { return "VarDecl"; }
    void PrintChildren(int indentLevel);
    bool Check(SymbolTable *SymbolTable);
    bool Check2(SymbolTable *SymbolTable);
    static const int kind= 1;
    int getScopeIndex(){return 0;}
    Type *GetType(){return type;}


};

class ClassDecl : public Decl 
{
  protected:
    List<Decl*> *members;
    NamedType *extends;
    List<NamedType*> *implements;
    int scopeIndex;

  public:
    ClassDecl(Identifier *name, NamedType *extends, 
              List<NamedType*> *implements, List<Decl*> *members);
    const char *GetPrintNameForNode() { return "ClassDecl"; }
    void PrintChildren(int indentLevel);
    bool Check(SymbolTable *SymbolTable);
    bool Check2(SymbolTable *SymbolTable);
    int getScopeIndex(){return scopeIndex;}
    bool inherits;
    static const int kind= 2;


};

class InterfaceDecl : public Decl 
{
  protected:
    List<Decl*> *members;
    int scopeIndex;
    
  public:
    InterfaceDecl(Identifier *name, List<Decl*> *members);
    const char *GetPrintNameForNode() { return "InterfaceDecl"; }
    void PrintChildren(int indentLevel);
    bool Check(SymbolTable *SymbolTable);
    bool Check2(SymbolTable *SymbolTable);
    int getScopeIndex(){return scopeIndex;}
    static const int kind= 3;
    List<Decl*> *GetMembers(){return members;}
};

class FnDecl : public Decl 
{
  protected:
    List<VarDecl*> *formals;
    Type *returnType;
    Stmt *body;
    
  public:
    FnDecl(Identifier *name, Type *returnType, List<VarDecl*> *formals);
    void SetFunctionBody(Stmt *b);
    const char *GetPrintNameForNode() { return "FnDecl"; }
    void PrintChildren(int indentLevel);
    bool Check(SymbolTable *SymbolTable);
    bool Check2(SymbolTable *SymbolTable);
    static const int kind= 4;
    int getScopeIndex(){return 0;}
    Type *GetType(){return returnType;}
    List<VarDecl*> *GetFormals() {return formals;}

};

#endif

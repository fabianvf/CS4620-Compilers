/* File: ast_type.h
 * ----------------
 * In our parse tree, Type nodes are used to represent and
 * store type information. The base Type class is used
 * for built-in types, the NamedType for classes and interfaces,
 * and the ArrayType for arrays of other types.  
 */
 
#ifndef _H_ast_type
#define _H_ast_type

#include "ast.h"
#include "list.h"
#include "symboltable.h"

class Type : public Node 
{
  protected:
    char *typeName;

  public :
    static Type *intType, *doubleType, *boolType, *voidType,
                *nullType, *stringType, *errorType;

    Type(yyltype loc) : Node(loc) {}
    Type(const char *str);
    
    const char *GetPrintNameForNode() { return "Type"; }
    void PrintChildren(int indentLevel);
    friend std::ostream& operator<<(std::ostream& o, Type *t){
        t->PrintId(o);
        return o;
    }
    virtual void PrintId(std::ostream& o){o << typeName;}
    virtual char *GetName(){return typeName;}
    virtual bool Check2(SymbolTable *SymTab) { return true;}
    virtual Identifier *GetId(){return NULL;}
};

class NamedType : public Type 
{
  protected:
    Identifier *id;
    
  public:
    NamedType(Identifier *i);
    Identifier* GetId();
    bool Check2(SymbolTable* SymTab);
    const char *GetPrintNameForNode() { return "NamedType"; }
    void PrintChildren(int indentLevel);
    char *GetName(){return id->GetName();}
    void PrintId(std::ostream& o){o  << id->GetName();}
};

class ArrayType : public Type 
{
  protected:
    Type *elemType;

  public:
    ArrayType(yyltype loc, Type *elemType);
    Identifier* GetId();
    char* GetName(){return GetId()->GetName();}    
    const char *GetPrintNameForNode() { return "ArrayType"; }
    void PrintChildren(int indentLevel);
    void Print(std::ostream& o) { o << elemType << "[]";}
    bool Check2(SymbolTable* SymTab);
};

 
#endif

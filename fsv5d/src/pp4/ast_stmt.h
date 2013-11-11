/* File: ast_stmt.h
 * ----------------
 * The Stmt class and its subclasses are used to represent
 * statements in the parse tree.  For each statment in the
 * language (for, if, return, etc.) there is a corresponding
 * node class for that construct. 
 */


#ifndef _H_ast_stmt
#define _H_ast_stmt

#include "list.h"
#include "ast.h"
#include "symboltable.h"

class Decl;
class VarDecl;
class Expr;
//class SymbolTable;

  
class Program : public Node
{
  protected:
     List<Decl*> *decls; 
    
  public:
     Program(List<Decl*> *declList);
     SymbolTable *symTab;
     const char *GetPrintNameForNode() { return "Program"; }
     bool Check();
     void PrintChildren(int indentLevel);
};

class Stmt : public Node
{
  public:
     Stmt() : Node() {}
     Stmt(yyltype loc) : Node(loc) {}
     virtual bool Check(SymbolTable *SymbolTable){return true;}
     virtual bool Check2(SymbolTable *SymbolTable){return true;}
     virtual ~Stmt(){}
};

class StmtBlock : public Stmt 
{
  protected:
    List<VarDecl*> *decls;
    List<Stmt*> *stmts;
    
  public:
    StmtBlock(List<VarDecl*> *variableDeclarations, List<Stmt*> *statements);
    const char *GetPrintNameForNode() { return "StmtBlock"; }
    void PrintChildren(int indentLevel);
    bool Check(SymbolTable *SymTab);
    bool Check2(SymbolTable *SymTab);
};

  
class ConditionalStmt : public Stmt
{
  protected:
    Expr *test;
    Stmt *body;
  
  public:
    ConditionalStmt(Expr *testExpr, Stmt *body);
    virtual bool Check(SymbolTable *SymTab){return true;}
    virtual bool Check2(SymbolTable *SymTab){return true;}
};

class LoopStmt : public ConditionalStmt 
{
  public:
    LoopStmt(Expr *testExpr, Stmt *body)
            : ConditionalStmt(testExpr, body) {}
    virtual bool Check(SymbolTable *SymTab){return true;}
    virtual bool Check2(SymbolTable *SymTab){return true;}
};

class ForStmt : public LoopStmt 
{
  protected:
    Expr *init, *step;
  
  public:
    ForStmt(Expr *init, Expr *test, Expr *step, Stmt *body);
    const char *GetPrintNameForNode() { return "ForStmt"; }
    void PrintChildren(int indentLevel); 
    bool Check(SymbolTable *SymTab);
    bool Check2(SymbolTable *SymTab);

};

class WhileStmt : public LoopStmt 
{
  public:
    WhileStmt(Expr *test, Stmt *body) : LoopStmt(test, body) {}
    const char *GetPrintNameForNode() { return "WhileStmt"; }
    void PrintChildren(int indentLevel);
    bool Check(SymbolTable *SymTab);
    bool Check2(SymbolTable *SymTab);
};



class IfStmt : public ConditionalStmt 
{
  protected:
    Stmt *elseBody;
  
  public:
    IfStmt(Expr *test, Stmt *thenBody, Stmt *elseBody);
    const char *GetPrintNameForNode() { return "IfStmt"; }
    void PrintChildren(int indentLevel);
    bool Check(SymbolTable *SymTab);
    bool Check2(SymbolTable *SymTab);

};

class BreakStmt : public Stmt 
{
  public:
    BreakStmt(yyltype loc) : Stmt(loc) {}
    const char *GetPrintNameForNode() { return "BreakStmt"; }
    bool Check2(SymbolTable *SymTab);

};

class ReturnStmt : public Stmt  
{
  protected:
    Expr *expr;
  
   public:
    ReturnStmt(yyltype loc, Expr *expr);
    const char *GetPrintNameForNode() { return "ReturnStmt"; }
    void PrintChildren(int indentLevel);
    bool Check(SymbolTable *SymTab);
    bool Check2(SymbolTable *SymTab);

};

class PrintStmt : public Stmt
{
  protected:
    List<Expr*> *args;
    
  public:
    PrintStmt(List<Expr*> *arguments);
    const char *GetPrintNameForNode() { return "PrintStmt"; }
    void PrintChildren(int indentLevel);
    bool Check(SymbolTable *SymTab);
    bool Check2(SymbolTable *SymTab);

};


class IntConstant;

class Case : public Node
{
  protected:
    IntConstant *value;
    List<Stmt*> *stmts;
    
  public:
    Case(IntConstant *v, List<Stmt*> *stmts);
    const char *GetPrintNameForNode() { return value ? "Case" :"Default"; }
    void PrintChildren(int indentLevel);
    bool Check(SymbolTable *SymTab);
    bool Check2(SymbolTable *SymTab);
};

class SwitchStmt : public Stmt
{
  protected:
    Expr *expr;
    List<Case*> *cases;
    
  public:
    SwitchStmt(Expr *e, List<Case*> *cases);
    const char *GetPrintNameForNode() { return "SwitchStmt"; }
    void PrintChildren(int indentLevel);
    bool Check(SymbolTable *SymTab);
    bool Check2(SymbolTable *SymTab);

};

#endif


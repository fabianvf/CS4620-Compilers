/* File: ast_stmt.cc
 * -----------------
 * Implementation of statement node classes.
 */
#include "ast_stmt.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "ast_expr.h"



Program::Program(List<Decl*> *d) {
    Assert(d != NULL);
    (decls=d)->SetParentAll(this);
}

bool Program::Check() {
    symTab = new SymbolTable();
    symTab->add_scope();
    // First Pass: All decls add themselves to the symbol table
    // Errors Caught: redeclaration of a variable within the same scope
    for(int i=0; i < decls->NumElements(); i++){
        decls->Nth(i)->Check(symTab);
   }

   // Second Pass; Need to traverse through AST, and
   // FOR PP3: check if Identifer is used but not declared
   //          check if class overrides an inherited method
   //           (So I need to unify class scopes and the scopes they inherit)             
    symTab->setForPass2();
    symTab->enter_scope();
//    symTab->print_contents();  
    for (int i=0; i < decls->NumElements(); i++){
        decls->Nth(i)->Check2(symTab);
    }

//    symTab->print_contents();
    return true;
}

void Program::PrintChildren(int indentLevel) {
    decls->PrintAll(indentLevel+1);
    printf("\n");
}

StmtBlock::StmtBlock(List<VarDecl*> *d, List<Stmt*> *s) {
    Assert(d != NULL && s != NULL);
    (decls=d)->SetParentAll(this);
    (stmts=s)->SetParentAll(this);
}

bool StmtBlock::Check(SymbolTable *SymTab){
    bool success = true;
    SymTab->add_scope();
    for(int i = 0; i < decls->NumElements(); i++){
        if (success){
            success = decls->Nth(i)->Check(SymTab);        
        }
        else{
            decls->Nth(i)->Check(SymTab);
        }
    }
    
    for(int i = 0; i < stmts->NumElements(); i++){
        if(success){
            success = stmts->Nth(i)->Check(SymTab);
        }
        else{
            stmts->Nth(i)->Check(SymTab);
        }
    }
    SymTab->exit_scope();
    return success;
}

bool StmtBlock::Check2(SymbolTable *SymTab){
    bool success = true;
    SymTab->enter_scope();
    for(int i = 0; i < decls->NumElements(); i++){
        if (!decls->Nth(i)->Check2(SymTab)){
            success = false;
        }
    }
    for (int i=0; i < stmts->NumElements(); i++){
        if (!stmts->Nth(i)->Check2(SymTab)){
            success = false;
        }
    }
    SymTab->exit_scope();
    return success;

}
void StmtBlock::PrintChildren(int indentLevel) {
    decls->PrintAll(indentLevel+1);
    stmts->PrintAll(indentLevel+1);
}

ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) { 
    Assert(t != NULL && b != NULL);
    (test=t)->SetParent(this); 
    (body=b)->SetParent(this);
}

ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b): LoopStmt(t, b) { 
    Assert(i != NULL && t != NULL && s != NULL && b != NULL);
    (init=i)->SetParent(this);
    (step=s)->SetParent(this);
}

bool ForStmt::Check(SymbolTable* SymTab){
    return body->Check(SymTab);
}

bool ForStmt::Check2(SymbolTable* SymTab){
    bool success = true;
        if(test->GetType(SymTab) != Type::boolType){
            ReportError::TestNotBoolean(test);
            success = false;
        }
    if(success){
        success =  body->Check2(SymTab);
    }
    else{
        body->Check2(SymTab);
    }
    return success;
}


void ForStmt::PrintChildren(int indentLevel) {
    init->Print(indentLevel+1, "(init) ");
    test->Print(indentLevel+1, "(test) ");
    step->Print(indentLevel+1, "(step) ");
    body->Print(indentLevel+1, "(body) ");
}

void WhileStmt::PrintChildren(int indentLevel) {
    test->Print(indentLevel+1, "(test) ");
    body->Print(indentLevel+1, "(body) ");
}

bool WhileStmt::Check(SymbolTable* SymTab){
    return body->Check(SymTab);
}

bool WhileStmt::Check2(SymbolTable* SymTab){
    bool success = true;
    if(test->GetType(SymTab) != Type::boolType){
        ReportError::TestNotBoolean(test);
        success = false;
    }
    if(success){
        success =  body->Check2(SymTab);
    }
    else{
        body->Check2(SymTab);
    }
    return success;
}


IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) { 
    Assert(t != NULL && tb != NULL); // else can be NULL
    elseBody = eb;
    if (elseBody) elseBody->SetParent(this);
}

void IfStmt::PrintChildren(int indentLevel) {
    test->Print(indentLevel+1, "(test) ");
    body->Print(indentLevel+1, "(then) ");
    if (elseBody) elseBody->Print(indentLevel+1, "(else) ");
}

bool IfStmt::Check2(SymbolTable* SymTab){
    bool success = true;
    if(test->GetType(SymTab) != Type::boolType){
        ReportError::TestNotBoolean(test);
        success = false;
    }
    if(success){
        success =  body->Check2(SymTab);
    }
    else{
        body->Check2(SymTab);
    }
    
    if(elseBody && !elseBody->Check2(SymTab)){
        return false;
    }
    return success;
}

bool IfStmt::Check(SymbolTable* SymTab){
    bool success = true;
  
    success = body->Check(SymTab);
    if(elseBody && !elseBody->Check(SymTab)){
        return false;
    }
    return success;
}


ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) { 
    Assert(e != NULL);
    (expr=e)->SetParent(this);
}

void ReturnStmt::PrintChildren(int indentLevel) {
    expr->Print(indentLevel+1);
}
  
bool ReturnStmt::Check(SymbolTable* SymTab){
    // Do Nothing 
    return true;
}

bool ReturnStmt::Check2(SymbolTable* SymTab){
    Node *n = this;
    while(dynamic_cast<Program*>(n) == NULL){
        if(dynamic_cast<FnDecl*>(n) != NULL){
            FnDecl* fn = dynamic_cast<FnDecl*>(n);
            if(fn->GetType() != expr->GetType(SymTab)){
                ReportError::ReturnMismatch(this, expr->GetType(SymTab), fn->GetType());
                return false;
            }
            return true;
        }
        n = n->GetParent();
    }
    return false;
}

bool BreakStmt::Check2(SymbolTable *SymTab){
    Node *n = this;
    while(dynamic_cast<Program*>(n) == NULL){
        if(dynamic_cast<LoopStmt*>(n) != NULL){
            return true;
        }
        n = n->GetParent();
    }
    ReportError::BreakOutsideLoop(this);
    return false;
}

PrintStmt::PrintStmt(List<Expr*> *a) {    
    Assert(a != NULL);
    (args=a)->SetParentAll(this);
}

void PrintStmt::PrintChildren(int indentLevel) {
    args->PrintAll(indentLevel+1, "(args) ");
}

bool PrintStmt::Check(SymbolTable* SymTab){
    // Do Nothing
    return true;
}
bool PrintStmt::Check2(SymbolTable* SymTab){
    bool success = true;
    for(int i = 0; i < args->NumElements(); i++){
        Type* t = args->Nth(i)->GetType(SymTab);
        if((t != Type::intType)
            && (t != Type::boolType)
            && (t != Type::stringType)
            && (t != Type::errorType)){
            ReportError::PrintArgMismatch(args->Nth(i), i+1, t);
            success = false;
        }
    }
    return success;
}


Case::Case(IntConstant *v, List<Stmt*> *s) {
    Assert(s != NULL);
    value = v;
    if (value) value->SetParent(this);
    (stmts=s)->SetParentAll(this);
}

void Case::PrintChildren(int indentLevel) {
    if (value) value->Print(indentLevel+1);
    stmts->PrintAll(indentLevel+1);
}


SwitchStmt::SwitchStmt(Expr *e, List<Case*> *c) {
    Assert(e != NULL && c != NULL);
    (expr=e)->SetParent(this);
    (cases=c)->SetParentAll(this);
}
      
void SwitchStmt::PrintChildren(int indentLevel) {
    expr->Print(indentLevel+1);
    cases->PrintAll(indentLevel+1);
}


bool Case::Check(SymbolTable* SymTab){
    bool success = true;

    for(int i = 0; i < stmts->NumElements(); i++){
        if(success){
           success = stmts->Nth(i)->Check(SymTab); 
        }
        else{
            stmts->Nth(i)->Check(SymTab);
        }
    }

    return success;
}


bool Case::Check2(SymbolTable* SymTab){
    bool success = true;

    for(int i = 0; i < stmts->NumElements(); i++){
        if(success){
           success = stmts->Nth(i)->Check2(SymTab); 
        }
        else{
            stmts->Nth(i)->Check2(SymTab);
        }
    }

    return success;
}


bool SwitchStmt::Check(SymbolTable* SymTab){
    bool success = true;
    for(int i = 0; i < cases->NumElements(); i++){
        if(success){
            success = cases->Nth(i)->Check(SymTab);
        }
        else{
            cases->Nth(i)->Check(SymTab);
        }
    }
    if(!expr->Check(SymTab)){
        return false;
    }

    return success;
}


bool SwitchStmt::Check2(SymbolTable* SymTab){
    bool success = true;
    for(int i = 0; i < cases->NumElements(); i++){
        if(success){
            success = cases->Nth(i)->Check2(SymTab);
        }
        else{
            cases->Nth(i)->Check2(SymTab);
        }
    }
    if(!expr->Check2(SymTab)){
        return false;
    }

    return success;
}




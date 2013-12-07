/* File: ast_stmt.cc
 * -----------------
 * Implementation of statement node classes.
 */
#include "ast_stmt.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "ast_expr.h"
#include "scope.h"
#include "errors.h"


Program::Program(List<Decl*> *d) {
    Assert(d != NULL);
    (decls=d)->SetParentAll(this);
}

void Program::Check() {
    nodeScope = new Scope();
    decls->DeclareAll(nodeScope);
    decls->CheckAll();
}

void Program::Emit(CodeGenerator *cg){
    FnDecl *fdecl;
    VarDecl *vdecl;
    // Catch linker error (there must be a main function) before generation starts
    fdecl = dynamic_cast<FnDecl*>(nodeScope->Lookup("main"));
    if(fdecl == NULL){
	    ReportError::NoMainFound();
    }    
    cg->global_offset = 0;
    for(int i = 0; i < decls->NumElements(); i++){
	// Need to separate global and local variable declarations
	vdecl = dynamic_cast<VarDecl*>(decls->Nth(i));
	if(vdecl != NULL){
            vdecl->EmitGlobal(cg);		
	}

	fdecl = dynamic_cast<FnDecl*>(decls->Nth(i));
	if(fdecl != NULL){
	    fdecl->Emit(cg);
	}
	//TODO: For now, only looking at global variable declarations and functions
//	decls->Nth(i)->Emit(cg);
    }
    cg->DoFinalCodeGen();
}
StmtBlock::StmtBlock(List<VarDecl*> *d, List<Stmt*> *s) {
    Assert(d != NULL && s != NULL);
    (decls=d)->SetParentAll(this);
    (stmts=s)->SetParentAll(this);
}
void StmtBlock::Check() {
    nodeScope = new Scope();
    decls->DeclareAll(nodeScope);
    decls->CheckAll();
    stmts->CheckAll();
}
void StmtBlock::Emit(CodeGenerator *cg){
   decls->EmitAll(cg);
   stmts->EmitAll(cg);
}
ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) { 
    Assert(t != NULL && b != NULL);
    (test=t)->SetParent(this); 
    (body=b)->SetParent(this);
}

void ConditionalStmt::Check() {
    body->Check();
}

ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b): LoopStmt(t, b) { 
    Assert(i != NULL && t != NULL && s != NULL && b != NULL);
    (init=i)->SetParent(this);
    (step=s)->SetParent(this);
}

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) { 
    Assert(t != NULL && tb != NULL); // else can be NULL
    elseBody = eb;
    if (elseBody) elseBody->SetParent(this);
}
void IfStmt::Check() {
    ConditionalStmt::Check();
    if (elseBody) elseBody->Check();
}


ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) { 
    Assert(e != NULL);
    (expr=e)->SetParent(this);
}
  
PrintStmt::PrintStmt(List<Expr*> *a) {    
    Assert(a != NULL);
    (args=a)->SetParentAll(this);
}



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
	//TODO: For now, ignore classes and (forever) interfaces
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

void WhileStmt::Emit(CodeGenerator *cg){
   // Steps for while stmt:
   // * Generate label for beginning of while
   // * generate test condition
   // * generate if stmt for ending the while loop
   // * generate body
   // * generate goto to beginning of while loop
   
   char* beginWhile = cg->NewLabel();
   char* endWhile = cg->NewLabel();
   breakLabel = endWhile;

   cg->GenLabel(beginWhile);
   test->Emit(cg);
   cg->GenIfZ(test->GetOffsetLoc(cg), endWhile);
   body->Emit(cg);
   cg->GenGoto(beginWhile);
   cg->GenLabel(endWhile);
}

ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b): LoopStmt(t, b) { 
    Assert(i != NULL && t != NULL && s != NULL && b != NULL);
    (init=i)->SetParent(this);
    (step=s)->SetParent(this);
}

void ForStmt::Emit(CodeGenerator *cg){
// For statements just specialized while statements
//
//     for (int i = 0; i < x; i = i + 1){
//          // Do Something
//     }
//
// Is equavalent to: 
//
//     int i = 0;
//     while (i < x){
//         // Do Something
//         i = i + 1;
//     }
    char* beginFor = cg->NewLabel();
    char* endFor = cg->NewLabel();
    breakLabel = endFor;

    init->Emit(cg);
    cg->GenLabel(beginFor);
    test->Emit(cg);
    cg->GenIfZ(test->GetOffsetLoc(cg), endFor);
    body->Emit(cg);
    step->Emit(cg);
    cg->GenGoto(beginFor);
    cg->GenLabel(endFor);
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

void IfStmt::Emit(CodeGenerator *cg) {
    // Steps for if functions: 
    //  * Emit code for test (as it is always executed)
    //  * Generate a label for the for the end of the if statement (if there is an else block, this points to it)
    //  * Generate the IfZ statement, using the location from test->Emit() and the label to the skip the body
    //  * Generate the body of the if statement
    //  * Generate a goto statement fo possibility
    char* elseLabel;
    test->Emit(cg);
    char* falseLabel = cg->NewLabel();
    cg->GenIfZ(test->GetOffsetLoc(cg), falseLabel);
    body->Emit(cg);
    if(elseBody != NULL){
        elseLabel = cg->NewLabel();
	cg->GenGoto(elseLabel);
    }
    cg->GenLabel(falseLabel);
    if(elseBody != NULL){
	elseBody->Emit(cg);
	cg->GenLabel(elseLabel);
    }
    
    

}
ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) { 
    Assert(e != NULL);
    (expr=e)->SetParent(this);
}

void ReturnStmt::Emit(CodeGenerator *cg){
    // Nice and easy one...
    expr->Emit(cg);
    cg->GenReturn(expr->GetOffsetLoc(cg));
}

void BreakStmt::Emit(CodeGenerator *cg){
    // TODO
    // Trickier... Have to find parent loop statement and find the label you want to skip to...
    // Recursive ascent is simple, but break label may have to be a class variable for loops?
    Node *n = this;
    while(dynamic_cast<Program*>(n) == NULL){
	if(dynamic_cast<LoopStmt*>(n) != NULL){
	    // Now I am inside my parent loop...
	    // So how do I get the label to goto?
	    LoopStmt *ls = dynamic_cast<LoopStmt*>(n);
	    cg->GenGoto(ls->breakLabel);
	    return;
	}
	n = n->GetParent();
    }
}
  
PrintStmt::PrintStmt(List<Expr*> *a) {    
    Assert(a != NULL);
    (args=a)->SetParentAll(this);
}

void PrintStmt::Emit(CodeGenerator *cg){
    BuiltIn b;
    Type *t;
    for(int i = 0; i < args->NumElements(); i++){
	args->Nth(i)->Emit(cg);
	if(args->Nth(i)->GetType() == Type::stringType){ t = Type::stringType; b = PrintString; }
	else if(args->Nth(i)->GetType() == Type::intType) { t = Type::intType; b = PrintInt; }
	else if(args->Nth(i)->GetType() == Type::boolType) {  t = Type::boolType; b = PrintBool; }
	else{ t = Type::errorType; }
	if(t != Type::errorType){
	//    if(dynamic_cast<ArrayAccess*>(args->Nth(i)) != NULL){
	//	cg->GenBuiltInCall(b, dynamic_cast<ArrayAccess*>(args->Nth(i))->GetOffsetLocation(cg));
	//    }
	//    else{
	        cg->GenBuiltInCall(b, args->Nth(i)->GetOffsetLoc(cg));	
	//    }
	}
    }
}

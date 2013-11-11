/* File: ast_expr.cc
 * -----------------
 * Implementation of expression node classes.
 */
#include "ast_expr.h"
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h>



IntConstant::IntConstant(yyltype loc, int val) : Expr(loc) {
    value = val;
}
void IntConstant::PrintChildren(int indentLevel) { 
    printf("%d", value);
}

DoubleConstant::DoubleConstant(yyltype loc, double val) : Expr(loc) {
    value = val;
}
void DoubleConstant::PrintChildren(int indentLevel) { 
    printf("%g", value);
}

BoolConstant::BoolConstant(yyltype loc, bool val) : Expr(loc) {
    value = val;
}
void BoolConstant::PrintChildren(int indentLevel) { 
    printf("%s", value ? "true" : "false");
}

StringConstant::StringConstant(yyltype loc, const char *val) : Expr(loc) {
    Assert(val != NULL);
    value = strdup(val);
}
void StringConstant::PrintChildren(int indentLevel) { 
    printf("%s",value);
}

Operator::Operator(yyltype loc, const char *tok) : Node(loc) {
    Assert(tok != NULL);
    strncpy(tokenString, tok, sizeof(tokenString));
}

void Operator::PrintChildren(int indentLevel) {
    printf("%s",tokenString);
}

CompoundExpr::CompoundExpr(Expr *l, Operator *o, Expr *r) 
  : Expr(Join(l->GetLocation(), r->GetLocation())) {
    Assert(l != NULL && o != NULL && r != NULL);
    (op=o)->SetParent(this);
    (left=l)->SetParent(this); 
    (right=r)->SetParent(this);
}

CompoundExpr::CompoundExpr(Operator *o, Expr *r) 
  : Expr(Join(o->GetLocation(), r->GetLocation())) {
    Assert(o != NULL && r != NULL);
    left = NULL; 
    (op=o)->SetParent(this);
    (right=r)->SetParent(this);
}

void CompoundExpr::PrintChildren(int indentLevel) {
   if (left) left->Print(indentLevel+1);
   op->Print(indentLevel+1);
   right->Print(indentLevel+1);
}
   

Type *ArithmeticExpr::GetType(SymbolTable *SymTab){
    Type *rightType = right->GetType(SymTab);
    if(left == NULL){
        if((rightType != Type::errorType) && (rightType != Type::intType) && (rightType != Type::doubleType)){
            ReportError::IncompatibleOperand(op, rightType);
            return Type::errorType;
        }
        return rightType;
    }
    Type *leftType = left->GetType(SymTab);
    
    if((leftType != rightType)){
        if(leftType != Type::errorType && rightType != Type::errorType){
            ReportError::IncompatibleOperands(op, leftType, rightType);
            return Type::errorType; 
        }
    }
    return rightType;
}

bool ArithmeticExpr::Check2(SymbolTable *SymTab){
    return (this->GetType(SymTab) != Type::errorType);
}


Type *RelationalExpr::GetType(SymbolTable *SymTab){
    Type *leftType = left->GetType(SymTab);
    Type *rightType = right->GetType(SymTab);
    if((leftType != rightType) || ((leftType != Type::errorType) && (rightType != Type::errorType) && (leftType != Type::intType) && (leftType != Type::doubleType)) || ((rightType != Type::intType) && (rightType != Type::doubleType))){
        ReportError::IncompatibleOperands(op, leftType, rightType);
    }
    return Type::boolType;
}

bool RelationalExpr::Check2(SymbolTable *SymTab){
    return (this->GetType(SymTab) != Type::errorType);
}
Type *EqualityExpr::GetType(SymbolTable *SymTab){
    Type *leftType = left->GetType(SymTab);
    Type *rightType = right->GetType(SymTab);
    if((leftType != rightType) || ((leftType != Type::errorType) && (rightType != Type::errorType) )){
        ReportError::IncompatibleOperands(op, leftType, rightType);
    }
    return Type::boolType;
}

bool EqualityExpr::Check2(SymbolTable *SymTab){
    return (this->GetType(SymTab) != Type::errorType);
}


Type *LogicalExpr::GetType(SymbolTable *SymTab){
    Type *rightType = right->GetType(SymTab);
    if(left == NULL){
        if((rightType != Type::boolType) && (rightType != Type::errorType)){
            ReportError::IncompatibleOperand(op, rightType);
        }
        return Type::boolType;
    }
    Type *leftType = left->GetType(SymTab);

    if((leftType != rightType) || ((leftType != Type::boolType) && (leftType != Type::errorType) && (rightType != Type::boolType) && (rightType != Type::errorType))) {
        ReportError::IncompatibleOperands(op, leftType, rightType);
    }
    return Type::boolType;
}

bool LogicalExpr::Check2(SymbolTable *SymTab){
    return (this->GetType(SymTab) != Type::errorType);
}
Type *AssignExpr::GetType(SymbolTable *SymTab){
    Type *leftType = left->GetType(SymTab);
    Type *rightType = right->GetType(SymTab);
    if((leftType != rightType)){
        if((dynamic_cast<NamedType*>(leftType) != NULL) && (rightType == Type::nullType)){
            return leftType;
        }
        if((leftType != Type::errorType) && (rightType != Type::errorType)){
            ReportError::IncompatibleOperands(op, leftType, rightType); 
        }
    }
    return leftType;
}

bool AssignExpr::Check2(SymbolTable *SymTab){
    return (this->GetType(SymTab) != Type::errorType);
}
 
ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc) {
    (base=b)->SetParent(this); 
    (subscript=s)->SetParent(this);
}

void ArrayAccess::PrintChildren(int indentLevel) {
    base->Print(indentLevel+1);
    subscript->Print(indentLevel+1, "(subscript) ");
  }
     
FieldAccess::FieldAccess(Expr *b, Identifier *f) 
  : LValue(b? Join(b->GetLocation(), f->GetLocation()) : *f->GetLocation()) {
    Assert(f != NULL); // b can be be NULL (just means no explicit base)
    base = b; 
    if (base) base->SetParent(this); 
    (field=f)->SetParent(this);
}


  void FieldAccess::PrintChildren(int indentLevel) {
    if (base) base->Print(indentLevel+1);
    field->Print(indentLevel+1);
  }

Type *FieldAccess::GetType(SymbolTable *SymTab){
    //TODO:Get printing of errors with arrays working 
    // This bit is for class variables
    if(base != NULL){
        ClassDecl *cDecl = dynamic_cast<ClassDecl*>(SymTab->lookup(base->GetType(SymTab)->GetName())); 
        Type* bt = base->GetType(SymTab);
        
        if (cDecl == NULL){
            ReportError::FieldNotFoundInBase(field, bt);
            return Type::errorType;
        }
        VarDecl* v = dynamic_cast<VarDecl*>(SymTab->find_in_scope(field->GetName(), cDecl->getScopeIndex()));
        if (v == NULL){
            ReportError::FieldNotFoundInBase(field, bt);
            return Type::errorType;
        }
 
        if(!SymTab->in_class_scope()){
            ReportError::InaccessibleField(field, bt);
            return Type::errorType;
        }
        return v->GetType();
   }
    
    // This bit is for normal variables
    VarDecl* d = dynamic_cast<VarDecl*>(SymTab->lookup(field->GetName()));
    if(d == NULL){
        ReportError::IdentifierNotDeclared(field, LookingForVariable);
        return Type::errorType;
    }
    else{
        return d->GetType();
    }
}

bool FieldAccess::Check2(SymbolTable *SymTab){
    return (this->GetType(SymTab) != Type::errorType);
}

Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc)  {
    Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
    base = b;
    if (base) base->SetParent(this);
    (field=f)->SetParent(this);
    (actuals=a)->SetParentAll(this);
}


Type *Call::GetType(SymbolTable *SymTab){
    // TODO: Need to check if base is used, and if so, if within class

    for(int i = 0; i < actuals->NumElements(); i++){
        actuals->Nth(i)->Check2(SymTab);
    }
    // This bit is for class method calls
    if(base != NULL){
        ClassDecl* cDecl = dynamic_cast<ClassDecl*>(SymTab->lookup(base->GetType(SymTab)->GetName()));
        if(cDecl == NULL){
            ReportError::FieldNotFoundInBase(field, base->GetType(SymTab));
            return Type::errorType;
        }
        FnDecl *f = dynamic_cast<FnDecl*>(SymTab->find_in_scope(field->GetName(), cDecl->getScopeIndex()));
        if(f == NULL){
           ReportError::FieldNotFoundInBase(field, base->GetType(SymTab));
           return Type::errorType;
        }
        return f->GetType();
    }
    
    // This bit is for normal function calls
    FnDecl *fn = dynamic_cast<FnDecl*>(SymTab->lookup(field->GetName()));
    if(fn == NULL){
        ReportError::IdentifierNotDeclared(field, LookingForFunction);
        return Type::errorType;
    }
    int num = actuals->NumElements();
    if(fn->GetFormals()->NumElements() != actuals->NumElements()){
        ReportError::NumArgsMismatch(field,fn->GetFormals()->NumElements(), actuals->NumElements() );
        if(fn->GetFormals()->NumElements() < actuals->NumElements()){ 
            num = fn->GetFormals()->NumElements();
        }
    }
    Expr* argument;
    VarDecl* formal;
    for(int i =0; i < num;i++){
        argument = actuals->Nth(i);
        formal = fn->GetFormals()->Nth(i);
        if(formal->GetType() != argument->GetType(SymTab)){
            ReportError::ArgMismatch(argument, i+1, argument->GetType(SymTab), formal->GetType());  
        }
    }
    
    return fn->GetType();
 
}
bool Call::Check2(SymbolTable *SymTab){
    return (this->GetType(SymTab) != Type::errorType);   
}
void Call::PrintChildren(int indentLevel) {
    if (base) base->Print(indentLevel+1);
    field->Print(indentLevel+1);
    actuals->PrintAll(indentLevel+1, "(actuals) ");
}

bool This::Check2(SymbolTable *SymTab){
    if(!SymTab->in_class_scope()){
        ReportError::ThisOutsideClassScope(this);
        return false;
    }
    return true;
}

Type *This::GetType(SymbolTable *SymTab){
    if(!this->Check2(SymTab)){
        return Type::errorType;
    }
    return Type::intType;
}


NewExpr::NewExpr(yyltype loc, NamedType *c) : Expr(loc) { 
  Assert(c != NULL);
  (cType=c)->SetParent(this);
}

void NewExpr::PrintChildren(int indentLevel) {	
    cType->Print(indentLevel+1);
}

NewArrayExpr::NewArrayExpr(yyltype loc, Expr *sz, Type *et) : Expr(loc) {
    Assert(sz != NULL && et != NULL);
    (size=sz)->SetParent(this); 
    (elemType=et)->SetParent(this);
}

void NewArrayExpr::PrintChildren(int indentLevel) {
    size->Print(indentLevel+1);
    elemType->Print(indentLevel+1);
}

PostfixExpr::PostfixExpr(LValue *lv, Operator *o) : Expr(Join(lv->GetLocation(), o->GetLocation())) {
    Assert(lv != NULL && o != NULL);
    (lvalue=lv)->SetParent(this);
    (op=o)->SetParent(this);
}

void PostfixExpr::PrintChildren(int indentLevel) {
    lvalue->Print(indentLevel+1);
    op->Print(indentLevel+1);
}
      

/* File: ast_decl.cc
 * -----------------
 * Implementation of Decl node classes.
 */
#include "ast_decl.h"
#include "ast_type.h"
#include "ast_stmt.h"
#include "errors.h"        
          
Decl::Decl(Identifier *n) : Node(*n->GetLocation()) {
    Assert(n != NULL);
    (id=n)->SetParent(this); 
}

char* Decl::GetName(){
    return id->GetName();
}



VarDecl::VarDecl(Identifier *n, Type *t) : Decl(n) {
    Assert(n != NULL && t != NULL);
    (type=t)->SetParent(this);
}

bool VarDecl::Check(SymbolTable *SymTab){
    if (SymTab->local_lookup(GetName()) != NULL){
        ReportError::DeclConflict(this, SymTab->local_lookup(id->GetName()));
        return false;
    }
    return SymTab->add(this);
}

bool VarDecl::Check2(SymbolTable *SymTab){
    if(!(type->Check2(SymTab))){
        ReportError::IdentifierNotDeclared(type->GetId(), LookingForType);
        type = Type::errorType;
        return false;
    }
    return true;
}


void VarDecl::PrintChildren(int indentLevel) { 
   type->Print(indentLevel+1);
   id->Print(indentLevel+1);
}

ClassDecl::ClassDecl(Identifier *n, NamedType *ex, List<NamedType*> *imp, List<Decl*> *m) : Decl(n) {
    // extends can be NULL, impl & mem may be empty lists but cannot be NULL
    Assert(n != NULL && imp != NULL && m != NULL);     
    extends = ex;
    if (extends) extends->SetParent(this);
    (implements=imp)->SetParentAll(this);
    (members=m)->SetParentAll(this);
}

bool ClassDecl::Check(SymbolTable *SymTab){
    if (SymTab->local_lookup(GetName()) != NULL){
        ReportError::DeclConflict(this, SymTab->local_lookup(id->GetName()));
        return false;
    }
    if(!SymTab->add(this)){
        return false;
    }
    else{
        if (extends != NULL || implements->NumElements() > 0){
            inherits = true;
        }
        SymTab->add_scope();
        SymTab->add_class_scope();
        scopeIndex = SymTab->get_scope_level();
        for(int i = 0; i < members->NumElements(); i++){
            members->Nth(i)->Check(SymTab);
        }
        SymTab->exit_scope();
    }
    return true;
}

bool ClassDecl::Check2(SymbolTable *SymTab){
    //TODO: Something regarding inheritance and interfaces goes here
    List<int> *add_scopes = new List<int>();
    bool success = true;

    // Adds the scope of an extended class to the current one
    if(extends != NULL ){
        if(!extends->Check2(SymTab)){
            ReportError::IdentifierNotDeclared(extends->GetId(), LookingForClass);
            success = false;
        }
        else{
            add_scopes->Append(SymTab->lookup(extends->GetId()->GetName())->getScopeIndex());
        }
//        std::cout << SymTab->lookup(extends->GetId()->GetName())->scopeIndex << std::endl;
    }

    // Adds the scope of inherited classes to the current one
    for (int i = 0; i < implements->NumElements(); i++){
        if(!implements->Nth(i)->Check2(SymTab)){
            ReportError::IdentifierNotDeclared(implements->Nth(i)->GetId(), LookingForInterface);
            success = false;
        }
        else{
            add_scopes->Append(SymTab->lookup(implements->Nth(i)->GetId()->GetName())->getScopeIndex());
        }
//        std::cout << SymTab->lookup(implements->Nth(i)->GetId()->GetName())->getScopeIndex() << std::endl;
   
    }
    
    SymTab->enter_scope();
    for(int i = 0; i < add_scopes->NumElements(); i++){
        if (!SymTab->unify(scopeIndex, add_scopes->Nth(i))){
            success = false;
        }
    }
    for(int i = 0; i < members->NumElements(); i++){
        if(success){
            success =  members->Nth(i)->Check2(SymTab);
        }
        else{
            members->Nth(i)->Check2(SymTab);
        }
    }
    SymTab->exit_scope();
    return success;
}


void ClassDecl::PrintChildren(int indentLevel) {
    id->Print(indentLevel+1);
    if (extends) extends->Print(indentLevel+1, "(extends) ");
    implements->PrintAll(indentLevel+1, "(implements) ");
    members->PrintAll(indentLevel+1);
}


InterfaceDecl::InterfaceDecl(Identifier *n, List<Decl*> *m) : Decl(n) {
    Assert(n != NULL && m != NULL);
    (members=m)->SetParentAll(this);
}

bool InterfaceDecl::Check(SymbolTable *SymTab){
    if (SymTab->local_lookup(GetName()) != NULL){
        ReportError::DeclConflict(this, SymTab->local_lookup(id->GetName()));
        return false;
    }
    if(!SymTab->add(this)){
        return false;
    }
    else{
        SymTab->add_scope();
        scopeIndex = SymTab->get_scope_level();
        for(int i = 0; i < members->NumElements(); i++){
            members->Nth(i)->Check(SymTab);
        }
        SymTab->exit_scope();
    }
    return true;
}

bool InterfaceDecl::Check2(SymbolTable *SymTab){
    SymTab->enter_scope();
    SymTab->exit_scope();
    return true;
}




void InterfaceDecl::PrintChildren(int indentLevel) {
    id->Print(indentLevel+1);
    members->PrintAll(indentLevel+1);
}
	
FnDecl::FnDecl(Identifier *n, Type *r, List<VarDecl*> *d) : Decl(n) {
    Assert(n != NULL && r!= NULL && d != NULL);
    (returnType=r)->SetParent(this);
    (formals=d)->SetParentAll(this);
    body = NULL;
}

bool FnDecl::Check(SymbolTable *SymTab){
    bool success = true;
    if (SymTab->local_lookup(GetName()) != NULL){
        ReportError::DeclConflict(this, SymTab->local_lookup(id->GetName()));
        success = false;
    }
    if(!SymTab->add(this)){
        success = false;
    }
    SymTab->add_scope();   
    for(int i = 0; i < formals->NumElements(); i++){
        if (success == true){
            success =formals->Nth(i)->Check(SymTab);
        }
        else{
            formals->Nth(i)->Check(SymTab);
        }
    }
    if((body !=NULL) && (!(body->Check(SymTab)))){ 
           success = false;    
    }
    SymTab->exit_scope();
    return success;
}


bool FnDecl::Check2(SymbolTable *SymTab){
    bool success = true;
    if (!(returnType->Check2(SymTab))){
        ReportError::IdentifierNotDeclared(returnType->GetId(), LookingForType);
        success = false;
    }
    SymTab->enter_scope();
    //std::cout << "In Function " << GetName() << " Formals: ";
    for(int i = 0; i < formals->NumElements(); i++){
        //std::cout << "\n\t" << SymTab->get_scope_level() << std::endl;
        if(!(formals->Nth(i)->Check2(SymTab))){
            success = false;
        }
        //std::cout << "\n\t" << SymTab->get_scope_level() << std::endl;

    }
    if((body != NULL)&&(!(body->Check2(SymTab)))){
        success = false;
    }
    SymTab->exit_scope();
    return success;
}


void FnDecl::SetFunctionBody(Stmt *b) { 
    (body=b)->SetParent(this);
}

void FnDecl::PrintChildren(int indentLevel) {
    returnType->Print(indentLevel+1, "(return type) ");
    id->Print(indentLevel+1);
    formals->PrintAll(indentLevel+1, "(formals) ");
    if (body) body->Print(indentLevel+1, "(body) ");
}



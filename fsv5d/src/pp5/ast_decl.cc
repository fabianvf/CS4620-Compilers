/* File: ast_decl.cc
 * -----------------
 * Implementation of Decl node classes.
 */
#include "ast_decl.h"
#include "ast_type.h"
#include "ast_stmt.h"
#include "scope.h"
#include "errors.h"
#include <string>


Decl::Decl(Identifier *n) : Node(*n->GetLocation()) {
    Assert(n != NULL);
    (id=n)->SetParent(this); 
}

bool Decl::ConflictsWithPrevious(Decl *prev) {
    ReportError::DeclConflict(this, prev);
    return true;
}

VarDecl::VarDecl(Identifier *n, Type *t) : Decl(n) {
    Assert(n != NULL && t != NULL);
    (type=t)->SetParent(this);
}
  
void VarDecl::Check() { type->Check(); }

// Code generation for local variable declarations
void VarDecl::Emit(CodeGenerator *cg){
    //printf(GetName());
    // Add the variable size to the current offset
    int offset = cg->var_offset;

    // This should never happen  
    if(offset > cg->OffsetToFirstLocal){
        offset = cg->OffsetToFirstLocal;
	printf("Error: Local offset was greater than -8!");
    }
    offsetLoc = new Location(fpRelative, offset, GetName());
    cg->var_offset -= cg->VarSize;
    isMember=false;
}

// Code generation for global variable declarations
void VarDecl::EmitGlobal(CodeGenerator *cg){
    // Add the variable size to the current offset
    int offset = cg->global_offset;

    // This should never happen
    if(offset < cg->OffsetToFirstGlobal){
        offset = cg->OffsetToFirstGlobal;
	printf("Error: Global offset was less than 0!");
    }

    offsetLoc = new Location(gpRelative, offset, GetName());
    cg->global_offset += cg->VarSize;
    isMember = false;
}

void VarDecl::EmitFormal(CodeGenerator *cg){	
    //printf(GetName());
    int offset = cg->formal_offset;
    // This should never happen
    if(offset < cg->OffsetToFirstParam){
        offset = cg->OffsetToFirstParam;
	printf("Error: Formal offset was less than +4!");
    }
    offsetLoc = new Location(fpRelative, offset, GetName());
    cg->formal_offset += cg->VarSize;
    isMember = false;
}

void VarDecl::EmitMember(CodeGenerator *cg){
    // Just need to store offset from vtable pointer
//    vtableOffset = cg->class_offset;
    cg->class_offset += cg->VarSize;
    isMember = true;
}

ClassDecl::ClassDecl(Identifier *n, NamedType *ex, List<NamedType*> *imp, List<Decl*> *m) : Decl(n) {
    // extends can be NULL, impl & mem may be empty lists but cannot be NULL
    Assert(n != NULL && imp != NULL && m != NULL);     
    extends = ex;
    if (extends) extends->SetParent(this);
    (implements=imp)->SetParentAll(this);
    (members=m)->SetParentAll(this);
    cType = new NamedType(n);
    cType->SetParent(this);
    convImp = NULL;
}

void ClassDecl::Check() {

    if (extends && !extends->IsClass()) {
        ReportError::IdentifierNotDeclared(extends->GetId(), LookingForClass);
        extends = NULL;
    }
    for (int i = 0; i < implements->NumElements(); i++) {
        NamedType *in = implements->Nth(i);
        if (!in->IsInterface()) {
            ReportError::IdentifierNotDeclared(in->GetId(), LookingForInterface);
            implements->RemoveAt(i--);
        }
    }
    PrepareScope();
    members->CheckAll();
}

// This is not done very cleanly. I should sit down and sort this out. Right now
// I was using the copy-in strategy from the old compiler, but I think the link to
// parent may be the better way now.
Scope *ClassDecl::PrepareScope()
{
    if (nodeScope) return nodeScope;
    nodeScope = new Scope();  
    if (extends) {
        ClassDecl *ext = dynamic_cast<ClassDecl*>(parent->FindDecl(extends->GetId())); 
        if (ext) nodeScope->CopyFromScope(ext->PrepareScope(), this);
    }
    convImp = new List<InterfaceDecl*>;
    for (int i = 0; i < implements->NumElements(); i++) {
        NamedType *in = implements->Nth(i);
        InterfaceDecl *id = dynamic_cast<InterfaceDecl*>(in->FindDecl(in->GetId()));
        if (id) {
		nodeScope->CopyFromScope(id->PrepareScope(), NULL);
            convImp->Append(id);
	  }
    }
    members->DeclareAll(nodeScope);
    return nodeScope;
}

void ClassDecl::Emit(CodeGenerator *cg){
    // Will be layed out as example in slides was- class points to address of vtable, 
    // which is followed by each field of the class, with inherited variables appearing first.
    //
    // Steps for declaring class:
    //  * Store class variables at correct offsets from class
    //  * Store function declarations correctly in Vtable...
    //  * Do inheritance stuff as well
    List<const char*> *methodLabels = new List<const char*>();
    cg->class_offset = cg->VarSize;

    FnDecl *fdecl;
    VarDecl*vdecl;
    for( int i = 0; i < members->NumElements(); i++){
	// First attempt was stupid, obviously vardecls go before fndecls...
	vdecl = dynamic_cast<VarDecl*>(members->Nth(i));
	if (vdecl != NULL){
	    vdecl->EmitMember(cg);	    
	}
    }

    for( int i = 0; i < members->NumElements(); i++){
        fdecl = dynamic_cast<FnDecl*>(members->Nth(i));
        if(fdecl != NULL){
            // May have to make FnDecl::EmitMember(cg, this)...
            fdecl->Emit(cg);
	    methodLabels->Append(("_" + std::string(GetName()) + "." + std::string(fdecl->GetName())).c_str());
	}
    }
   // Is it really this easy?
    cg->GenVTable(GetName(), methodLabels);
}

int ClassDecl::GetSize(){
    int size = 4;
    for(int i = 0; i < members->NumElements(); i++){
	if(dynamic_cast<VarDecl*>(members->Nth(i)) != NULL){
	    dynamic_cast<VarDecl*>(members->Nth(i))->vtableOffset = size;
	    size += 4;
	}
    }
    return size;
}

InterfaceDecl::InterfaceDecl(Identifier *n, List<Decl*> *m) : Decl(n) {
    Assert(n != NULL && m != NULL);
    (members=m)->SetParentAll(this);
}

void InterfaceDecl::Check() {
    PrepareScope();
    members->CheckAll();
}
  
Scope *InterfaceDecl::PrepareScope() {
    if (nodeScope) return nodeScope;
    nodeScope = new Scope();  
    members->DeclareAll(nodeScope);
    return nodeScope;
}
	
FnDecl::FnDecl(Identifier *n, Type *r, List<VarDecl*> *d) : Decl(n) {
    Assert(n != NULL && r!= NULL && d != NULL);
    (returnType=r)->SetParent(this);
    (formals=d)->SetParentAll(this);
    body = NULL;
}

void FnDecl::SetFunctionBody(Stmt *b) { 
    (body=b)->SetParent(this);
}

void FnDecl::Check() {
    returnType->Check();
    if (body) {
        nodeScope = new Scope();
        formals->DeclareAll(nodeScope);
        formals->CheckAll();
	body->Check();
    }
}

bool FnDecl::ConflictsWithPrevious(Decl *prev) {
 // special case error for method override
    if (IsMethodDecl() && prev->IsMethodDecl() && parent != prev->GetParent()) { 
        if (!MatchesPrototype(dynamic_cast<FnDecl*>(prev))) {
            ReportError::OverrideMismatch(this);
            return true;
        }
        return false;
    }
    ReportError::DeclConflict(this, prev);
    return true;
}

bool FnDecl::IsMethodDecl() 
  { return dynamic_cast<ClassDecl*>(parent) != NULL || dynamic_cast<InterfaceDecl*>(parent) != NULL; }

bool FnDecl::MatchesPrototype(FnDecl *other) {
    if (!returnType->IsEquivalentTo(other->returnType)) return false;
    if (formals->NumElements() != other->formals->NumElements())
        return false;
    for (int i = 0; i < formals->NumElements(); i++)
        if (!formals->Nth(i)->GetDeclaredType()->IsEquivalentTo(other->formals->Nth(i)->GetDeclaredType()))
            return false;
    return true;
}

void FnDecl::Emit(CodeGenerator *cg){
    // Deal with offset (resets when entering functions, but returns to original value after exit
    int offsetOfParent = cg->var_offset;
    cg->var_offset = cg->OffsetToFirstLocal;

    // Names the functions
    std::string fnName = std::string(GetName());
    if(fnName == "main"){
        cg->GenLabel(fnName.c_str());
    } 
    else if(IsMethodDecl()){
    	ClassDecl* parentClass = dynamic_cast<ClassDecl*>(parent);
	fnName = "_" + std::string(parentClass->GetName()) + "." + fnName;
	cg->GenLabel(fnName.c_str());
    }
    else{
        fnName = "_" + fnName;
        cg->GenLabel(fnName.c_str());
    }
    //this->label = fnName;

    //printf(GetName());

    //Generate begin func statement (including getting location and getting correct size
    BeginFunc *beginFunc = cg->GenBeginFunc(); 

    // Formals
    if(formals != NULL){
        cg->formal_offset = cg->OffsetToFirstParam;
        for (int i = 0; i < formals->NumElements(); i++){
	    formals->Nth(i)->EmitFormal(cg);
        }
    }

    // Body 
    if (body != NULL){
        body->Emit(cg);
    }
    // Backpatch size into begin func statement
    beginFunc->SetFrameSize(-1 * (cg->var_offset - cg->OffsetToFirstLocal));
    cg->var_offset = offsetOfParent;
    cg->GenEndFunc();
}


/* File: ast_expr.cc
 * -----------------
 * Implementation of expression node classes.
 */
#include "ast_expr.h"
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h>
#include "errors.h"


IntConstant::IntConstant(yyltype loc, int val) : Expr(loc) {
    value = val;
}

DoubleConstant::DoubleConstant(yyltype loc, double val) : Expr(loc) {
    value = val;
}

BoolConstant::BoolConstant(yyltype loc, bool val) : Expr(loc) {
    value = val;
}

StringConstant::StringConstant(yyltype loc, const char *val) : Expr(loc) {
    Assert(val != NULL);
    value = strdup(val);
}

Operator::Operator(yyltype loc, const char *tok) : Node(loc) {
    Assert(tok != NULL);
    strncpy(tokenString, tok, sizeof(tokenString));
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
   
  
ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc) {
    (base=b)->SetParent(this); 
    (subscript=s)->SetParent(this);
}
     
FieldAccess::FieldAccess(Expr *b, Identifier *f) 
  : LValue(b? Join(b->GetLocation(), f->GetLocation()) : *f->GetLocation()) {
    Assert(f != NULL); // b can be be NULL (just means no explicit base)
    base = b; 
    if (base) base->SetParent(this); 
    (field=f)->SetParent(this);
}


Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc)  {
    Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
    base = b;
    if (base) base->SetParent(this);
    (field=f)->SetParent(this);
    (actuals=a)->SetParentAll(this);
}
 

NewExpr::NewExpr(yyltype loc, NamedType *c) : Expr(loc) { 
  Assert(c != NULL);
  (cType=c)->SetParent(this);
}


NewArrayExpr::NewArrayExpr(yyltype loc, Expr *sz, Type *et) : Expr(loc) {
    Assert(sz != NULL && et != NULL);
    (size=sz)->SetParent(this); 
    (elemType=et)->SetParent(this);
}

/*
   ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
   +                         PP5 Emit() implementations below                         + 
   ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
*/

void IntConstant::Emit(CodeGenerator *cg){
    offsetLoc = cg->GenLoadConstant(value);
}

void StringConstant::Emit(CodeGenerator *cg){
    offsetLoc = cg->GenLoadConstant(value);
}

void BoolConstant::Emit(CodeGenerator *cg){
    if(value){
        offsetLoc = cg->GenLoadConstant(1);
    }
    else{
        offsetLoc = cg->GenLoadConstant(0);
    }
}

void NullConstant::Emit(CodeGenerator *cg){
    offsetLoc = cg->GenLoadConstant(0);
}

void FieldAccess::Emit(CodeGenerator *cg){
    if (base != NULL){
	// Class stuff with explicit this goes here eventually
	return;
    }
    // Implicit this - if I am in a class scope, then this is implicit
    VarDecl* vdecl = dynamic_cast<VarDecl*>(FindDecl(field));
    if(vdecl->isMember){
	// Now I need to get a location that points to the correct address in the class...
	this->classPointer = cg->ThisPtr;
	this->vtableAddress = vdecl->vtableOffset;
//	std::cout << vtableAddress << std::endl;
//	Assert(cg->ThisPtr != NULL);
//	Assert(classPointer != NULL);
        return;
    }
    // Normal variables
    offsetLoc = FindDecl(field)->GetOffsetLoc(cg); 
}

// Just like array access, shouldn't load it immediately (NEVER MIND COULDN"T GET WORKING)
Location *FieldAccess::GetOffsetLoc(CodeGenerator *cg){
    return offsetLoc;
}
void AssignExpr::Emit(CodeGenerator *cg){
    // Generate assignment, by first evaluating the left and right (to get the address)
    // and then by assigning the value in the right location to the left location
    left->Emit(cg);
    right->Emit(cg);
    
    if((dynamic_cast<ArrayAccess*>(left) != NULL)){  // || (dynamic_cast<NewArrayExpr*>(right) != NULL)){
      cg->GenStore(left->offsetLoc, right->GetOffsetLoc(cg));
      return;
    }
    // Assigning to a member variable
    VarDecl* vdecl = dynamic_cast<VarDecl*>(FindDecl(dynamic_cast<FieldAccess*>(left)->GetId()));
    if(vdecl->isMember){
	cg->GenStore(dynamic_cast<FieldAccess*>(left)->classPointer, right->GetOffsetLoc(cg), vdecl->vtableOffset);
    }
/**    else if(dynamic_cast<NamedType*>(FindDecl(dynamic_cast<FieldAccess*>(left)->GetId())->GetType()) != NULL){
	VarDecl* vdecl= dynamic_cast<VarDecl*>(FindDecl(dynamic_cast<FieldAccess*>(left)->GetId()));
	if(vdecl->isMember){
	    cg->GenStore(cg->ThisPtr, right->GetOffsetLoc(cg), vdecl->vtableOffset);
	    return;
	}
	
   }*/
    if((left->GetOffsetLoc(cg) != NULL) && (right->GetOffsetLoc(cg) != NULL)){
        cg->GenAssign(left->GetOffsetLoc(cg), right->GetOffsetLoc(cg));
    }
}

void ArithmeticExpr::Emit(CodeGenerator *cg){
    if(left != NULL) left->Emit(cg);
    right->Emit(cg);
    if( left != NULL ){ // Binary operators (everything but unary -)
	offsetLoc = cg->GenBinaryOp(op->str(), left->GetOffsetLoc(cg), right->GetOffsetLoc(cg));
    }
    else{
	offsetLoc = cg->GenBinaryOp(op->str(), cg->GenLoadConstant(0), right->GetOffsetLoc(cg));
    }
}

void RelationalExpr::Emit(CodeGenerator *cg){
// Relational ops availabe in tac file : <
// Well that's a bit limiting isn't it...
    std::string opName = std::string(op->str());
    //printf(opName.c_str());
    left->Emit(cg);
    right->Emit(cg);

    // Uses "<", only defined relational symbol
    if(opName == "<") {
        offsetLoc = cg->GenBinaryOp(op->str(), left->GetOffsetLoc(cg), right->GetOffsetLoc(cg));
    }

    // 2 > 1 is equivalent to 1 < 2
    else if(opName == ">") {
	offsetLoc = cg->GenBinaryOp("<", right->GetOffsetLoc(cg), left->GetOffsetLoc(cg));
    }
    // 1 <= 2 is equivalent to (1 < 2) || (1 == 2), so this is a three step process
    else if (opName == "<=") {
	 Location* lt = cg->GenBinaryOp("<", left->GetOffsetLoc(cg), right->GetOffsetLoc(cg));
	 Location* eq = cg->GenBinaryOp("==", left->GetOffsetLoc(cg), right->GetOffsetLoc(cg));
	 offsetLoc = cg->GenBinaryOp("||", lt, eq);
    }
    // 2 >= 1 ~> 1 <= 2 ~> (1 < 2) || (1 == 2), so this is a three step process as well
    else if (opName == ">="){
        Location* gt = cg->GenBinaryOp("<", right->GetOffsetLoc(cg), left->GetOffsetLoc(cg));
        Location* eq = cg->GenBinaryOp("==", left->GetOffsetLoc(cg), right->GetOffsetLoc(cg));
	offsetLoc = cg->GenBinaryOp("||", gt, eq);
    }
}

void EqualityExpr::Emit(CodeGenerator *cg){
// Equality ops available in tac file : "=="
// String equality needs to be deep (not pointer level)
    std::string opName = std::string(op->str());
    left->Emit(cg);
    right->Emit(cg);
    // uses "==", only defined equality operator
    if(opName == "=="){
	if(left->GetType() == Type::stringType){
            offsetLoc = cg->GenBuiltInCall(StringEqual, left->GetOffsetLoc(cg), right->GetOffsetLoc(cg));
	}
	else{
	    offsetLoc = cg->GenBinaryOp("==", left->GetOffsetLoc(cg), right->GetOffsetLoc(cg));
	}
    }
    // 1 != 2 is equivalent to (1 == 2) == false (0)
    else if(opName == "!="){
	if(left->GetType() == Type::stringType){
	    Location* eq = cg->GenBuiltInCall(StringEqual, left->GetOffsetLoc(cg), right->GetOffsetLoc(cg));
	    offsetLoc = cg->GenBinaryOp("==", eq, cg->GenLoadConstant(0));
	}
	else{
	    Location* eq = cg->GenBinaryOp("==", left->GetOffsetLoc(cg), right->GetOffsetLoc(cg));
	    offsetLoc = cg->GenBinaryOp("==", eq, cg->GenLoadConstant(0));	
	}
    }

}

void LogicalExpr::Emit(CodeGenerator *cg){
// Logical ops available in tac file : "&&" "||"
    std::string opName = std::string(op->str());
    if(left != NULL) left->Emit(cg);
    right->Emit(cg);

    if (left != NULL) {// Everything but unary NOT is already defined
	if(opName == "&&"){
	   offsetLoc = cg->GenBinaryOp("&&", left->GetOffsetLoc(cg), right->GetOffsetLoc(cg));
	}
	else if (opName == "||"){
	    offsetLoc = cg->GenBinaryOp("||", left->GetOffsetLoc(cg), right->GetOffsetLoc(cg));
	}
    }
    else{
	// ! true ~> true == false (false) ; ! false ~> false == false (true)
	if(opName == "!"){
	    offsetLoc = cg->GenBinaryOp("==", right->GetOffsetLoc(cg), cg->GenLoadConstant(0));
	}
    }
}

void Call::Emit(CodeGenerator *cg){
    // Steps for call (for non-methods):
    //  * Iterate over params, emit code for them, and push them to the paramstack
    //  * LCall function label, and store result if function returns
    if(base != NULL){
	base->Emit(cg);
	if(dynamic_cast<ArrayType*>(base->GetType()) != NULL){
		offsetLoc = cg->GenLoad(base->GetOffsetLoc(cg), -4);
	}
	if(dynamic_cast<ArrayAccess*>(base) != NULL){
	    ArrayAccess *arr = dynamic_cast<ArrayAccess*>(base);
            offsetLoc = cg->GenLoad(arr->GetOffsetLoc(cg), -4);
        // Do class/array.length() stuff
	}
	return;
    }
    FnDecl* fnDecl = dynamic_cast<FnDecl*>(FindDecl(field));
    Assert(fnDecl != NULL);
    // Deal with parameters
    actuals->EmitAll(cg);
    for(int i = actuals->NumElements()-1; i >= 0; i --){
	cg->GenPushParam(actuals->Nth(i)->GetOffsetLoc(cg));
    }
    std::string fnName = std::string(fnDecl->GetName());
    if(fnName == "main"){
        // Do nothing
    } 
    else if(fnDecl->IsMethodDecl()){
    	// do class stuff (implicit this?)
    }
    else{
        fnName = "_" + fnName;
    }
    offsetLoc = cg->GenLCall(fnName.c_str(), fnDecl->GetType() != Type::voidType);
    cg->GenPopParams(actuals->NumElements() * cg->VarSize);
}

void ReadIntegerExpr::Emit(CodeGenerator *cg){
    offsetLoc = cg->GenBuiltInCall(ReadInteger);    
}

void ReadLineExpr::Emit(CodeGenerator *cg){
    offsetLoc = cg->GenBuiltInCall(ReadLine);
}

void NewArrayExpr::Emit(CodeGenerator *cg){
    // Emit code for size expr
    size->Emit(cg);
    // Steps to generate new array expr:
    //  * Check that size > 0 (Generate size, generate 0, compare size and 0)
    //  * If size > 0, goto label for after if statement
    //  * Inside body of then statement, print error and halt program
    //  * Compute size of array (1 + size * VarSize)
    //  * call alloc with size of array
    //  * Put size into pointer for new space
    //  * point b to array (offset VarSize)

    // Error handling (checks size > 0, prints error if not)
    Location* nought = cg->GenLoadConstant(0);
    Location* lt = cg->GenBinaryOp("<", size->GetOffsetLoc(cg), nought);
    char* afterError = cg->NewLabel();
    cg->GenIfZ(lt, afterError);
    cg->GenBuiltInCall(PrintString, cg->GenLoadConstant(err_arr_bad_size));
    cg->GenBuiltInCall(Halt);
    cg->GenLabel(afterError);

    // Computes size of array and stores it
    Location *eins = cg->GenLoadConstant(1);
    Location *added = cg->GenBinaryOp("+", eins, size->GetOffsetLoc(cg));
    Location *vSize = cg->GenLoadConstant(cg->VarSize);
    Location *multiplied = cg->GenBinaryOp("*", added, vSize);
    Location *memLoc = cg->GenBuiltInCall(Alloc, multiplied);
    // offsetLoc = cg->GenBuiltInCall(Alloc, multiplied);
    cg->GenStore(memLoc, size->GetOffsetLoc(cg), 0);
    offsetLoc = cg->GenBinaryOp("+", memLoc, vSize);
}

void ArrayAccess::Emit(CodeGenerator *cg){
    // Steps for Array Access:
    //  * compare index to 0
    //  * compare index to address of array decremented by varsize (where the length of the array is stored)
    //  * compare result of above with 0
    //  * get result of comparison between index and 0 || comparison of index to decremented address
    //  * If true, goto label for after error
    //  * Generate then body, which contains the error printing and halt() call
    //  * generate aftererror label
    //  * load VarSize
    //  * get result of index * VarSize
    //  * get address of array plus above offset
    //  * Point i to above address
    base->Emit(cg);
    subscript->Emit(cg);
    Location *subLoc = subscript->GetOffsetLoc(cg);

    Location *nought = cg->GenLoadConstant(0);
    Location *lt0 = cg->GenBinaryOp("<", subLoc, nought);
    char* afterError = cg->NewLabel();
    Location *arrOffset = cg->GenLoad(base->GetOffsetLoc(cg), -4);
    Location *ltAddress = cg->GenBinaryOp("<", subLoc, arrOffset);
    Location *eq = cg->GenBinaryOp("==", ltAddress, nought);
    Location *OR = cg->GenBinaryOp("||", lt0,eq);
    cg->GenIfZ(OR, afterError);
    cg->GenBuiltInCall(PrintString, cg->GenLoadConstant(err_arr_out_of_bounds));
    cg->GenBuiltInCall(Halt);
    cg->GenLabel(afterError);
    Location *vSize = cg->GenLoadConstant(cg->VarSize);
    Location *memLoc = cg->GenBinaryOp("*", vSize, subLoc);
    offsetLoc = cg->GenBinaryOp("+", base->GetOffsetLoc(cg), memLoc);
    //cg->GenStore(offsetLoc, subscript->offsetLoc); 
    // Location *loaded = cg->GenLoad(offsetLoc, 0);
}

Location* ArrayAccess::GetOffsetLoc(CodeGenerator *cg){
    return cg->GenLoad(offsetLoc, 0);
}

void NewExpr::Emit(CodeGenerator *cg){
    // Steps to create new object:
    //  * Get size of class (need to compute size of class)
    //  * Allocate space
    //  * Point tempvar to Vtable for class
    //  * store vtable in allocated memory
    ClassDecl* cdecl = dynamic_cast<ClassDecl*>(FindDecl(cType->GetId()));
    Assert(cdecl != NULL);
    Location *classSize = cg->GenLoadConstant(cdecl->GetSize());
    Location *memLoc = cg->GenBuiltInCall(Alloc, classSize);
    Location* vtableLabel = cg->GenLoadLabel(cdecl->GetName());
    cg->GenStore(memLoc, vtableLabel);
    offsetLoc = memLoc;
}

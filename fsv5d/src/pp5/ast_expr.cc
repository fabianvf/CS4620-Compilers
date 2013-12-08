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
	//TODO: Class stuff goes here eventually
    }
    offsetLoc = FindDecl(field)->offsetLoc;
    if(offsetLoc == NULL){
	    printf("FieldAccess broken");
    }
}

void AssignExpr::Emit(CodeGenerator *cg){
    // Generate assignment, by first evaluating the left and right (to get the address)
    // and then by assigning the value in the right location to the left location
    left->Emit(cg);
    right->Emit(cg);
    
    if(dynamic_cast<ArrayAccess*>(left) != NULL){
	cg->GenStore(left->offsetLoc, right->offsetLoc);
	return;
    }
    if((left->offsetLoc != NULL) && (right->offsetLoc != NULL)){
        cg->GenAssign(left->offsetLoc, right->offsetLoc);
    }
}

void ArithmeticExpr::Emit(CodeGenerator *cg){
    if(left != NULL) left->Emit(cg);
    right->Emit(cg);
    if( left != NULL ){ // Binary operators (everything but unary -)
	offsetLoc = cg->GenBinaryOp(op->str(), left->offsetLoc, right->offsetLoc);
    }
    else{
	offsetLoc = cg->GenBinaryOp(op->str(), cg->GenLoadConstant(0), right->offsetLoc);
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
        offsetLoc = cg->GenBinaryOp(op->str(), left->offsetLoc, right->offsetLoc);
    }

    // 2 > 1 is equivalent to 1 < 2
    else if(opName == ">") {
	offsetLoc = cg->GenBinaryOp("<", right->offsetLoc, left->offsetLoc);
    }
    // 1 <= 2 is equivalent to (1 < 2) || (1 == 2), so this is a three step process
    else if (opName == "<=") {
	 Location* lt = cg->GenBinaryOp("<", left->offsetLoc, right->offsetLoc);
	 Location* eq = cg->GenBinaryOp("==", left->offsetLoc, right->offsetLoc);
	 offsetLoc = cg->GenBinaryOp("||", lt, eq);
    }
    // 2 >= 1 ~> 1 <= 2 ~> (1 < 2) || (1 == 2), so this is a three step process as well
    else if (opName == ">="){
        Location* gt = cg->GenBinaryOp("<", right->offsetLoc, left->offsetLoc);
        Location* eq = cg->GenBinaryOp("==", left->offsetLoc, right->offsetLoc);
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
            offsetLoc = cg->GenBuiltInCall(StringEqual, left->offsetLoc, right->offsetLoc);
	}
	else{
	    offsetLoc = cg->GenBinaryOp("==", left->offsetLoc, right->offsetLoc);
	}
    }
    // 1 != 2 is equivalent to (1 == 2) == false (0)
    else if(opName == "!="){
	if(left->GetType() == Type::stringType){
	    Location* eq = cg->GenBuiltInCall(StringEqual, left->offsetLoc, right->offsetLoc);
	    offsetLoc = cg->GenBinaryOp("==", eq, cg->GenLoadConstant(0));
	}
	else{
	    Location* eq = cg->GenBinaryOp("==", left->offsetLoc, right->offsetLoc);
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
	   offsetLoc = cg->GenBinaryOp("&&", left->offsetLoc, right->offsetLoc);
	}
	else if (opName == "||"){
	    offsetLoc = cg->GenBinaryOp("||", left->offsetLoc, right->offsetLoc);
	}
    }
    else{
	// ! true ~> true == false (false) ; ! false ~> false == false (true)
	if(opName == "!"){
	    offsetLoc = cg->GenBinaryOp("==", right->offsetLoc, cg->GenLoadConstant(0));
	}
    }
}

void Call::Emit(CodeGenerator *cg){
    // Steps for call (for non-methods):
    //  * Iterate over params, emit code for them, and push them to the paramstack
    //  * LCall function label, and store result if function returns
    if(base != NULL){
	base->Emit(cg);
	offsetLoc = cg->GenLoad(base->offsetLoc, -4);
        // Do class/array.length() stuff
	 return;
    }
    FnDecl* fnDecl = dynamic_cast<FnDecl*>(FindDecl(field));

    // Deal with parameters
    actuals->EmitAll(cg);
    for(int i = actuals->NumElements()-1; i >= 0; i --){
	cg->GenPushParam(actuals->Nth(i)->offsetLoc);
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
    Location* lt = cg->GenBinaryOp("<", size->offsetLoc, nought);
    char* afterError = cg->NewLabel();
    cg->GenIfZ(lt, afterError);
    cg->GenBuiltInCall(PrintString, cg->GenLoadConstant(err_arr_bad_size));
    cg->GenBuiltInCall(Halt);
    cg->GenLabel(afterError);

    // Computes size of array and stores it
    Location *eins = cg->GenLoadConstant(1);
    Location *added = cg->GenBinaryOp("+", eins, size->offsetLoc);
    Location *vSize = cg->GenLoadConstant(cg->VarSize);
    Location *multiplied = cg->GenBinaryOp("*", added, vSize);
    Location *memLoc = cg->GenBuiltInCall(Alloc, multiplied);
    cg->GenStore(memLoc, size->offsetLoc, 0);
    offsetLoc = cg->GenBinaryOp("+", vSize, memLoc);
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
    Location *subLoc;
    if(dynamic_cast<ArrayAccess*>(subscript) != NULL){
	subLoc = dynamic_cast<ArrayAccess*>(subscript)->GetOffsetLocation(cg);
    }
    else subLoc = subscript->offsetLoc;
    Location *nought = cg->GenLoadConstant(0);
    Location *lt0 = cg->GenBinaryOp("<", subLoc, nought);
    char* afterError = cg->NewLabel();
    Location *arrOffset = cg->GenLoad(base->offsetLoc, -4);
    Location *ltAddress = cg->GenBinaryOp("<", subLoc, arrOffset);
    Location *eq = cg->GenBinaryOp("==", ltAddress, nought);
    Location *OR = cg->GenBinaryOp("||", lt0,eq);
    cg->GenIfZ(OR, afterError);
    cg->GenBuiltInCall(PrintString, cg->GenLoadConstant(err_arr_out_of_bounds));
    cg->GenBuiltInCall(Halt);
    cg->GenLabel(afterError);
    Location *vSize = cg->GenLoadConstant(cg->VarSize);
    Location *memLoc = cg->GenBinaryOp("*", vSize, subscript->offsetLoc);
    offsetLoc = cg->GenBinaryOp("+", base->offsetLoc, memLoc);
    // cg->GenStore(offsetLoc, subscript->offsetLoc); 
}

Location* ArrayAccess::GetOffsetLocation(CodeGenerator *cg){
    return cg->GenLoad(offsetLoc, 0);
}

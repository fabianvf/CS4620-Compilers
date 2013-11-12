/* File: ast_type.cc
 * -----------------
 * Implementation of type node classes.
 */
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h>

 
/* Class constants
 * ---------------
 * These are public constants for the built-in base types (int, double, etc.)
 * They can be accessed with the syntax Type::intType. This allows you to
 * directly access them and share the built-in types where needed rather that
 * creates lots of copies.
 */

Type *Type::intType    = new Type("int");
Type *Type::doubleType = new Type("double");
Type *Type::voidType   = new Type("void");
Type *Type::boolType   = new Type("bool");
Type *Type::nullType   = new Type("null");
Type *Type::stringType = new Type("string");
Type *Type::errorType  = new Type("error"); 

Type::Type(const char *n) {
    Assert(n);
    typeName = strdup(n);
}

void Type::PrintChildren(int indentLevel) {
    printf("%s", typeName);
}

	
NamedType::NamedType(Identifier *i) : Type(*i->GetLocation()) {
    Assert(i != NULL);
    (id=i)->SetParent(this);
} 

void NamedType::PrintChildren(int indentLevel) {
    id->Print(indentLevel+1);
}
bool NamedType::Check2(SymbolTable* SymTab){
//    return true;
    //std:cerr << "Made it to NamedType::Check2():\n";
    if (SymTab->lookup(id->GetName()) == NULL){
        //std:cerr << "I should go here and return false now";
        return false; 
    }
    return true;
}

Identifier* NamedType::GetId(){
//    return NULL;
    return id;
}

ArrayType::ArrayType(yyltype loc, Type *et) : Type(loc) {
    Assert(et != NULL);
    (elemType=et)->SetParent(this);
}

ArrayType::ArrayType(const char *n) : Type(n){
    Assert(n);
    elemType = new Type(strdup(n));
}


Identifier* ArrayType::GetId(){
    return elemType->GetId();
}

char *ArrayType::GetName(){
    return elemType->GetName();
}
bool ArrayType::Check2(SymbolTable *SymTab){
    if((elemType == Type::intType) || (elemType == Type::doubleType) ||(elemType == Type::boolType) || (elemType == Type::stringType)){return true;}
    return (SymTab->lookup(elemType->GetId()->GetName()) != NULL);
}
void ArrayType::PrintChildren(int indentLevel) {
    elemType->Print(indentLevel+1);
}


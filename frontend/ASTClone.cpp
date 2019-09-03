// Copyright (c) 2008 Roberto Raggi <roberto.raggi@gmail.com>
// Copyright (c) 2016 Leandro T. C. Melo <ltcmelo@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


#include "AST.h"
#include "MemoryPool.h"

using namespace psyche;

SimpleSpecifierAST* SimpleSpecifierAST::clone(MemoryPool *pool) const
{
    SimpleSpecifierAST* ast = new (pool) SimpleSpecifierAST;
    ast->specifier_token = specifier_token;
    return ast;
}

AlignmentSpecifierAST* AlignmentSpecifierAST::clone(MemoryPool *pool) const
{
    AlignmentSpecifierAST* ast = new (pool) AlignmentSpecifierAST;
    ast->align_token = align_token;
    ast->lparen_token = lparen_token;
    if (typeIdExprOrAlignmentExpr)
        ast->typeIdExprOrAlignmentExpr = typeIdExprOrAlignmentExpr->clone(pool);
    ast->ellipses_token = ellipses_token;
    ast->rparen_token = rparen_token;
    return ast;
}

GnuAttributeSpecifierAST* GnuAttributeSpecifierAST::clone(MemoryPool *pool) const
{
    GnuAttributeSpecifierAST* ast = new (pool) GnuAttributeSpecifierAST;
    ast->attribute_token = attribute_token;
    ast->first_lparen_token = first_lparen_token;
    ast->second_lparen_token = second_lparen_token;
    for (GnuAttributeListAST* iter = attribute_list, **ast_iter = &ast->attribute_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) GnuAttributeListAST((iter->value) ? iter->value->clone(pool) : 0);
    ast->first_rparen_token = first_rparen_token;
    ast->second_rparen_token = second_rparen_token;
    return ast;
}

GnuAttributeAST* GnuAttributeAST::clone(MemoryPool *pool) const
{
    GnuAttributeAST* ast = new (pool) GnuAttributeAST;
    ast->identifier_token = identifier_token;
    ast->lparen_token = lparen_token;
    ast->tag_token = tag_token;
    for (ExpressionListAST* iter = expression_list, **ast_iter = &ast->expression_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) ExpressionListAST((iter->value) ? iter->value->clone(pool) : 0);
    ast->rparen_token = rparen_token;
    return ast;
}

TypeofSpecifierAST* TypeofSpecifierAST::clone(MemoryPool *pool) const
{
    TypeofSpecifierAST* ast = new (pool) TypeofSpecifierAST;
    ast->typeof_token = typeof_token;
    ast->lparen_token = lparen_token;
    if (expression)
        ast->expression = expression->clone(pool);
    ast->rparen_token = rparen_token;
    return ast;
}

DecltypeSpecifierAST* DecltypeSpecifierAST::clone(MemoryPool *pool) const
{
    DecltypeSpecifierAST* ast = new (pool) DecltypeSpecifierAST;
    ast->decltype_token = decltype_token;
    ast->lparen_token = lparen_token;
    if (expression)
        ast->expression = expression->clone(pool);
    ast->rparen_token = rparen_token;
    return ast;
}

DeclaratorAST* DeclaratorAST::clone(MemoryPool *pool) const
{
    DeclaratorAST* ast = new (pool) DeclaratorAST;
    for (SpecifierListAST* iter = attribute_list, **ast_iter = &ast->attribute_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) SpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    for (PtrOperatorListAST* iter = ptr_operator_list, **ast_iter = &ast->ptr_operator_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) PtrOperatorListAST((iter->value) ? iter->value->clone(pool) : 0);
    if (core_declarator)
        ast->core_declarator = core_declarator->clone(pool);
    for (PostfixDeclaratorListAST* iter = postfix_declarator_list, **ast_iter = &ast->postfix_declarator_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) PostfixDeclaratorListAST((iter->value) ? iter->value->clone(pool) : 0);
    for (SpecifierListAST* iter = post_attribute_list, **ast_iter = &ast->post_attribute_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) SpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    ast->equal_token = equal_token;
    if (initializer)
        ast->initializer = initializer->clone(pool);
    return ast;
}

SimpleDeclarationAST* SimpleDeclarationAST::clone(MemoryPool *pool) const
{
    SimpleDeclarationAST* ast = new (pool) SimpleDeclarationAST;
    for (SpecifierListAST* iter = decl_specifier_list, **ast_iter = &ast->decl_specifier_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) SpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    for (DeclaratorListAST* iter = declarator_list, **ast_iter = &ast->declarator_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) DeclaratorListAST((iter->value) ? iter->value->clone(pool) : 0);
    ast->semicolon_token = semicolon_token;
    return ast;
}

EmptyDeclarationAST* EmptyDeclarationAST::clone(MemoryPool *pool) const
{
    EmptyDeclarationAST* ast = new (pool) EmptyDeclarationAST;
    ast->semicolon_token = semicolon_token;
    return ast;
}

AccessDeclarationAST* AccessDeclarationAST::clone(MemoryPool *pool) const
{
    AccessDeclarationAST* ast = new (pool) AccessDeclarationAST;
    ast->access_specifier_token = access_specifier_token;
    ast->slots_token = slots_token;
    ast->colon_token = colon_token;
    return ast;
}

AsmDefinitionAST* AsmDefinitionAST::clone(MemoryPool *pool) const
{
    AsmDefinitionAST* ast = new (pool) AsmDefinitionAST;
    ast->asm_token = asm_token;
    ast->volatile_token = volatile_token;
    ast->lparen_token = lparen_token;
    ast->rparen_token = rparen_token;
    ast->semicolon_token = semicolon_token;
    return ast;
}

BaseSpecifierAST* BaseSpecifierAST::clone(MemoryPool *pool) const
{
    BaseSpecifierAST* ast = new (pool) BaseSpecifierAST;
    ast->virtual_token = virtual_token;
    ast->access_specifier_token = access_specifier_token;
    if (name)
        ast->name = name->clone(pool);
    ast->ellipsis_token = ellipsis_token;
    return ast;
}

IdExpressionAST* IdExpressionAST::clone(MemoryPool *pool) const
{
    IdExpressionAST* ast = new (pool) IdExpressionAST;
    if (name)
        ast->name = name->clone(pool);
    return ast;
}

CompoundExpressionAST* CompoundExpressionAST::clone(MemoryPool *pool) const
{
    CompoundExpressionAST* ast = new (pool) CompoundExpressionAST;
    ast->lparen_token = lparen_token;
    if (statement)
        ast->statement = statement->clone(pool);
    ast->rparen_token = rparen_token;
    return ast;
}

CompoundLiteralAST* CompoundLiteralAST::clone(MemoryPool *pool) const
{
    CompoundLiteralAST* ast = new (pool) CompoundLiteralAST;
    ast->lparen_token = lparen_token;
    if (type_id)
        ast->type_id = type_id->clone(pool);
    ast->rparen_token = rparen_token;
    if (initializer)
        ast->initializer = initializer->clone(pool);
    return ast;
}

BinaryExpressionAST* BinaryExpressionAST::clone(MemoryPool *pool) const
{
    BinaryExpressionAST* ast = new (pool) BinaryExpressionAST;
    if (left_expression)
        ast->left_expression = left_expression->clone(pool);
    ast->binary_op_token = binary_op_token;
    if (right_expression)
        ast->right_expression = right_expression->clone(pool);
    return ast;
}

CastExpressionAST* CastExpressionAST::clone(MemoryPool *pool) const
{
    CastExpressionAST* ast = new (pool) CastExpressionAST;
    ast->lparen_token = lparen_token;
    if (type_id)
        ast->type_id = type_id->clone(pool);
    ast->rparen_token = rparen_token;
    if (expression)
        ast->expression = expression->clone(pool);
    return ast;
}

ClassSpecifierAST* ClassSpecifierAST::clone(MemoryPool *pool) const
{
    ClassSpecifierAST* ast = new (pool) ClassSpecifierAST;
    ast->classkey_token = classkey_token;
    for (SpecifierListAST* iter = attribute_list, **ast_iter = &ast->attribute_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) SpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    if (name)
        ast->name = name->clone(pool);
    ast->final_token = final_token;
    ast->colon_token = colon_token;
    for (BaseSpecifierListAST* iter = base_clause_list, **ast_iter = &ast->base_clause_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) BaseSpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    ast->dot_dot_dot_token = dot_dot_dot_token;
    ast->lbrace_token = lbrace_token;
    for (DeclarationListAST* iter = member_specifier_list, **ast_iter = &ast->member_specifier_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) DeclarationListAST((iter->value) ? iter->value->clone(pool) : 0);
    ast->rbrace_token = rbrace_token;
    return ast;
}

CaseStatementAST* CaseStatementAST::clone(MemoryPool *pool) const
{
    CaseStatementAST* ast = new (pool) CaseStatementAST;
    ast->case_token = case_token;
    if (expression)
        ast->expression = expression->clone(pool);
    ast->colon_token = colon_token;
    if (statement)
        ast->statement = statement->clone(pool);
    return ast;
}

CompoundStatementAST* CompoundStatementAST::clone(MemoryPool *pool) const
{
    CompoundStatementAST* ast = new (pool) CompoundStatementAST;
    ast->lbrace_token = lbrace_token;
    for (StatementListAST* iter = statement_list, **ast_iter = &ast->statement_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) StatementListAST((iter->value) ? iter->value->clone(pool) : 0);
    ast->rbrace_token = rbrace_token;
    return ast;
}

ConditionAST* ConditionAST::clone(MemoryPool *pool) const
{
    ConditionAST* ast = new (pool) ConditionAST;
    for (SpecifierListAST* iter = type_specifier_list, **ast_iter = &ast->type_specifier_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) SpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    if (declarator)
        ast->declarator = declarator->clone(pool);
    return ast;
}

ConditionalExpressionAST* ConditionalExpressionAST::clone(MemoryPool *pool) const
{
    ConditionalExpressionAST* ast = new (pool) ConditionalExpressionAST;
    if (condition)
        ast->condition = condition->clone(pool);
    ast->question_token = question_token;
    if (left_expression)
        ast->left_expression = left_expression->clone(pool);
    ast->colon_token = colon_token;
    if (right_expression)
        ast->right_expression = right_expression->clone(pool);
    return ast;
}

CppCastExpressionAST* CppCastExpressionAST::clone(MemoryPool *pool) const
{
    CppCastExpressionAST* ast = new (pool) CppCastExpressionAST;
    ast->cast_token = cast_token;
    ast->less_token = less_token;
    if (type_id)
        ast->type_id = type_id->clone(pool);
    ast->greater_token = greater_token;
    ast->lparen_token = lparen_token;
    if (expression)
        ast->expression = expression->clone(pool);
    ast->rparen_token = rparen_token;
    return ast;
}

CtorInitializerAST* CtorInitializerAST::clone(MemoryPool *pool) const
{
    CtorInitializerAST* ast = new (pool) CtorInitializerAST;
    ast->colon_token = colon_token;
    for (MemInitializerListAST* iter = member_initializer_list, **ast_iter = &ast->member_initializer_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) MemInitializerListAST((iter->value) ? iter->value->clone(pool) : 0);
    ast->dot_dot_dot_token = dot_dot_dot_token;
    return ast;
}

DeclarationStatementAST* DeclarationStatementAST::clone(MemoryPool *pool) const
{
    DeclarationStatementAST* ast = new (pool) DeclarationStatementAST;
    if (declaration)
        ast->declaration = declaration->clone(pool);
    return ast;
}

DeclaratorIdAST* DeclaratorIdAST::clone(MemoryPool *pool) const
{
    DeclaratorIdAST* ast = new (pool) DeclaratorIdAST;
    ast->dot_dot_dot_token = dot_dot_dot_token;
    if (name)
        ast->name = name->clone(pool);
    return ast;
}

NestedDeclaratorAST* NestedDeclaratorAST::clone(MemoryPool *pool) const
{
    NestedDeclaratorAST* ast = new (pool) NestedDeclaratorAST;
    ast->lparen_token = lparen_token;
    if (declarator)
        ast->declarator = declarator->clone(pool);
    ast->rparen_token = rparen_token;
    return ast;
}

BitfieldDeclaratorAST* BitfieldDeclaratorAST::clone(MemoryPool *pool) const
{
    BitfieldDeclaratorAST* ast = new (pool) BitfieldDeclaratorAST;
    ast->colon_token = colon_token;
    return ast;
}

FunctionDeclaratorAST* FunctionDeclaratorAST::clone(MemoryPool *pool) const
{
    FunctionDeclaratorAST* ast = new (pool) FunctionDeclaratorAST;
    ast->lparen_token = lparen_token;
    if (parameter_declaration_clause)
        ast->parameter_declaration_clause = parameter_declaration_clause->clone(pool);
    ast->rparen_token = rparen_token;
    for (SpecifierListAST* iter = cv_qualifier_list, **ast_iter = &ast->cv_qualifier_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) SpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    ast->ref_qualifier_token = ref_qualifier_token;
    if (exception_specification)
        ast->exception_specification = exception_specification->clone(pool);
    if (trailing_return_type)
        ast->trailing_return_type = trailing_return_type->clone(pool);
    if (as_cpp_initializer)
        ast->as_cpp_initializer = as_cpp_initializer->clone(pool);
    return ast;
}

ArrayDeclaratorAST* ArrayDeclaratorAST::clone(MemoryPool *pool) const
{
    ArrayDeclaratorAST* ast = new (pool) ArrayDeclaratorAST;
    ast->lbracket_token = lbracket_token;
    if (expression)
        ast->expression = expression->clone(pool);
    ast->rbracket_token = rbracket_token;
    return ast;
}

DeleteExpressionAST* DeleteExpressionAST::clone(MemoryPool *pool) const
{
    DeleteExpressionAST* ast = new (pool) DeleteExpressionAST;
    ast->scope_token = scope_token;
    ast->delete_token = delete_token;
    ast->lbracket_token = lbracket_token;
    ast->rbracket_token = rbracket_token;
    if (expression)
        ast->expression = expression->clone(pool);
    return ast;
}

DoStatementAST* DoStatementAST::clone(MemoryPool *pool) const
{
    DoStatementAST* ast = new (pool) DoStatementAST;
    ast->do_token = do_token;
    if (statement)
        ast->statement = statement->clone(pool);
    ast->while_token = while_token;
    ast->lparen_token = lparen_token;
    if (expression)
        ast->expression = expression->clone(pool);
    ast->rparen_token = rparen_token;
    ast->semicolon_token = semicolon_token;
    return ast;
}

NamedTypeSpecifierAST* NamedTypeSpecifierAST::clone(MemoryPool *pool) const
{
    NamedTypeSpecifierAST* ast = new (pool) NamedTypeSpecifierAST;
    if (name)
        ast->name = name->clone(pool);
    return ast;
}

ElaboratedTypeSpecifierAST* ElaboratedTypeSpecifierAST::clone(MemoryPool *pool) const
{
    ElaboratedTypeSpecifierAST* ast = new (pool) ElaboratedTypeSpecifierAST;
    for (SpecifierListAST* iter = attribute_list, **ast_iter = &ast->attribute_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) SpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    if (name)
        ast->name = name->clone(pool);
    return ast;
}

EnumSpecifierAST* EnumSpecifierAST::clone(MemoryPool *pool) const
{
    EnumSpecifierAST* ast = new (pool) EnumSpecifierAST;
    ast->enum_token = enum_token;
    ast->key_token = key_token;
    if (name)
        ast->name = name->clone(pool);
    ast->colon_token = colon_token;
    for (SpecifierListAST* iter = type_specifier_list, **ast_iter = &ast->type_specifier_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) SpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    ast->lbrace_token = lbrace_token;
    for (EnumeratorListAST* iter = enumerator_list, **ast_iter = &ast->enumerator_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) EnumeratorListAST((iter->value) ? iter->value->clone(pool) : 0);
    ast->stray_comma_token = stray_comma_token;
    ast->rbrace_token = rbrace_token;
    return ast;
}

EnumeratorAST* EnumeratorAST::clone(MemoryPool *pool) const
{
    EnumeratorAST* ast = new (pool) EnumeratorAST;
    ast->identifier_token = identifier_token;
    ast->equal_token = equal_token;
    if (expression)
        ast->expression = expression->clone(pool);
    return ast;
}

ExceptionDeclarationAST* ExceptionDeclarationAST::clone(MemoryPool *pool) const
{
    ExceptionDeclarationAST* ast = new (pool) ExceptionDeclarationAST;
    for (SpecifierListAST* iter = type_specifier_list, **ast_iter = &ast->type_specifier_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) SpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    if (declarator)
        ast->declarator = declarator->clone(pool);
    ast->dot_dot_dot_token = dot_dot_dot_token;
    return ast;
}

DynamicExceptionSpecificationAST* DynamicExceptionSpecificationAST::clone(MemoryPool *pool) const
{
    DynamicExceptionSpecificationAST* ast = new (pool) DynamicExceptionSpecificationAST;
    ast->throw_token = throw_token;
    ast->lparen_token = lparen_token;
    ast->dot_dot_dot_token = dot_dot_dot_token;
    for (ExpressionListAST* iter = type_id_list, **ast_iter = &ast->type_id_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) ExpressionListAST((iter->value) ? iter->value->clone(pool) : 0);
    ast->rparen_token = rparen_token;
    return ast;
}

NoExceptSpecificationAST* NoExceptSpecificationAST::clone(MemoryPool *pool) const
{
    NoExceptSpecificationAST* ast = new (pool) NoExceptSpecificationAST;
    ast->noexcept_token = noexcept_token;
    ast->lparen_token = lparen_token;
    if (expression)
        ast->expression = expression->clone(pool);
    ast->rparen_token = rparen_token;
    return ast;
}

ExpressionOrDeclarationStatementAST* ExpressionOrDeclarationStatementAST::clone(MemoryPool *pool) const
{
    ExpressionOrDeclarationStatementAST* ast = new (pool) ExpressionOrDeclarationStatementAST;
    if (expression)
        ast->expression = expression->clone(pool);
    if (declaration)
        ast->declaration = declaration->clone(pool);
    return ast;
}

ExpressionStatementAST* ExpressionStatementAST::clone(MemoryPool *pool) const
{
    ExpressionStatementAST* ast = new (pool) ExpressionStatementAST;
    if (expression)
        ast->expression = expression->clone(pool);
    ast->semicolon_token = semicolon_token;
    return ast;
}

AmbiguousStatementAST* AmbiguousStatementAST::clone(MemoryPool *pool) const
{
    AmbiguousStatementAST* ast = new (pool) AmbiguousStatementAST;
    if (declarationStmt)
        ast->declarationStmt = declarationStmt->clone(pool);
    if (expressionStmt)
        ast->expressionStmt = expressionStmt->clone(pool);
    return ast;
}

FunctionDefinitionAST* FunctionDefinitionAST::clone(MemoryPool *pool) const
{
    FunctionDefinitionAST* ast = new (pool) FunctionDefinitionAST;
    for (SpecifierListAST* iter = decl_specifier_list, **ast_iter = &ast->decl_specifier_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) SpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    if (declarator)
        ast->declarator = declarator->clone(pool);
    if (ctor_initializer)
        ast->ctor_initializer = ctor_initializer->clone(pool);
    if (function_body)
        ast->function_body = function_body->clone(pool);
    return ast;
}

ForeachStatementAST* ForeachStatementAST::clone(MemoryPool *pool) const
{
    ForeachStatementAST* ast = new (pool) ForeachStatementAST;
    ast->foreach_token = foreach_token;
    ast->lparen_token = lparen_token;
    for (SpecifierListAST* iter = type_specifier_list, **ast_iter = &ast->type_specifier_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) SpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    if (declarator)
        ast->declarator = declarator->clone(pool);
    if (initializer)
        ast->initializer = initializer->clone(pool);
    ast->comma_token = comma_token;
    if (expression)
        ast->expression = expression->clone(pool);
    ast->rparen_token = rparen_token;
    if (statement)
        ast->statement = statement->clone(pool);
    return ast;
}

RangeBasedForStatementAST* RangeBasedForStatementAST::clone(MemoryPool *pool) const
{
    RangeBasedForStatementAST* ast = new (pool) RangeBasedForStatementAST;
    ast->for_token = for_token;
    ast->lparen_token = lparen_token;
    for (SpecifierListAST* iter = type_specifier_list, **ast_iter = &ast->type_specifier_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) SpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    if (declarator)
        ast->declarator = declarator->clone(pool);
    ast->colon_token = colon_token;
    if (expression)
        ast->expression = expression->clone(pool);
    ast->rparen_token = rparen_token;
    if (statement)
        ast->statement = statement->clone(pool);
    return ast;
}

ForStatementAST* ForStatementAST::clone(MemoryPool *pool) const
{
    ForStatementAST* ast = new (pool) ForStatementAST;
    ast->for_token = for_token;
    ast->lparen_token = lparen_token;
    if (initializer)
        ast->initializer = initializer->clone(pool);
    if (condition)
        ast->condition = condition->clone(pool);
    ast->semicolon_token = semicolon_token;
    if (expression)
        ast->expression = expression->clone(pool);
    ast->rparen_token = rparen_token;
    if (statement)
        ast->statement = statement->clone(pool);
    return ast;
}

IfStatementAST* IfStatementAST::clone(MemoryPool *pool) const
{
    IfStatementAST* ast = new (pool) IfStatementAST;
    ast->if_token = if_token;
    ast->lparen_token = lparen_token;
    if (condition)
        ast->condition = condition->clone(pool);
    ast->rparen_token = rparen_token;
    if (statement)
        ast->statement = statement->clone(pool);
    ast->else_token = else_token;
    if (else_statement)
        ast->else_statement = else_statement->clone(pool);
    return ast;
}

ArrayInitializerAST* ArrayInitializerAST::clone(MemoryPool *pool) const
{
    ArrayInitializerAST* ast = new (pool) ArrayInitializerAST;
    ast->lbrace_token = lbrace_token;
    for (ExpressionListAST* iter = expression_list, **ast_iter = &ast->expression_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) ExpressionListAST((iter->value) ? iter->value->clone(pool) : 0);
    ast->rbrace_token = rbrace_token;
    return ast;
}

LabeledStatementAST* LabeledStatementAST::clone(MemoryPool *pool) const
{
    LabeledStatementAST* ast = new (pool) LabeledStatementAST;
    ast->label_token = label_token;
    ast->colon_token = colon_token;
    if (statement)
        ast->statement = statement->clone(pool);
    return ast;
}

LinkageBodyAST* LinkageBodyAST::clone(MemoryPool *pool) const
{
    LinkageBodyAST* ast = new (pool) LinkageBodyAST;
    ast->lbrace_token = lbrace_token;
    for (DeclarationListAST* iter = declaration_list, **ast_iter = &ast->declaration_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) DeclarationListAST((iter->value) ? iter->value->clone(pool) : 0);
    ast->rbrace_token = rbrace_token;
    return ast;
}

LinkageSpecificationAST* LinkageSpecificationAST::clone(MemoryPool *pool) const
{
    LinkageSpecificationAST* ast = new (pool) LinkageSpecificationAST;
    ast->extern_token = extern_token;
    ast->extern_type_token = extern_type_token;
    if (declaration)
        ast->declaration = declaration->clone(pool);
    return ast;
}

MemInitializerAST* MemInitializerAST::clone(MemoryPool *pool) const
{
    MemInitializerAST* ast = new (pool) MemInitializerAST;
    if (name)
        ast->name = name->clone(pool);
    if (expression)
        ast->expression = expression->clone(pool);
    return ast;
}

NestedNameSpecifierAST* NestedNameSpecifierAST::clone(MemoryPool *pool) const
{
    NestedNameSpecifierAST* ast = new (pool) NestedNameSpecifierAST;
    if (class_or_namespace_name)
        ast->class_or_namespace_name = class_or_namespace_name->clone(pool);
    ast->scope_token = scope_token;
    return ast;
}

QualifiedNameAST* QualifiedNameAST::clone(MemoryPool *pool) const
{
    QualifiedNameAST* ast = new (pool) QualifiedNameAST;
    ast->global_scope_token = global_scope_token;
    for (NestedNameSpecifierListAST* iter = nested_name_specifier_list, **ast_iter = &ast->nested_name_specifier_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) NestedNameSpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    if (unqualified_name)
        ast->unqualified_name = unqualified_name->clone(pool);
    return ast;
}

QuantifiedTypeSpecifierAST* QuantifiedTypeSpecifierAST::clone(MemoryPool *pool) const
{
    QuantifiedTypeSpecifierAST* ast = new (pool) QuantifiedTypeSpecifierAST;
    ast->quantifier_token = quantifier_token;
    ast->lparen_token = lparen_token;
    if (name)
        ast->name = name->clone(pool);
    ast->rparen_token = rparen_token;
    return ast;
}

TaggedNameAST* TaggedNameAST::clone(MemoryPool *pool) const
{
    TaggedNameAST* ast = new (pool) TaggedNameAST;
    ast->tag_token = tag_token;
    if (core_name)
        ast->core_name = core_name->clone(pool);
    return ast;
}

OperatorFunctionIdAST* OperatorFunctionIdAST::clone(MemoryPool *pool) const
{
    OperatorFunctionIdAST* ast = new (pool) OperatorFunctionIdAST;
    ast->operator_token = operator_token;
    if (op)
        ast->op = op->clone(pool);
    return ast;
}

ConversionFunctionIdAST* ConversionFunctionIdAST::clone(MemoryPool *pool) const
{
    ConversionFunctionIdAST* ast = new (pool) ConversionFunctionIdAST;
    ast->operator_token = operator_token;
    for (SpecifierListAST* iter = type_specifier_list, **ast_iter = &ast->type_specifier_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) SpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    for (PtrOperatorListAST* iter = ptr_operator_list, **ast_iter = &ast->ptr_operator_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) PtrOperatorListAST((iter->value) ? iter->value->clone(pool) : 0);
    return ast;
}

EmptyNameAST* EmptyNameAST::clone(MemoryPool *pool) const
{
    EmptyNameAST* ast = new (pool) EmptyNameAST;
    return ast;
}

SimpleNameAST* SimpleNameAST::clone(MemoryPool *pool) const
{
    SimpleNameAST* ast = new (pool) SimpleNameAST;
    ast->identifier_token = identifier_token;
    return ast;
}

DestructorNameAST* DestructorNameAST::clone(MemoryPool *pool) const
{
    DestructorNameAST* ast = new (pool) DestructorNameAST;
    ast->tilde_token = tilde_token;
    if (unqualified_name)
        ast->unqualified_name = unqualified_name->clone(pool);
    return ast;
}

TemplateIdAST* TemplateIdAST::clone(MemoryPool *pool) const
{
    TemplateIdAST* ast = new (pool) TemplateIdAST;
    ast->template_token = template_token;
    ast->identifier_token = identifier_token;
    ast->less_token = less_token;
    for (ExpressionListAST* iter = template_argument_list, **ast_iter = &ast->template_argument_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) ExpressionListAST((iter->value) ? iter->value->clone(pool) : 0);
    ast->greater_token = greater_token;
    return ast;
}

NamespaceAST* NamespaceAST::clone(MemoryPool *pool) const
{
    NamespaceAST* ast = new (pool) NamespaceAST;
    ast->inline_token = inline_token;
    ast->namespace_token = namespace_token;
    ast->identifier_token = identifier_token;
    for (SpecifierListAST* iter = attribute_list, **ast_iter = &ast->attribute_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) SpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    if (linkage_body)
        ast->linkage_body = linkage_body->clone(pool);
    return ast;
}

NamespaceAliasDefinitionAST* NamespaceAliasDefinitionAST::clone(MemoryPool *pool) const
{
    NamespaceAliasDefinitionAST* ast = new (pool) NamespaceAliasDefinitionAST;
    ast->namespace_token = namespace_token;
    ast->namespace_name_token = namespace_name_token;
    ast->equal_token = equal_token;
    if (name)
        ast->name = name->clone(pool);
    ast->semicolon_token = semicolon_token;
    return ast;
}

AliasDeclarationAST* AliasDeclarationAST::clone(MemoryPool *pool) const
{
    AliasDeclarationAST* ast = new (pool) AliasDeclarationAST;
    ast->using_token = using_token;
    if (name)
        ast->name = name->clone(pool);
    ast->equal_token = equal_token;
    if (typeId)
        ast->typeId = typeId->clone(pool);
    ast->semicolon_token = semicolon_token;
    return ast;
}

ExpressionListParenAST* ExpressionListParenAST::clone(MemoryPool *pool) const
{
    ExpressionListParenAST* ast = new (pool) ExpressionListParenAST;
    ast->lparen_token = lparen_token;
    for (ExpressionListAST* iter = expression_list, **ast_iter = &ast->expression_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) ExpressionListAST((iter->value) ? iter->value->clone(pool) : 0);
    ast->rparen_token = rparen_token;
    return ast;
}

NewArrayDeclaratorAST* NewArrayDeclaratorAST::clone(MemoryPool *pool) const
{
    NewArrayDeclaratorAST* ast = new (pool) NewArrayDeclaratorAST;
    ast->lbracket_token = lbracket_token;
    if (expression)
        ast->expression = expression->clone(pool);
    ast->rbracket_token = rbracket_token;
    return ast;
}

NewExpressionAST* NewExpressionAST::clone(MemoryPool *pool) const
{
    NewExpressionAST* ast = new (pool) NewExpressionAST;
    ast->scope_token = scope_token;
    ast->new_token = new_token;
    if (new_placement)
        ast->new_placement = new_placement->clone(pool);
    ast->lparen_token = lparen_token;
    if (type_id)
        ast->type_id = type_id->clone(pool);
    ast->rparen_token = rparen_token;
    if (new_type_id)
        ast->new_type_id = new_type_id->clone(pool);
    if (new_initializer)
        ast->new_initializer = new_initializer->clone(pool);
    return ast;
}

NewTypeIdAST* NewTypeIdAST::clone(MemoryPool *pool) const
{
    NewTypeIdAST* ast = new (pool) NewTypeIdAST;
    for (SpecifierListAST* iter = type_specifier_list, **ast_iter = &ast->type_specifier_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) SpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    for (PtrOperatorListAST* iter = ptr_operator_list, **ast_iter = &ast->ptr_operator_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) PtrOperatorListAST((iter->value) ? iter->value->clone(pool) : 0);
    for (NewArrayDeclaratorListAST* iter = new_array_declarator_list, **ast_iter = &ast->new_array_declarator_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) NewArrayDeclaratorListAST((iter->value) ? iter->value->clone(pool) : 0);
    return ast;
}

OperatorAST* OperatorAST::clone(MemoryPool *pool) const
{
    OperatorAST* ast = new (pool) OperatorAST;
    ast->op_token = op_token;
    ast->open_token = open_token;
    ast->close_token = close_token;
    return ast;
}

ParameterDeclarationAST* ParameterDeclarationAST::clone(MemoryPool *pool) const
{
    ParameterDeclarationAST* ast = new (pool) ParameterDeclarationAST;
    for (SpecifierListAST* iter = type_specifier_list, **ast_iter = &ast->type_specifier_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) SpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    if (declarator)
        ast->declarator = declarator->clone(pool);
    ast->equal_token = equal_token;
    if (expression)
        ast->expression = expression->clone(pool);
    return ast;
}

ParameterDeclarationClauseAST* ParameterDeclarationClauseAST::clone(MemoryPool *pool) const
{
    ParameterDeclarationClauseAST* ast = new (pool) ParameterDeclarationClauseAST;
    for (ParameterDeclarationListAST* iter = parameter_declaration_list, **ast_iter = &ast->parameter_declaration_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) ParameterDeclarationListAST((iter->value) ? iter->value->clone(pool) : 0);
    ast->dot_dot_dot_token = dot_dot_dot_token;
    return ast;
}

CallAST* CallAST::clone(MemoryPool *pool) const
{
    CallAST* ast = new (pool) CallAST;
    if (base_expression)
        ast->base_expression = base_expression->clone(pool);
    ast->lparen_token = lparen_token;
    for (ExpressionListAST* iter = expression_list, **ast_iter = &ast->expression_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) ExpressionListAST((iter->value) ? iter->value->clone(pool) : 0);
    ast->rparen_token = rparen_token;
    return ast;
}

ArrayAccessAST* ArrayAccessAST::clone(MemoryPool *pool) const
{
    ArrayAccessAST* ast = new (pool) ArrayAccessAST;
    if (base_expression)
        ast->base_expression = base_expression->clone(pool);
    ast->lbracket_token = lbracket_token;
    if (expression)
        ast->expression = expression->clone(pool);
    ast->rbracket_token = rbracket_token;
    return ast;
}

PostIncrDecrAST* PostIncrDecrAST::clone(MemoryPool *pool) const
{
    PostIncrDecrAST* ast = new (pool) PostIncrDecrAST;
    if (base_expression)
        ast->base_expression = base_expression->clone(pool);
    ast->incr_decr_token = incr_decr_token;
    return ast;
}

MemberAccessAST* MemberAccessAST::clone(MemoryPool *pool) const
{
    MemberAccessAST* ast = new (pool) MemberAccessAST;
    if (base_expression)
        ast->base_expression = base_expression->clone(pool);
    ast->access_token = access_token;
    ast->template_token = template_token;
    if (member_name)
        ast->member_name = member_name->clone(pool);
    return ast;
}

TypeidExpressionAST* TypeidExpressionAST::clone(MemoryPool *pool) const
{
    TypeidExpressionAST* ast = new (pool) TypeidExpressionAST;
    ast->typeid_token = typeid_token;
    ast->lparen_token = lparen_token;
    if (expression)
        ast->expression = expression->clone(pool);
    ast->rparen_token = rparen_token;
    return ast;
}

TypenameCallExpressionAST* TypenameCallExpressionAST::clone(MemoryPool *pool) const
{
    TypenameCallExpressionAST* ast = new (pool) TypenameCallExpressionAST;
    ast->typename_token = typename_token;
    if (name)
        ast->name = name->clone(pool);
    if (expression)
        ast->expression = expression->clone(pool);
    return ast;
}

TypeConstructorCallAST* TypeConstructorCallAST::clone(MemoryPool *pool) const
{
    TypeConstructorCallAST* ast = new (pool) TypeConstructorCallAST;
    for (SpecifierListAST* iter = type_specifier_list, **ast_iter = &ast->type_specifier_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) SpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    if (expression)
        ast->expression = expression->clone(pool);
    return ast;
}

PointerToMemberAST* PointerToMemberAST::clone(MemoryPool *pool) const
{
    PointerToMemberAST* ast = new (pool) PointerToMemberAST;
    ast->global_scope_token = global_scope_token;
    for (NestedNameSpecifierListAST* iter = nested_name_specifier_list, **ast_iter = &ast->nested_name_specifier_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) NestedNameSpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    ast->star_token = star_token;
    for (SpecifierListAST* iter = cv_qualifier_list, **ast_iter = &ast->cv_qualifier_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) SpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    ast->ref_qualifier_token = ref_qualifier_token;
    return ast;
}

PointerAST* PointerAST::clone(MemoryPool *pool) const
{
    PointerAST* ast = new (pool) PointerAST;
    ast->star_token = star_token;
    for (SpecifierListAST* iter = cv_qualifier_list, **ast_iter = &ast->cv_qualifier_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) SpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    return ast;
}

ReferenceAST* ReferenceAST::clone(MemoryPool *pool) const
{
    ReferenceAST* ast = new (pool) ReferenceAST;
    ast->reference_token = reference_token;
    return ast;
}

BreakStatementAST* BreakStatementAST::clone(MemoryPool *pool) const
{
    BreakStatementAST* ast = new (pool) BreakStatementAST;
    ast->break_token = break_token;
    ast->semicolon_token = semicolon_token;
    return ast;
}

ContinueStatementAST* ContinueStatementAST::clone(MemoryPool *pool) const
{
    ContinueStatementAST* ast = new (pool) ContinueStatementAST;
    ast->continue_token = continue_token;
    ast->semicolon_token = semicolon_token;
    return ast;
}

GotoStatementAST* GotoStatementAST::clone(MemoryPool *pool) const
{
    GotoStatementAST* ast = new (pool) GotoStatementAST;
    ast->goto_token = goto_token;
    ast->identifier_token = identifier_token;
    ast->semicolon_token = semicolon_token;
    return ast;
}

ReturnStatementAST* ReturnStatementAST::clone(MemoryPool *pool) const
{
    ReturnStatementAST* ast = new (pool) ReturnStatementAST;
    ast->return_token = return_token;
    if (expression)
        ast->expression = expression->clone(pool);
    ast->semicolon_token = semicolon_token;
    return ast;
}

SizeofExpressionAST* SizeofExpressionAST::clone(MemoryPool *pool) const
{
    SizeofExpressionAST* ast = new (pool) SizeofExpressionAST;
    ast->sizeof_token = sizeof_token;
    ast->dot_dot_dot_token = dot_dot_dot_token;
    ast->lparen_token = lparen_token;
    if (expression)
        ast->expression = expression->clone(pool);
    ast->rparen_token = rparen_token;
    return ast;
}

AlignofExpressionAST* AlignofExpressionAST::clone(MemoryPool *pool) const
{
    AlignofExpressionAST* ast = new (pool) AlignofExpressionAST;
    ast->alignof_token = alignof_token;
    ast->lparen_token = lparen_token;
    if (typeId)
        ast->typeId = typeId->clone(pool);
    ast->rparen_token = rparen_token;
    return ast;
}

PointerLiteralAST* PointerLiteralAST::clone(MemoryPool *pool) const
{
    PointerLiteralAST* ast = new (pool) PointerLiteralAST;
    ast->literal_token = literal_token;
    return ast;
}

NumericLiteralAST* NumericLiteralAST::clone(MemoryPool *pool) const
{
    NumericLiteralAST* ast = new (pool) NumericLiteralAST;
    ast->literal_token = literal_token;
    return ast;
}

BoolLiteralAST* BoolLiteralAST::clone(MemoryPool *pool) const
{
    BoolLiteralAST* ast = new (pool) BoolLiteralAST;
    ast->literal_token = literal_token;
    return ast;
}

ThisExpressionAST* ThisExpressionAST::clone(MemoryPool *pool) const
{
    ThisExpressionAST* ast = new (pool) ThisExpressionAST;
    ast->this_token = this_token;
    return ast;
}

NestedExpressionAST* NestedExpressionAST::clone(MemoryPool *pool) const
{
    NestedExpressionAST* ast = new (pool) NestedExpressionAST;
    ast->lparen_token = lparen_token;
    if (expression)
        ast->expression = expression->clone(pool);
    ast->rparen_token = rparen_token;
    return ast;
}

StaticAssertDeclarationAST* StaticAssertDeclarationAST::clone(MemoryPool *pool) const
{
    StaticAssertDeclarationAST* ast = new (pool) StaticAssertDeclarationAST;
    ast->static_assert_token = static_assert_token;
    ast->lparen_token = lparen_token;
    if (expression)
        ast->expression = expression->clone(pool);
    ast->comma_token = comma_token;
    if (string_literal)
        ast->string_literal = string_literal->clone(pool);
    ast->rparen_token = rparen_token;
    ast->semicolon_token = semicolon_token;
    return ast;
}

StringLiteralAST* StringLiteralAST::clone(MemoryPool *pool) const
{
    StringLiteralAST* ast = new (pool) StringLiteralAST;
    ast->literal_token = literal_token;
    if (next)
        ast->next = next->clone(pool);
    return ast;
}

SwitchStatementAST* SwitchStatementAST::clone(MemoryPool *pool) const
{
    SwitchStatementAST* ast = new (pool) SwitchStatementAST;
    ast->switch_token = switch_token;
    ast->lparen_token = lparen_token;
    if (condition)
        ast->condition = condition->clone(pool);
    ast->rparen_token = rparen_token;
    if (statement)
        ast->statement = statement->clone(pool);
    return ast;
}

GenericsDeclarationAST* GenericsDeclarationAST::clone(MemoryPool *pool) const
{
    GenericsDeclarationAST* ast = new (pool) GenericsDeclarationAST;
    ast->generics_token = generics_token;
    if (declaration)
        ast->declaration = declaration->clone(pool);
    return ast;
}

TemplateDeclarationAST* TemplateDeclarationAST::clone(MemoryPool *pool) const
{
    TemplateDeclarationAST* ast = new (pool) TemplateDeclarationAST;
    ast->export_token = export_token;
    ast->template_token = template_token;
    ast->less_token = less_token;
    for (DeclarationListAST* iter = template_parameter_list, **ast_iter = &ast->template_parameter_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) DeclarationListAST((iter->value) ? iter->value->clone(pool) : 0);
    ast->greater_token = greater_token;
    if (declaration)
        ast->declaration = declaration->clone(pool);
    return ast;
}

ThrowExpressionAST* ThrowExpressionAST::clone(MemoryPool *pool) const
{
    ThrowExpressionAST* ast = new (pool) ThrowExpressionAST;
    ast->throw_token = throw_token;
    if (expression)
        ast->expression = expression->clone(pool);
    return ast;
}

NoExceptOperatorExpressionAST* NoExceptOperatorExpressionAST::clone(MemoryPool *pool) const
{
    NoExceptOperatorExpressionAST* ast = new (pool) NoExceptOperatorExpressionAST;
    ast->noexcept_token = noexcept_token;
    if (expression)
        ast->expression = expression->clone(pool);
    return ast;
}

TranslationUnitAST* TranslationUnitAST::clone(MemoryPool *pool) const
{
    TranslationUnitAST* ast = new (pool) TranslationUnitAST;
    for (DeclarationListAST* iter = declaration_list, **ast_iter = &ast->declaration_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) DeclarationListAST((iter->value) ? iter->value->clone(pool) : 0);
    return ast;
}

TryBlockStatementAST* TryBlockStatementAST::clone(MemoryPool *pool) const
{
    TryBlockStatementAST* ast = new (pool) TryBlockStatementAST;
    ast->try_token = try_token;
    if (statement)
        ast->statement = statement->clone(pool);
    for (CatchClauseListAST* iter = catch_clause_list, **ast_iter = &ast->catch_clause_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) CatchClauseListAST((iter->value) ? iter->value->clone(pool) : 0);
    return ast;
}

CatchClauseAST* CatchClauseAST::clone(MemoryPool *pool) const
{
    CatchClauseAST* ast = new (pool) CatchClauseAST;
    ast->catch_token = catch_token;
    ast->lparen_token = lparen_token;
    if (exception_declaration)
        ast->exception_declaration = exception_declaration->clone(pool);
    ast->rparen_token = rparen_token;
    if (statement)
        ast->statement = statement->clone(pool);
    return ast;
}

TypeIdAST* TypeIdAST::clone(MemoryPool *pool) const
{
    TypeIdAST* ast = new (pool) TypeIdAST;
    for (SpecifierListAST* iter = type_specifier_list, **ast_iter = &ast->type_specifier_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) SpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    if (declarator)
        ast->declarator = declarator->clone(pool);
    return ast;
}

TypenameTypeParameterAST* TypenameTypeParameterAST::clone(MemoryPool *pool) const
{
    TypenameTypeParameterAST* ast = new (pool) TypenameTypeParameterAST;
    ast->classkey_token = classkey_token;
    ast->dot_dot_dot_token = dot_dot_dot_token;
    if (name)
        ast->name = name->clone(pool);
    ast->equal_token = equal_token;
    if (type_id)
        ast->type_id = type_id->clone(pool);
    return ast;
}

TemplateTypeParameterAST* TemplateTypeParameterAST::clone(MemoryPool *pool) const
{
    TemplateTypeParameterAST* ast = new (pool) TemplateTypeParameterAST;
    ast->template_token = template_token;
    ast->less_token = less_token;
    for (DeclarationListAST* iter = template_parameter_list, **ast_iter = &ast->template_parameter_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) DeclarationListAST((iter->value) ? iter->value->clone(pool) : 0);
    ast->greater_token = greater_token;
    ast->class_token = class_token;
    ast->dot_dot_dot_token = dot_dot_dot_token;
    if (name)
        ast->name = name->clone(pool);
    ast->equal_token = equal_token;
    if (type_id)
        ast->type_id = type_id->clone(pool);
    return ast;
}

UnaryExpressionAST* UnaryExpressionAST::clone(MemoryPool *pool) const
{
    UnaryExpressionAST* ast = new (pool) UnaryExpressionAST;
    ast->unary_op_token = unary_op_token;
    if (expression)
        ast->expression = expression->clone(pool);
    return ast;
}

UsingAST* UsingAST::clone(MemoryPool *pool) const
{
    UsingAST* ast = new (pool) UsingAST;
    ast->using_token = using_token;
    ast->typename_token = typename_token;
    if (name)
        ast->name = name->clone(pool);
    ast->semicolon_token = semicolon_token;
    return ast;
}

UsingDirectiveAST* UsingDirectiveAST::clone(MemoryPool *pool) const
{
    UsingDirectiveAST* ast = new (pool) UsingDirectiveAST;
    ast->using_token = using_token;
    ast->namespace_token = namespace_token;
    if (name)
        ast->name = name->clone(pool);
    ast->semicolon_token = semicolon_token;
    return ast;
}

WhileStatementAST* WhileStatementAST::clone(MemoryPool *pool) const
{
    WhileStatementAST* ast = new (pool) WhileStatementAST;
    ast->while_token = while_token;
    ast->lparen_token = lparen_token;
    if (condition)
        ast->condition = condition->clone(pool);
    ast->rparen_token = rparen_token;
    if (statement)
        ast->statement = statement->clone(pool);
    return ast;
}

LambdaExpressionAST* LambdaExpressionAST::clone(MemoryPool *pool) const
{
    LambdaExpressionAST* ast = new (pool) LambdaExpressionAST;
    if (lambda_introducer)
        ast->lambda_introducer = lambda_introducer->clone(pool);
    if (lambda_declarator)
        ast->lambda_declarator = lambda_declarator->clone(pool);
    if (statement)
        ast->statement = statement->clone(pool);
    return ast;
}

LambdaIntroducerAST* LambdaIntroducerAST::clone(MemoryPool *pool) const
{
    LambdaIntroducerAST* ast = new (pool) LambdaIntroducerAST;
    ast->lbracket_token = lbracket_token;
    if (lambda_capture)
        ast->lambda_capture = lambda_capture->clone(pool);
    ast->rbracket_token = rbracket_token;
    return ast;
}

LambdaCaptureAST* LambdaCaptureAST::clone(MemoryPool *pool) const
{
    LambdaCaptureAST* ast = new (pool) LambdaCaptureAST;
    ast->default_capture_token = default_capture_token;
    for (CaptureListAST* iter = capture_list, **ast_iter = &ast->capture_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) CaptureListAST((iter->value) ? iter->value->clone(pool) : 0);
    return ast;
}

CaptureAST* CaptureAST::clone(MemoryPool *pool) const
{
    CaptureAST* ast = new (pool) CaptureAST;
    ast->amper_token = amper_token;
    if (identifier)
        ast->identifier = identifier->clone(pool);
    return ast;
}

LambdaDeclaratorAST* LambdaDeclaratorAST::clone(MemoryPool *pool) const
{
    LambdaDeclaratorAST* ast = new (pool) LambdaDeclaratorAST;
    ast->lparen_token = lparen_token;
    if (parameter_declaration_clause)
        ast->parameter_declaration_clause = parameter_declaration_clause->clone(pool);
    ast->rparen_token = rparen_token;
    for (SpecifierListAST* iter = attributes, **ast_iter = &ast->attributes;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) SpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    ast->mutable_token = mutable_token;
    if (exception_specification)
        ast->exception_specification = exception_specification->clone(pool);
    if (trailing_return_type)
        ast->trailing_return_type = trailing_return_type->clone(pool);
    return ast;
}

TrailingReturnTypeAST* TrailingReturnTypeAST::clone(MemoryPool *pool) const
{
    TrailingReturnTypeAST* ast = new (pool) TrailingReturnTypeAST;
    ast->arrow_token = arrow_token;
    for (SpecifierListAST* iter = attributes, **ast_iter = &ast->attributes;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) SpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    for (SpecifierListAST* iter = type_specifier_list, **ast_iter = &ast->type_specifier_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) SpecifierListAST((iter->value) ? iter->value->clone(pool) : 0);
    if (declarator)
        ast->declarator = declarator->clone(pool);
    return ast;
}

BracedInitializerAST* BracedInitializerAST::clone(MemoryPool *pool) const
{
    BracedInitializerAST* ast = new (pool) BracedInitializerAST;
    ast->lbrace_token = lbrace_token;
    for (ExpressionListAST* iter = expression_list, **ast_iter = &ast->expression_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) ExpressionListAST((iter->value) ? iter->value->clone(pool) : 0);
    ast->comma_token = comma_token;
    ast->rbrace_token = rbrace_token;
    return ast;
}

DotDesignatorAST* DotDesignatorAST::clone(MemoryPool *pool) const
{
    DotDesignatorAST* ast = new (pool) DotDesignatorAST;
    ast->dot_token = dot_token;
    ast->identifier_token = identifier_token;
    return ast;
}

BracketDesignatorAST* BracketDesignatorAST::clone(MemoryPool *pool) const
{
    BracketDesignatorAST* ast = new (pool) BracketDesignatorAST;
    ast->lbracket_token = lbracket_token;
    if (expression)
        ast->expression = expression->clone(pool);
    ast->rbracket_token = rbracket_token;
    return ast;
}

DesignatedInitializerAST* DesignatedInitializerAST::clone(MemoryPool *pool) const
{
    DesignatedInitializerAST* ast = new (pool) DesignatedInitializerAST;
    for (DesignatorListAST* iter = designator_list, **ast_iter = &ast->designator_list;
         iter; iter = iter->next, ast_iter = &(*ast_iter)->next)
        *ast_iter = new (pool) DesignatorListAST((iter->value) ? iter->value->clone(pool) : 0);
    ast->equal_token = equal_token;
    if (initializer)
        ast->initializer = initializer->clone(pool);
    return ast;
}


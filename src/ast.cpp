#include "ast.hpp"
#include <iostream>

IntLiteral::IntLiteral(int v) : val(v) {
    type = ASTNodeType::IntLit;
}

RetStmt::RetStmt(IntLiteral* e) : expr(e) {
    type = ASTNodeType::RetStmt;
}

RetStmt::~RetStmt() { delete expr; }

BinaryExpr::BinaryExpr(BinOp o, ASTNode* l, ASTNode* r)
    : op(o), left(l), right(r)
{
    type = ASTNodeType::BinaryExpr;
}

BinaryExpr::~BinaryExpr() {
    delete left;
    delete right;
}

VarRef::VarRef(std::string n) : name(std::move(n)) {
    type = ASTNodeType::VarRef;
}

AssignStmt::AssignStmt(std::string n, ASTNode* v)
    : name(std::move(n)), value(v)
{
    type = ASTNodeType::AssignStmt;
}

AssignStmt::~AssignStmt() { delete value; }

void display_ast(const ASTNode* node, int indent) {
    if (!node) return;
    std::string pad(indent, ' ');

    switch (node->type) {
        case ASTNodeType::IntLit: {
            const IntLiteral* n = static_cast<const IntLiteral*>(node);
            std::cout << pad << "IntLiteral(" << n->val << ")\n";
            break;
        }
        case ASTNodeType::RetStmt: {
            const RetStmt* n = static_cast<const RetStmt*>(node);
            std::cout << pad << "RetStmt\n";
            display_ast(n->expr, indent + 2);
            break;
        }
        default:
            std::cout << pad << "Unknown node\n";
            break;
    }
}

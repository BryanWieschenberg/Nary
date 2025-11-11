#pragma once
#include <memory>
#include <string>

enum class ASTNodeType {
    RetStmt,
    IntLit
};

struct ASTNode {
    ASTNodeType type;
    virtual ~ASTNode() = default;
};

struct IntLiteral : public ASTNode {
    int val;
    IntLiteral(int v) : val(v) {
        type = ASTNodeType::IntLit;
    }
};

struct RetStmt : public ASTNode {
    IntLiteral* expr;
    RetStmt(IntLiteral* e) : expr(e) {
        type = ASTNodeType::RetStmt;
    }

    ~RetStmt() {
        delete expr;
    }
};

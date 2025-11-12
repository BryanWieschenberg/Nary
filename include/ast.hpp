#pragma once
#include <string>

enum class ASTNodeType {
    RetStmt,
    IntLit,
    BinaryExpr,
    VarRef,
    AssignStmt
};

enum class BinOp { Add, Sub, Mul, Div };

struct ASTNode {
    ASTNodeType type;
    virtual ~ASTNode() = default;
};

struct IntLiteral : public ASTNode {
    int val;
    explicit IntLiteral(int v);
};

struct RetStmt : public ASTNode {
    IntLiteral* expr;
    explicit RetStmt(IntLiteral* e);
    ~RetStmt();
};

struct BinaryExpr : public ASTNode {
    BinOp op;
    ASTNode* left;
    ASTNode* right;
    BinaryExpr(BinOp o, ASTNode* l, ASTNode* r);
    ~BinaryExpr();
};

struct VarRef : public ASTNode {
    std::string name;
    explicit VarRef(std::string n);
};

struct AssignStmt : public ASTNode {
    std::string name;
    ASTNode* value;
    AssignStmt(std::string n, ASTNode* v);
    ~AssignStmt();
};

void display_ast(const ASTNode* node, int indent = 0);

#pragma once
#include <iostream>
#include <fstream>
#include "ast.hpp"

class Generator {
public:
    Generator(std::ostream& out);
    void generate(const ASTNode* node);

private:
    std::ostream& out;
    void gen_ret(const RetStmt* node);
    void gen_intlit(const IntLiteral* node);
};

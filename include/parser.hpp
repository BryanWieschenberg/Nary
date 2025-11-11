#pragma once
#include <vector>
#include "lexer.hpp"
#include "ast.hpp"

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    ASTNode* parse();

private:
    const std::vector<Token>& tokens;
    size_t pos;

    const Token& peek() const;
    const Token& consume();
    bool expect(TokenType type);
};

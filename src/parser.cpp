#include <iostream>
#include <memory>
#include "parser.hpp"

Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens), pos(0) {}

const Token& Parser::peek() const {
    return tokens[pos];
}

const Token& Parser::consume() {
    if (pos >= tokens.size()) return tokens.back();
    return tokens[pos++];
}

bool Parser::expect(TokenType type) {
    if (peek().type == type) return true;
    std::cerr << "Parse error: expected " << to_str(type)
              << " at " << peek().line << ":" << peek().col << "\n";
    return false;
}

ASTNode* Parser::parse() {
    if (!expect(TokenType::Ret)) return nullptr;
    consume();
    if (!expect(TokenType::IntLit)) return nullptr;

    int value = std::stoi(std::string(consume().lexeme));
    IntLiteral* intNode = new IntLiteral(value);

    if (!expect(TokenType::Semi)) return nullptr;
    consume();
    if (!expect(TokenType::End)) return nullptr;

    return new RetStmt(intNode);
}

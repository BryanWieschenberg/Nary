#pragma once
#include <string>
#include <vector>
#include <string_view>

enum class TokenType {
    Ret,
    IntLit,
    Semi,
    End,
    Invalid
};

struct Token {
    TokenType type;
    std::string_view lexeme;
    size_t line;
    size_t col;
};

std::string to_str(TokenType type);
void display_tokens(const std::vector<Token>& tokens, bool verbose = false);

class Lexer {
public:
    Lexer(std::string_view src);
    std::vector<Token> tokenize();

private:
    std::string_view src;
    size_t pos;
    size_t line;
    size_t col;

    char peek() const;
    char consume();
    void skip_whitespace();
    Token next_token();
};

#include <cctype>
#include <sstream>
#include "lexer.hpp"

Lexer::Lexer(std::string_view src)
    : src(src), pos(0), line(1), col(1) {}

char Lexer::peek() const {
    return pos < src.size() ? src[pos] : '\0';
}

char Lexer::consume() {
    if (pos >= src.size()) return '\0';
    char c = src[pos++];
    if (c == '\n') { line++; col = 1; }
    else col++;
    return c;
}

void Lexer::skip_whitespace() {
    while (std::isspace(static_cast<unsigned char>(peek()))) consume();
}

Token Lexer::next_token() {
    skip_whitespace();
    size_t start_pos = pos;
    size_t start_col = col;

    if (pos >= src.size())
        return {TokenType::End, "", line, start_col};
    
    char c = peek();

    if (std::isalpha(c)) {
        std::string word;
        while (std::isalpha(peek())) word += consume();
        if (word == "return")
            return {TokenType::Ret, std::string_view(src).substr(start_pos, word.size()), line, start_col};
        return {TokenType::Invalid, std::string_view(src).substr(start_pos, word.size()), line, start_col};
    }

    if (std::isdigit(c)) {
        size_t len = 0;
        while (std::isdigit(peek())) { consume(); len++; }
        return {TokenType::IntLit, std::string_view(src).substr(start_pos, len), line, start_col};
    }

    if (c == ';') {
        consume();
        return {TokenType::Semi, ";", line, start_col};
    }

    consume();
    return {TokenType::Invalid, std::string_view(src).substr(start_pos, 1), line, start_col};
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (1) {
        Token t = next_token();
        tokens.push_back(t);
        if (t.type == TokenType::End) break;
    }
    return tokens;
}

std::string to_str(TokenType type) {
    switch (type) {
        case TokenType::Ret: return "return";
        case TokenType::IntLit: return "integer literal";
        case TokenType::Semi: return "';'";
        case TokenType::End: return "end of source code";
        default: return "invalid";
    }

    return "invalid";
}

std::string display_token(const Token& token) {
    std::ostringstream out;
    switch (token.type) {
        case TokenType::Ret:
            out << "Ret - " << token.line << ":" << token.col;
            break;
        case TokenType::IntLit:
            out << "IntLit:" << token.lexeme << " - "
                << token.line << ":" << token.col;
            break;
        case TokenType::Semi:
            out << "Semi - " << token.line << ":" << token.col;
            break;
        case TokenType::End:
            out << "End - " << token.line << ":" << token.col;
            break;
        default:
            out << "Invalid - " << token.line << ":" << token.col;
            break;
    }
    return out.str();
}

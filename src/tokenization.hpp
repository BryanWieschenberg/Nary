#pragma once
#include <string>
#include <vector>

enum class TokenType {
    INT_LITERAL,
    RETURN,
    SEMICOLON
};

struct Token {
    TokenType type;
    std::optional<std::string> value;
};

class Tokenizer {
public:
    inline explicit Tokenizer(const std::string& src) :
        src_(std::move(src)), index_(0)
    {}

    inline std::vector<Token> tokenize() {
        std::vector<Token> tokens;
        std::string buf;
        while (peek().has_value()) {
            if (std::isalpha(peek().value())) {
                buf.push_back(consume());
                while (peek().has_value() && std::isalnum(peek().value())) {
                    buf.push_back(consume());
                }
                if (buf == "return") {
                    tokens.push_back({.type = TokenType::RETURN});
                    buf.clear();
                    continue;
                } else error();
            } else if (std::isdigit(peek().value())) {
                buf.push_back(consume());
                while (peek().has_value() && std::isdigit(peek().value())) {
                    buf.push_back(consume());
                }
                tokens.push_back({.type = TokenType::INT_LITERAL, .value = buf});
                buf.clear();
                continue;
            } else if (peek().value() == ';') {
                consume();
                tokens.push_back({.type = TokenType::SEMICOLON});
                continue;
            } else if (std::isspace(peek().value())) {
                consume();
                continue;
            } else error();
        }

        index_ = 0;
        return tokens;
    }
    
private:
    const std::string src_;
    size_t index_ = 0;

    [[nodiscard]] inline std::optional<char> peek(int ahead = 0) const {
        if (index_ + ahead >= src_.length()) {
            return {};
        }
        return src_.at(index_ + ahead);
    }

    inline char consume() {
        return src_.at(index_++);
    }

    inline void error() {
        std::cerr << "Invalid syntax" << std::endl;
        exit(EXIT_FAILURE);
    }
};

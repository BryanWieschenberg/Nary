#pragma once
#include <vector>

#include "tokenization.hpp"

struct NodeExpr {
    Token INT_LITERAL;
};

struct NodeReturn {
    NodeExpr expr;
};

class Parser {
public:
    inline explicit Parser(std::vector<Token> tokens) :
        tokens_(std::move(tokens))
    {}

    std::optional<NodeExpr> parse_expr() {
        if (peek().has_value() && peek().value().type == TokenType::INT_LITERAL) {
            return NodeExpr{.INT_LITERAL = consume()};
        }

        return {};
    }

    std::optional<NodeReturn> parse() {
        std::optional<NodeReturn> return_node;
        while (peek().has_value()) {
            if (peek().value().type == TokenType::RETURN) {
                consume();
                auto node_expr = parse_expr();
                if (!node_expr) error();
                if (!peek() || peek()-> type != TokenType::SEMICOLON) error();
                consume();
                return_node = NodeReturn{.expr = *node_expr};
            } else consume();
        }
        index_ = 0;
        return return_node;
    }

private:
    const std::vector<Token> tokens_;
    size_t index_ = 0;

    [[nodiscard]] inline std::optional<Token> peek(int ahead = 0) const {
        if (index_ + ahead >= tokens_.size()) {
            return {};
        }
        return tokens_.at(index_ + ahead);
    }

    inline Token consume() {
        return tokens_.at(index_++);
    }

    inline void error() {
        std::cerr << "Invalid syntax" << std::endl;
        exit(EXIT_FAILURE);
    }
};

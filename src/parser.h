#pragma once

#include "tokenization.h"

namespace node {
    struct NodeExpr {
        Token int_lit;
    };

    struct NodeExit {
        NodeExpr expr;
    };
}

class Parser {
public:
    inline explicit Parser(std::vector<Token> tokens)
        : m_tokens(std::move(tokens)) {
    }

    std::optional<node::NodeExpr> parse_expr() {
        if (peak().has_value() && peak().value().type == TokenType::int_lit) {
            return node::NodeExpr {
                .int_lit = consume()
            };
        }
        else {
            return {};
        }
    }

    std::optional<node::NodeExit> parse() {
        std::optional<node::NodeExit> exit_node;

        while (peak().has_value()) {
            if (peak().value().type == TokenType::_exit) {
                consume();

                if (auto node_expr = parse_expr()) {
                    exit_node = node::NodeExit {
                        .expr = node_expr.value()
                    };
                }
                else {
                    std::cerr << "Invalid expression" << std::endl;
                    exit(EXIT_FAILURE);
                }

                if (!peak().has_value() || peak().value().type != TokenType::semi) {
                    std::cerr << "Invalid expression" << std::endl;
                    exit(EXIT_FAILURE);
                }

                consume();
            }
        }

        m_index = 0;
        return exit_node;
    }

private:
    [[nodiscard]] inline std::optional<Token> peak(int ahead = 0) const {
        if (m_index + ahead >= m_tokens.size()) {
            return {};
        }
        else {
            return m_tokens.at(m_index + ahead);
        }
    }

    inline Token consume() {
        return m_tokens.at(m_index++);
    }

    const std::vector<Token> m_tokens;
    size_t m_index = 0;
};
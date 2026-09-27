#pragma once

#include "parser.h"
#include <sstream>

class Generator {
public:
    inline explicit Generator(node::NodeExit root)
        : m_root(std::move(root)) {
    }

    [[nodiscard]] std::string generate() const {
        std::stringstream output;

        output << "global _start\n";
        output << "_start:\n";
        output << "    mov rax, 60\n";
        output << "    mov rdi, " << m_root.expr.int_lit.value.value() << "\n";
        output << "    syscall\n";

        return output.str();
    }

private:
    node::NodeExit m_root;
};

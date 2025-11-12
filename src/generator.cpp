#include "generator.hpp"

Generator::Generator(std::ostream& out)
    : out(out) {}

void Generator::generate(const ASTNode* node) {
    if (!node) return;

    switch (node->type) {
        case ASTNodeType::RetStmt:
            gen_ret(static_cast<const RetStmt*>(node));
            break;
        case ASTNodeType::IntLit:
            gen_intlit(static_cast<const IntLiteral*>(node));
            break;
    }
}

void Generator::gen_ret(const RetStmt* node) {
    out << "section .text\nglobal _start\n_start:\n";
    int value = 0;
    if (node->expr) value = node->expr->val;
    out << "    mov rdi, " << value << "\n    mov rax, 60\n    syscall\n";
}

void Generator::gen_intlit(const IntLiteral* node) {
    out << "    mov eax, " << node->val << "\n";
}

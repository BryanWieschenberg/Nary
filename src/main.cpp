#include <iostream>
#include <fstream>
#include <sstream>
#include "lexer.hpp"
#include "parser.hpp"
#include "generator.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: nary <input.na> <executable>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Error: cannot open " << argv[1] << "\n";
        return 1;
    }

    std::stringstream buf;
    buf << file.rdbuf();
    std::string src = buf.str();

    Lexer lexer(src);
    std::vector<Token> tokens = lexer.tokenize();
    display_tokens(tokens); // DISPLAY

    Parser parser(tokens);
    ASTNode* ast = parser.parse();
    display_ast(ast); // DISPLAY
    
    if (ast) {
        {
            std::ofstream out("out.asm");
            Generator gen(out);
            gen.generate(ast);
        }
        delete ast;

        std::system("nasm -f elf64 out.asm -o out.o");
        std::system("ld out.o -o main");
    }

    return 0;
}

#include <iostream>
#include <fstream>
#include <sstream>
#include "lexer.hpp"
#include "parser.hpp"

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

    for (const Token& t : tokens)
        std::cout << display_token(t) << " | ";
    std::cout << "\n";

    Parser parser(tokens);
    ASTNode* ast = parser.parse();

    if (ast) std::cout << "SUCCESS\n";
    delete ast;
    
    return 0;
}

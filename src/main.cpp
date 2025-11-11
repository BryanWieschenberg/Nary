#include <iostream>
#include <fstream>
#include <sstream>
#include "lexer.hpp"

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
        std::cout << display_token(t) << "\n";

    return 0;
}

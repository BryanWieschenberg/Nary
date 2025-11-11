#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>

#include "./generation.hpp"

void error() {
    std::cerr << "Invalid syntax" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::printf("Incorrect usage. Correct usage is...\n");
        std::printf("nary <input.na> <executable>\n");
        return EXIT_FAILURE;
    }

    std::string contents;
    {
        std::stringstream contents_stream;
        std::fstream input(argv[1], std::ios::in);
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }

    Tokenizer tokenizer(std::move(contents));
    std::vector<Token> tokens = tokenizer.tokenize();

    Parser parser(std::move(tokens));
    std::optional<NodeReturn> tree = parser.parse();
    if (!tree.has_value()) error();

    Generator generator(tree.value());
    {
        std::fstream file("out.asm", std::ios::out);
        file << generator.generate();
    }

    std::system("nasm -felf64 out.asm");
    char outbuf[256];
    std::snprintf(outbuf, sizeof(outbuf), "ld -o %s out.o", argv[2]);
    std::system(outbuf);

    return EXIT_SUCCESS;
}

// pseudo-IR registration
// addExtern("__velo_write", Type::Void, {Type::PtrChar, Type::USize});

#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
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

std::vector<Token> tokenize(const std::string& str) {
    std::vector<Token> tokens;
    
    std::string buf = "";
    for (int i = 0; i < str.length(); i++) {
        char c = str.at(i);
        if (std::isalpha(c)) {
            buf.push_back(c);
            i++;
            while (std::isalnum(str.at(i))) {
                buf.push_back(str.at(i));
                i++;
            }
            i--;

            if (buf == "return") {
                tokens.push_back({.type = TokenType::RETURN});
                buf.clear();
                continue;
            } else {
                std::perror("Invalid syntax");
                exit(EXIT_FAILURE);
            }
        } else if (std::isdigit(c)) {
            buf.push_back(c);
            i++;
            while (std::isdigit(str.at(i))) {
                buf.push_back(str.at(i));
                i++;
            }
            i--;
            tokens.push_back({.type = TokenType::INT_LITERAL, .value = buf});
        } else if (c == ';') {
            tokens.push_back({.type = TokenType::SEMICOLON});
        } else if (std::isspace(c)) {
            continue;
        } else {
            std::perror("Invalid syntax");
            exit(EXIT_FAILURE);
        }
    }
    
    return tokens;
}

std::string tokens_to_asm(const std::vector<Token>& tokens) {
    std::stringstream output;
    output << "global _start\n_start:\n";

    for (int i = 0; i < tokens.size(); i++) {
        const Token& token = tokens.at(i);

        if (token.type == TokenType::RETURN) {
            if (
                (i + 1 < tokens.size() && tokens.at(i + 1).type == TokenType::INT_LITERAL) &&
                (i + 2 < tokens.size() && tokens.at(i + 2).type == TokenType::SEMICOLON)
            ) {
                output << "    mov rax, 60\n";
                output << "    mov rdi, " << tokens.at(i + 1).value.value() << "\n";
                output << "    syscall\n";
            }
        }
    }

    return output.str();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::printf("Incorrect usage. Correct usage is...\n");
        std::printf("main <input.vl> <executable>\n");
        return EXIT_FAILURE;
    }

    std::string contents;
    {
        std::stringstream contents_stream;
        std::fstream input(argv[1], std::ios::in);
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }

    std::vector<Token> tokens = tokenize(contents);
    {
        std::fstream file("out.asm", std::ios::out);
        file << tokens_to_asm(tokens);
    }

    std::system("nasm -felf64 out.asm");
    char outbuf[256];
    std::snprintf(outbuf, sizeof(outbuf), "ld -o %s out.o", argv[2]);
    std::system(outbuf);

    return EXIT_SUCCESS;
}

// pseudo-IR registration
// addExtern("__velo_write", Type::Void, {Type::PtrChar, Type::USize});

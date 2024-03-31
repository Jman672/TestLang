#include "includeFile.h"

std::string generate_asm(const std::vector<Token>& tokens){
    std::stringstream output;
    std::vector<std::string> labels;
    std::string var, var2;
    output << "global _start\n_start:\n";
    for(int i = 0; i < tokens.size(); i++){
        switch(tokens[i].type) {
            case TokenType::_return:
                if (i + 1 < tokens.size() && tokens[i + 1].type == TokenType::int_lit) {
                    if (i + 2 < tokens.size() && tokens[i + 2].type == TokenType::semi) {
                        output << "    mov rax, 60\n";
                        output << "    mov rdi, " << tokens[i + 1].value.value() << "\n";
                        output << "    syscall\n";
                    }
                }
                i += 2;
                break;
            case TokenType::int_lit:
                std::cerr << "expected an expression or something\n";
                exit(EXIT_FAILURE);
                break;
            case TokenType::semi:
                std::cerr << "expected an expression or something\n";
                exit(EXIT_FAILURE);
                break;
            case TokenType::assign:
                break;
            case TokenType::equal:
                std::cerr << "expected an expression or something\n";
                exit(EXIT_FAILURE);
                break;
            case TokenType::variable:
                for (auto j: labels) {
                    if (j == tokens[i].value.value()) {
                        var == j;
                    }
                }
                if (var.empty()) {
                    std::cerr << tokens[i].value.value() << " is undeclared\n";
                    exit(EXIT_FAILURE);
                } else {
                    if (i + 1 < tokens.size() && tokens[i + 1].type == TokenType::equal) {
                        if (i + 2 < tokens.size() && tokens[i + 2].type == TokenType::int_lit) {
                            if (i + 3 < tokens.size() && tokens[i + 3].type == TokenType::semi) {

                            }
                        } else if (i + 2 < tokens.size() && tokens[i + 2].type == TokenType::variable) {
                            for (auto j: labels) {
                                if (j == tokens[i].value.value()) {
                                    var2 == j;
                                }
                            }
                            if (var2.empty()) {
                                std::cerr << var2 << " is undeclared\n";
                                exit(EXIT_FAILURE);
                            } else {

                            }
                        }
                    }
                }
                break;
        }
    }



    output << "    mov rax, 60\n";
    output << "    mov rdi, 0\n";
    output << "    syscall\n";
    return {};
}
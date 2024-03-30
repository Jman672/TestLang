#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <optional>
#include <vector>

enum class TokenType {
    _return,
    int_lit,
    semi
};

struct Token{
    TokenType type;
    std::optional<std::string> value;
};

std::vector<Token> tokenize(const std::string& str){
    std::vector<Token> tokens;
    std::string buf;
    for(int i = 0; i < str.length(); i++){
        char c = str[i];
        if(std::isalpha(c)){
            while(isalnum(str[i])){
                buf.push_back(str[i]);
                i++;
            }
            i--;
            if(buf == "return"){
                tokens.push_back({.type = TokenType::_return});
                //std::cout<<"return token found\n";
                buf.clear();
                continue;
            }else{
                std::cerr<<"You messed up!";
                exit(EXIT_FAILURE);
            }
        }
        else if(std::isspace(c)){
            continue;
        }
        else if(std::isdigit(c)){
            while(isdigit(str[i])){
                buf.push_back((str[i]));
                i++;
            }
            i--;
            tokens.push_back({.type = TokenType::int_lit, .value = buf});
            //std::cout<<"int token found\n";
            buf.clear();
            continue;
        }
        else if(c == ';'){
            tokens.push_back({.type = TokenType::semi});
            //std::cout<<"semi token found\n";
            continue;
        }
        else{
            std::cerr<<"Soemthing Went Wrong";
            exit(EXIT_FAILURE);
        }
    }
    return tokens;
}

std::string tokens_to_asm(const std::vector<Token>& tokens){
    std::stringstream output;
    output << "global _start\n_start:\n";
    for(int i = 0; i < tokens.size(); i++){
        const Token& token = tokens[i];
        if(token.type == TokenType::_return){
            if(i+1 < tokens.size() && tokens[i+1].type == TokenType::int_lit){
                if(i+2 < tokens.size() && tokens[i+2].type == TokenType::semi){
                    output << "    mov rax, 60\n";
                    output << "    mov rdi, " << tokens[i+1].value.value() << "\n";
                    output << "    syscall\n";
                }
            }
        }
    }
    return output.str();
}

int main(int argc, char** argv){
    if(argc != 2){
        std::cerr << "Incorrect Usage. Correct usage is...\n";
        std::cerr << "test <input.hy>\n";
        return EXIT_FAILURE;
    }

    std::fstream output("out.asm", std::ios::out); //open output file
    std::fstream input(argv[1], std::ios::in); //open input file

    std::stringstream contents_stream;//create a stream for contents of input file
    contents_stream << input.rdbuf();//read input file to a stream
    input.close();//close input file

    std::string contents = contents_stream.str();//get a string from stream

    std::vector<Token> tokens = tokenize(contents);//tokenize the string

    output << tokens_to_asm(tokens);//convert to asm

    output.close();//close output file

    system("nasm -felf64 out.asm");
    system("ld -o out out.o");

    return EXIT_SUCCESS;
}
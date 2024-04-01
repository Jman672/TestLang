//
// Created by Jermiah B on 3/30/2024.
//

#ifndef TESTLANG_TOKENIZATION_HPP
#define TESTLANG_TOKENIZATION_HPP

//#include "includeFile.h"

enum class TokenType {
    _return,
    int_lit,
    semi,
    assign,
    equal,
    variable,
    open_parenthesis,
    close_parenthesis
};

struct Token{
    TokenType type;
    std::optional<std::string> value;
};

class Tokenizer {
public:
    inline explicit Tokenizer(std::string src) : source(std::move(src)){}
    inline std::vector<Token> tokenize(){
        std::vector<Token> tokens;
        std::string buf;
        //std::cout<<"{";
        while(peek().has_value()){
            if(isalpha(peek().value())){
                buf.push_back(consume());
                while(peek().has_value() && std::isalnum(peek().value())){
                    buf.push_back(consume());
                }
                if(buf == "return"){
                    //std::cout<<"return,";
                    tokens.emplace_back(TokenType::_return);
                    buf.clear();
                }else if(buf == "assign"){
                    //std::cout<<"assign,";
                    tokens.emplace_back(TokenType::assign);
                    buf.clear();
                }else{
                    //std::cout<<"variable,";
                    tokens.emplace_back(TokenType::variable, buf);
                    buf.clear();
                }
            }else if(std::isdigit(peek().value())){
                buf.push_back(consume());
                while(peek().has_value() && std::isdigit(peek().value())){
                    buf.push_back(consume());
                }
                //std::cout<<"int_lit: "<<buf<<",";
                tokens.push_back({.type = TokenType::int_lit, .value = buf});
                buf.clear();
            }else if(peek().value() == ';'){
                //std::cout<<"semi,";
                tokens.emplace_back(TokenType::semi);
                consume();
            } else if(isspace(peek().value())){
                consume();
            }else if(peek().value() == '='){
                //std::cout<<"equals,";
                tokens.emplace_back(TokenType::equal);
                consume();
            }else if(peek().value() == '('){
                //std::cout<<"open_parenthesis,";
                tokens.emplace_back(TokenType::open_parenthesis);
                consume();
            }else if(peek().value() == ')'){
                //std::cout<<"close_parenthesis,";
                tokens.emplace_back(TokenType::close_parenthesis);
                consume();
            }else{
                std::cerr << "invalid character: " << peek().value()<<"\n";
                exit(EXIT_FAILURE);
            }
        }
        //std::cout<<"}\n";

        index = 0;
        return tokens;
    }
private:
    [[nodiscard]] inline std::optional<char> peek(int ahead = 0) const{
        if(index + ahead < source.length()){
            return source[index + ahead];
        }
        return {};
    }
    inline char consume(){
        return source[index++];
    }
    size_t index = 0;
    const std::string source;
};


#endif //TESTLANG_TOKENIZATION_HPP

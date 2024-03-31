//
// Created by Jermiah B on 3/30/2024.
//

#ifndef TESTLANG_PARSER_HPP
#define TESTLANG_PARSER_HPP

struct nodeExpression{
    Token int_lit;
};
struct nodeRet{
      nodeExpression expression;
};


class Parser{
public:
    inline explicit Parser(std::vector<Token> tokens) : _tokens(std::move(tokens)){}

    std::optional<nodeExpression> parse_expr(){
        if(peek().has_value() && peek().value().type == TokenType::int_lit){
            return nodeExpression{.int_lit = consume()};
        }else{
            return {};
        }
    }

    std::optional<nodeRet> parse(){
        std::optional<nodeRet> out;
        while(peek().has_value()){
            if(peek().value().type == TokenType::_return){
                consume();
                if(auto node_expr = parse_expr()){
                    out = nodeRet {.expression = node_expr.value()};
                }else{
                    std::cerr << "Invalid Expression";
                    exit(EXIT_FAILURE);
                }
                if(!peek().has_value() || peek().value().type != TokenType::semi){
                    std::cerr << "Missing ';'";
                    exit(EXIT_FAILURE);
                }else{
                    consume();
                }
            }
        }
        index = 0;
        return out;
    }

private:
    [[nodiscard]] inline std::optional<Token> peek(int ahead = 1) const{
        if(index + ahead <= _tokens.size()){
            return _tokens[index];
        }
        return {};
    }
    inline Token consume(){
        return _tokens[index++];
    }

    size_t index = 0;
    const std::vector<Token> _tokens;
};


#endif //TESTLANG_PARSER_HPP

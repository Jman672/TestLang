//
// Created by Jermiah B on 3/30/2024.
//

#ifndef TESTLANG_PARSER_HPP
#define TESTLANG_PARSER_HPP

#include <variant>

struct nodeExprIntLit{
    Token int_lit;
};
struct nodeExprVariable{
    Token variable;
};

struct nodeExpression{
    std::variant<nodeExprIntLit, nodeExprVariable> expr;
};
struct nodeRet{
    nodeExpression expression;
};
struct nodeStatementReturn{
    nodeExpression expression;
};
struct nodeStatementAssign{
    Token variable;
    nodeExpression expression;
};
struct nodeStatement{
    std::variant<nodeStatementReturn, nodeStatementAssign> statement;
};
struct nodeProgram{
    std::vector<nodeStatement> statements;
};


class Parser{
public:
    inline explicit Parser(std::vector<Token> tokens) : _tokens(std::move(tokens)){}

    std::optional<nodeExpression> parse_expr() {
        if (peek().has_value() && peek().value().type == TokenType::int_lit){
            return nodeExpression{.expr = nodeExprIntLit{.int_lit = consume()}};
        } else if (peek().has_value() && peek().value().type == TokenType::variable) {
            return nodeExpression{.expr = nodeExprVariable{.variable = consume()}};
        } else {
            return {};
        }
    }

    std::optional<nodeStatement> parseStatement(){
        nodeStatementReturn out;
        nodeStatementAssign assign;
        if(peek().has_value() && peek().value().type == TokenType::_return){
            consume();
            if(auto node_expr = parse_expr()){
                out.expression = node_expr.value();
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
            return nodeStatement{.statement = out};
        }else if(peek().has_value() && peek().value().type == TokenType::assign){
            consume();
            if(auto node_var = parse_var()){
                assign.variable = node_var.value().variable;
            }else{
                std::cerr << "Invalid Expression";
                exit(EXIT_FAILURE);
            }
            if(peek().has_value() && peek().value().type == TokenType::equal){
                consume();
                if(auto node_expr = parse_expr()){
                    assign.expression = node_expr.value();
                }else{
                    std::cerr << "Expected Expression\n";
                    exit(EXIT_FAILURE);
                }
            }else{
                std::cerr << "Expected '='";
                exit(EXIT_FAILURE);
            }
            if(!peek().has_value() || peek().value().type != TokenType::semi){
                std::cerr << "Expected ';'";
                exit(EXIT_FAILURE);
            }else{
                consume();
            }
            return nodeStatement{.statement = assign};
        }
        return {};
    }

    std::optional<nodeProgram> parseProgram(){
        nodeProgram program;

        while(peek().has_value()){
            if(auto stmt = parseStatement()){
                program.statements.push_back(stmt.value());
            }else{
                std::cerr << "Invalid Statement";
                exit(EXIT_FAILURE);
            }
        }
        return program;
    }


    std::optional<nodeExprVariable> parse_var(){
        if(peek().has_value() && peek().value().type == TokenType::variable){
            return nodeExprVariable{.variable = consume()};
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
    [[nodiscard]] inline std::optional<Token> peek(int ahead = 0) const{
        if(index + ahead < _tokens.size()){
            return _tokens[index + ahead];
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

//
// Created by Jermiah B on 3/30/2024.
//

#ifndef TESTLANG_GENERATE_HPP
#define TESTLANG_GENERATE_HPP

#include <unordered_map>

class Generator{
public:
    inline explicit Generator(nodeProgram program): m_program(std::move(program)){}

    void gen_expr(const nodeExpression& expr){
        struct ExprVisitor{
            Generator* gen;
            void operator()(const nodeExprIntLit& exprintlit) const{
                gen->m_output << "    mov rax, " << exprintlit.int_lit.value.value() << "\n";
                gen->push("rax");
            }
            void operator()(const nodeExprVariable& exprvar)const{
                //TODO
                if(!gen->m_vars.contains(exprvar.variable.value.value())){
                    std::cerr << "Undeclared variable: " << exprvar.variable.value.value() << "\n";
                    exit(EXIT_FAILURE);
                }
                std::stringstream offset;
                offset << "QWORD [rsp + " << 8*(gen->m_stacksize - gen->m_vars[exprvar.variable.value.value()].stack_loc - 1) << "]\n";
                gen->push(offset.str());
                //gen->m_output << "   push [rsp + 8*" << gen->m_stacksize - gen->m_vars[exprvar.variable.value.value()].stack_loc << "]\n";
            }
        };

        ExprVisitor visitor{.gen=this};
        std::visit(visitor, expr.expr);
    }

    void gen_statement(const nodeStatement& statement)  {
        struct statementVisitor{
            Generator* gen;
            void operator()(const nodeStatementReturn& stateRet) const{
                gen->gen_expr(stateRet.expression);
                gen->m_output << "    mov rax, 60\n";
                gen->pop("rdi");
                gen->m_output << "    syscall\n";
            }
            void operator()(const nodeStatementAssign& stateAssign) const{
                if(gen->m_vars.contains(stateAssign.variable.value.value())){
                    std::cerr << "Already used variable " << stateAssign.variable.value.value() << "\n";
                    exit(EXIT_FAILURE);
                }
                gen->m_vars.insert({stateAssign.variable.value.value(), Var{.stack_loc = gen->m_stacksize}});
                gen->gen_expr(stateAssign.expression);

            }
        };
        statementVisitor visitor{.gen = this};
        std::visit(visitor, statement.statement);
    }

    [[nodiscard]] std::string generate() {
        m_output << "global _start\n_start:\n";

        for(const nodeStatement& i : m_program.statements){
            gen_statement(i);
        }

        m_output << "    mov rax, 60\n";
        m_output << "    mov rdi, 0\n";
        m_output << "    syscall\n";
        return m_output.str();
    }

private:

    void push(const std::string& reg){
        m_output << "    push " << reg << "\n";
        m_stacksize++;
    }

    void pop(const std::string& reg){
        m_output << "    pop " << reg << "\n";
        m_stacksize--;
    }
    const nodeProgram m_program;
    std::stringstream m_output;
    size_t m_stacksize = 0;

    struct Var{
        size_t stack_loc;
    };

    std::unordered_map<std::string, Var> m_vars {};
};

//struct nodeProgram{
//    std::vector<nodeStatement> statements;
//};
// struct nodeStatement{
//    std::variant<nodeStatementReturn, nodeStatementAssign> statement;
//};
// struct nodeStatementReturn{
//    nodeExpression expression;
//};
//struct nodeStatementAssign{
//    Token variable;
//    nodeExpression expression;
//};
//struct nodeExpression{
//    std::variant<nodeExprIntLit, nodeExprVariable> expr;
//};
//struct nodeExprIntLit{
//    Token int_lit;
//};
//struct nodeExprVariable{
//    Token variable;
//};



#endif //TESTLANG_GENERATE_HPP

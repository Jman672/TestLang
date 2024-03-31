//
// Created by Jermiah B on 3/30/2024.
//

#ifndef TESTLANG_GENERATE_HPP
#define TESTLANG_GENERATE_HPP

class Generator{
public:
    inline explicit Generator(nodeRet root): root_(std::move(root)){}

    [[nodiscard]] std::string generate() const{
        std::stringstream output;
        output << "global _start\n_start:\n";
        output << "    mov rax, 60\n";
        output << "    mov rdi, " << root_.expression.int_lit.value.value() << "\n";
        output << "    syscall\n";
        return output.str();
    }

private:
    const nodeRet root_;
};



#endif //TESTLANG_GENERATE_HPP

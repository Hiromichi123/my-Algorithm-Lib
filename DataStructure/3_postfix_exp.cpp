// 后移运算符栈计算
# ifndef POSTFIX_EXP_CPP
# define POSTFIX_EXP_CPP
# include"2_stack_queue.cpp"
# include<iostream>

typedef enum {
    LEFT_PARE,
    RIGHT_PARE,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    EOS, // 结束标志
    NUM
}contentType;

contentType getToken(const char* exp, char* symbol, int* index) {
    if(exp[*index] == '\0') return EOS;

    switch(exp[(*index)++]) {
        case '(': *symbol = '('; return LEFT_PARE;
        case ')': *symbol = ')'; return RIGHT_PARE;
        case '+': *symbol = '+'; return ADD;
        case '-': *symbol = '-'; return SUB;
        case '*': *symbol = '*'; return MUL;
        case '/': *symbol = '/'; return DIV;
        case '%': *symbol = '%'; return MOD;
        default: return NUM;
    }
}

class Stack;

class Stack_postfix : public Stack {
private:
    const char* exp;
public:
    Stack_postfix(const char* exp) : Stack() {
        this->exp = exp;
        for(int i = 0; exp[i] != '\0'; i++) {
            this->push(exp[i]);
        }
    }

    int eval();
};

int Stack_postfix::eval() {
    char symbol;
    int op1, op2;
    int index = 0;
    for(contentType token=getToken(exp, &symbol, &index); token != EOS; token=getToken(exp, &symbol, &index)) {
        if(token == NUM) {
            this->push(symbol - '0'); // 转为值入栈
        } else {
            op2 = this->peek(); this->pop();
            op1 = this->peek(); this->pop();

            switch(token) {
                case ADD: this->push(op1 + op2); break;
                case SUB: this->push(op1 - op2); break;
                case MUL: this->push(op1 * op2); break;
                case DIV: this->push(op1 / op2); break;
                case MOD: this->push(op1 % op2); break;
                default: break;
            }
        }
    }
    return this->peek();
}

#ifdef POSTFIX_EXP_TEST
int main() {
    char exp[] = "82/2+56*-";
    Stack_postfix s(exp);
    std::cout << s.eval() << std::endl;
}
#endif // POSTFIX_EXP_TEST

#endif // POSTFIX_EXP_CPP

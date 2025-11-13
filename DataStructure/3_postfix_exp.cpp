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

    *symbol = exp[(*index)++];

    switch(*symbol) {
        case '(': return LEFT_PARE;
        case ')': return RIGHT_PARE;
        case '+': return ADD;
        case '-': return SUB;
        case '*': return MUL;
        case '/': return DIV;
        case '%': return MOD;
        default: return NUM;
    }
}

// 将 contentType 转换为字符
char tokenToChar(contentType token) {
    switch(token) {
        case LEFT_PARE:  return '(';
        case RIGHT_PARE: return ')';
        case ADD:        return '+';
        case SUB:        return '-';
        case MUL:        return '*';
        case DIV:        return '/';
        case MOD:        return '%';
        case NUM:        return 'e'; // error
        case EOS:        return '\0';
    }
    return 'e'; // error
}

class Stack;

class Stack_postfix : public Stack {
private:
    const char* exp;
public:
    Stack_postfix(const char* exp) : Stack(), exp(exp) {}

    int eval();
    void postfix();
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

void Stack_postfix::postfix() {
    int in_stack[] = {0, 19, 12, 12, 13, 13, 13, 0};
    //                (   )   +   -   *   /   %  EOS
    int out_stack[] = {20, 19, 12, 12, 13, 13, 13, 0};
    //                (     )   +   -   *   /   %  EOS

    int index = 0;
    char symbol;
    this->arr[top = 0] = EOS; // 栈底放结束标志

    for(contentType token = getToken(exp, &symbol, &index); token != EOS; token = getToken(exp, &symbol, &index)) {
        if(token == NUM) { // 值输出
            std::cout << symbol;
        } else if (token == RIGHT_PARE) {
            while(arr[top] != LEFT_PARE) { // 左括号最低优先级
                std::cout << tokenToChar((contentType)arr[top]); // 运算符输出
                this->pop();
            }
            this->pop(); // 左括号出栈
        } else {
            while(in_stack[this->peek()] >= out_stack[token]) {
                std::cout << tokenToChar((contentType)arr[top]); // 运算符输出
                this->pop();
            }
            this->push(token); // 运算符入栈
        }
    }

    // 清空栈中剩余的运算符
    while(this->top > 0) {
        std::cout << tokenToChar((contentType)arr[top]); // 运算符输出
        this->pop();
    }
    std::cout<<std::endl;
}

#ifdef POSTFIX_EXP_TEST
int main() {
    char exp[] = "82/2+56*-";
    Stack_postfix s1(exp);
    std::cout << s1.eval() << std::endl;
    char exp2[] = "x/(i-j)*y";
    Stack_postfix s2(exp2);
    s2.postfix();
}
#endif // POSTFIX_EXP_TEST

#endif // POSTFIX_EXP_CPP

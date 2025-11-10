#include<iostream>

#define MAX 100

class Stack {
public:
    int top;
    int arr[MAX];

    Stack() : top(-1) {}
    bool isEmpty();
    bool push(int x);
    bool pop();
    int peek();
};

bool Stack::isEmpty() { return top == -1; }

bool Stack::push(int x) {
    if(top >= MAX - 1) return false; // 栈满
    arr[++top] = x;
    return true;
}

bool Stack::pop() {
    if(isEmpty()) return false; // 栈空
    top--;
    return true;
}

int Stack::peek() {
    if(isEmpty()) return -1; // 栈空
    return arr[top];
}

class Queue {
public:
    int arr[MAX];
    int front;
    int rear;

    Queue() : front(0), rear(0) {}
    bool isEmpty();
    bool enqueue(int x);
    bool dequeue();
    int getHead();
};

bool Queue::isEmpty() { return front == rear; }

// 非循环队列
bool Queue::enqueue(int x) {
    if(rear >= MAX) {
        if(front > 0) { // 前面还有空位
            for(int i=front; i<rear; i++) {
                arr[i - front] = arr[i];
            }
            rear -= front; // rear前移
            front = 0; // front前移到头
        }
        else {
            return false; // 队列真满
        }
    }
    arr[rear] = x;
    rear++;
    return true;
}

bool Queue::dequeue() {
    if(isEmpty()) return false;
    front++; // 后移
    return true;
}

int Queue::getHead() {
    if(isEmpty()) return -1;
    return arr[front];
}

int main() {
    Stack s;
    s.push(10);
    s.push(20);
    s.push(30);
    std::cout << "Top element is: " << s.peek() << std::endl; // 输出30
    s.pop();
    std::cout << "Top element is: " << s.peek() << std::endl; // 输出20

    Queue q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    std::cout << "Front element is: " << q.getHead() << std::endl; // 输出10
    q.dequeue();
    std::cout << "Front element is: " << q.getHead() << std::endl; // 输出20

    return 0;
}
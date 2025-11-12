// 栈与队列
#ifndef STACK_QUEUE_CPP
#define STACK_QUEUE_CPP
#include<iostream>

#define MAX 100

class Stack {
public:
    int top;
    int arr[MAX];

    Stack() : top(-1) {}
    bool isEmpty();
    Stack& push(int x);
    Stack& pop();
    int peek();
};

bool Stack::isEmpty() { return top == -1; }

Stack& Stack::push(int x) {
    if(top >= MAX - 1) std::cerr << "Stack is full" << std::endl; // 栈满
    arr[++top] = x;
    return *this;
}

Stack& Stack::pop() {
    if(isEmpty()) std::cerr << "Stack is empty" << std::endl; // 栈空
    top--;
    return *this;
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
    Queue& enqueue(int x);
    Queue& dequeue();
    int getHead();
};

bool Queue::isEmpty() { return front == rear; }

// 非循环队列
Queue& Queue::enqueue(int x) {
    if(rear >= MAX) {
        if(front > 0) { // 前面还有空位
            for(int i=front; i<rear; i++) {
                arr[i - front] = arr[i];
            }
            rear -= front; // rear前移
            front = 0; // front前移到头
        }
        else {
            std::cerr << "Queue is full" << std::endl; // 队列真满
        }
    }
    arr[rear] = x;
    rear++;
    return *this;
}

Queue& Queue::dequeue() {
    if(isEmpty()) throw std::out_of_range("Queue is empty");
    front++; // 后移
    return *this;
}

int Queue::getHead() {
    if(isEmpty()) return -1;
    return arr[front];
}

#ifdef STACK_QUEUE_TEST
int main() {
    Stack s;
    s.push(10).push(20).push(30);
    std::cout << "Top element is: " << s.peek() << std::endl; // 输出30
    s.pop();
    std::cout << "Top element is: " << s.peek() << std::endl; // 输出20

    Queue q;
    q.enqueue(10).enqueue(20).enqueue(30);
    std::cout << "Front element is: " << q.getHead() << std::endl; // 输出10
    q.dequeue();
    std::cout << "Front element is: " << q.getHead() << std::endl; // 输出20

    return 0;
}
#endif // STACK_QUEUE_TEST

#endif // STACK_QUEUE_CPP

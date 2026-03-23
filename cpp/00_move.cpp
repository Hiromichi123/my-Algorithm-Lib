#include <iostream>
/*
    左值：
    lvalue  纯左值 left

    右值：
    xvalue  将亡值（即将被移动的对象）eXpiring，它是一个信号，告诉接收的构造器或重载运算符，可以移动资源了。
    prvalue 纯右值 pure right
*/

auto main() -> int {
    int a = 10;               // a 是左值
    int& ra = a;              // ra 是左值引用，绑定到左值 a
    int&& rra = std::move(a); // rra 是右值引用，本身是左值，所有具名对象都是左值。move 返回右值引用，值类别为 xvalue，绑定到了 rra 上
    /*
        左值引用 必须 绑定到 lvalue 的引用
        右值引用 可以 绑定到 xvalue 或 prvalue的引用
    */
    std::cout<<"a: "<< a << std::endl;
    ra++;
    std::cout<<"ra: "<< ra << std::endl;
    rra++;
    std::cout<<"rra: "<< rra << std::endl;
    return 0;
}

// std::move 将传参数转换为右值引用类型，move 本身不直接移动资源
template<typename T>
typename std::remove_reference<T>::type&& move(T&& t) noexcept {
    return static_cast<typename std::remove_reference<T>::type&&>(t);
}

// 示例
class MyString {
    char* data;
    size_t len;
public:
    // 移动构造函数
    MyString(MyString&& other) noexcept 
        : data(other.data), len(other.len) {
        other.data = nullptr;   // 让源对象放弃资源所有权
        other.len = 0;
    }
    
    // 移动赋值运算符
    MyString& operator=(MyString&& other) noexcept {
        if (this != &other) {
            delete[] data;      // 释放当前资源
            data = other.data;   // 转移资源
            len = other.len;
            other.data = nullptr;
            other.len = 0;
        }
        return *this;
    }
};

// 使用示例
MyString createString() {
    MyString temp("hello");
    return temp;  // 自动使用移动语义（C++11起）
}

MyString s1 = createString();      // 移动构造
MyString s2 = std::move(s1);       // 显式移动
// s1 现在处于"有效但未指定"状态

#include <iostream>
// 奇特递归模板cruiously recurring template pattern(CRTP)
// 派生类将自身作为模板参数传递给基类

// 虚函数的调用是通过虚表实现的，编译器在编译时无法确定调用哪个函数，因此无法内联
template <typename Derived>
struct Base {
    template <typename TI>
    void Fun(const TI& input) {
        Derived* derived = static_cast<Derived*>(this); // 将Base指针强制转换为Derived指针，因为此时Base知道了Derived的类型
        derived->Impl(input); // 编译器看到的是Derived::Impl(input)，会尝试内联调用
    }
};

struct Derived : public Base<Derived> {
    template <typename TI>
    void Impl(const TI& input) {
        std::cout << input << std::endl;
    }
};

int main() {
    Derived d;
    d.Fun("Hello World");
    return 0;
}

// 注意：Impl这样的函数模板，或者类的静态函数，不能声明为虚函数
// 函数签名要在编译期确定，模板函数本质不是函数，而是一组函数簇的生成规则。而静态函数不依赖于对象实例，无法通过虚表（vtable）机制实现多态。
// 如果想要实现类似于运行时多态的功能，可以使用CRTP
template <typename Derived>
struct Base {
    static void Fun() {
        Derived::Impl();
    }
};

struct Derived : public Base<Derived> {
    static void Impl() {
        std::cout << "Hello World" << std::endl;
    }
};

int main() {
    Derived::Fun();
    return 0;
}

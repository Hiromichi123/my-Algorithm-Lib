#include <iostream>
/*
    lvalue  纯左值 left
    xvalue  将亡值 eXpiring，它是一个信号，告诉接收的构造器或重载运算符，可以移动资源了。
    prvalue 纯右值 pure right
*/

auto main() -> int {
    int a = 10;
    int& ra = a;
    int&& rra = std::move(a); // 返回右值引用，返回值类别为 xvalue
    /*
        右值引用 可以 绑定到 xvalue 或 prvalue的引用
        左值引用 必须 绑定到 lvalue 的引用
    */
    std::cout<<"a: "<< a << std::endl;
    ra++;
    std::cout<<"ra: "<< ra << std::endl;
    rra++;
    std::cout<<"rra: "<< rra << std::endl;
    return 0;
}

// std::move 的核心，其实就将传参数强制转换为右值引用类型，所以 move 本身其实不直接移动资源!
template<typename T>
typename std::remove_reference<T>::type&& move(T&& t) noexcept {
    return static_cast<typename std::remove_reference<T>::type&&>(t);
}

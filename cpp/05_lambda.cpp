// lambda表达式
// 一种匿名函数，可以直接在需要函数对象的地方定义和使用。手动控制可访问的外部变量，简化代码结构，提高可读性和灵活性。
// 语句：
// [capture](parameters) -> return_type { body }
// capture：捕获列表，指定lambda表达式可以访问哪些外部变量，[this]捕获当前对象，[=]默认按值全部捕获，&默认按引用全部捕获


// 默认lambda是const的
[a]() {
    a = 10; // error: a是只读变量
};

[&a]() {
    a = 10; // ok
};

[a]() mutable {
    a = 10; // ok，但修改的是a的拷贝
};

// 返回值常用auto推导
auto add = [](int a, int b) {
    return a + b;
};
// 如果需要也可以显示指定返回类型
auto add = [](int a, int b) -> int { 
    return a + b;
};

// 隐式捕获
int a = 10, b = 20;
auto lambda = [=, &b]() { // 隐式按值捕获a，按引用捕获b
    return a + b;
};

// C++14引入了泛型lambda，可以使用auto推导和模板参数，也允许使用表达式做参数构建新的变量。
int x = 10;
auto lambda = [y = x + 5](auto z) { // y是一个新的变量，值为x + 5
    return y + z;
};

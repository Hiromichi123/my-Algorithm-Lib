// 万能引用 模板+引用折叠
template<typename T>
void foo(T&& x);

// T&& 是万能引用（forwarding reference），既可以接收左值也可以接收右值

// 引用折叠 reference collapsing规则
// T& & -> T& // 左值
// T& && -> T& // 左值
// T&& & -> T& // 右值
// T&& && -> T&& // 右值


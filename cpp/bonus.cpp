
// 一个声明了一个函数指针数组的变量f，数组中的每个元素都是指向返回类型为int且无参数的函数的指针
int (*f[])();

int sampleFunction1() {
    return 42;
}

int sampleFunction2() {
    return 7;
}

void exampleUsage() {
    // 初始化函数指针数组
    f[0] = sampleFunction1;
    f[1] = sampleFunction2;

    // 调用函数指针数组中的函数
    int result1 = f[0](); // 调用sampleFunction1
    int result2 = f[1](); // 调用sampleFunction2
}


// 定义一个结构体X，重载逗号运算符
struct X{
    int operator,(int v){ return 666; }
};

// 使用重载的逗号运算符
void exampleCommaOperator(){
    X x;
    int a = (x, 3);  // → 调用 x.operator,(3)
}

// 在预先分配的缓冲区buffer中构造类型T的对象，传递参数args...
void examplePlacementNew(){ 
    new(buffer) T(args...);
}

// 使用decltype推导变量类型
void exampleDecltype(){
    int i = 4;
    decltype(i) a; //推导结果为int。a的类型为int。

    // 与using/typedef合用，用于定义类型。
    using size_t = decltype(sizeof(0));//sizeof(a)的返回值为size_t类型
    using ptrdiff_t = decltype((int*)0 - (int*)0);
    using nullptr_t = decltype(nullptr);

    int x;
    decltype(x);   // x的声明类型为int
    decltype((x)); // x的表达式类型为int&
}

template<auto N> // n可以是任意非类型模板参数，int、enum、（函数）指针、lambda
struct Vec { };
Vec<[]()[]>
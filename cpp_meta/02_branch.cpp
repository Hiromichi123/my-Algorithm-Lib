# include<iostream>
// 编译期的分支逻辑可以表现为纯粹的元函数，也可以与运行期的执行逻辑相结合

// 常用形式：模版特化实现分支
struct A;
struct B;

template <typename T>
struct Fun_ { constexpr static size_t value = 0; };

template <>
struct Fun_<A> { constexpr static size_t value = 1; };

template <>
struct Fun_<B> { constexpr static size_t value = 2; };

constexpr size_t valueA = Fun_<A>::value; // valueA为1
constexpr size_t valueB = Fun_<B>::value; // valueB为2


// C++14 引入了变量模版，简化特化过程
struct A;
struct B;

template <typename T>
constexpr size_t Fun = 0;

template <>
constexpr size_t Fun<A> = 1;

template <>
constexpr size_t Fun<B> = 2;

constexpr size_t valueA = Fun<A>; // valueA为1
constexpr size_t valueB = Fun<B>; // valueB为2

//——————————————————————————————————————————————————————————————

// 使用 std::conditional 和 std::enable_if 实现分支（type_traits库cpp11）
namespace std {

    template <bool B, typename T, typename F>
    struct conditional { using type = T; };

    template <typename T, typename F>
    struct conditional<false, T, F> { using type = F; };

    template <bool B, typename T, typename F>
    using conditional_t = typename conditional<B, T, F>::type;
}
// 逻辑为：如果B为true，则type为T，否则为F
std::conditional<true, int, float>::type x = 3; // type为int
std::conditional_t<false, int, float> y = 3.14f; // type为float
//编译期的三目运算 x = B ? T : F

//——————————————————————————————————————————————————————————————

// 2.使用（部分）特化实现分支

// 非完全特化引入完全特化分支是非法的
// 因此，可以使用 部分特化 + 伪参数TDummy，来代替完全特化
template <typename TW> // 让Wrapper成为模版类，可以特化
struct Wrapper {
    template <typename T, typename TDummy = void> // 伪参数TDummy，保持分支的合法性
    struct Fun_ {
        constexpr static size_t value = 0;
    };

    // int特化分支
    template <typename TDummy>
    struct Fun_<int, TDummy> {
        constexpr static size_t value = 1;
    };
};

// 使用示例
Wrapper<void>::Fun_<int>::value; // value为1
Wrapper<void>::Fun_<float>::value; // value为0

//——————————————————————————————————————————————————————————————

// 3.使用 std::enable_if 和 std::enable_if_t 实现分支（type_traits库cpp11）
namespace std {

    template <bool B, typename T = void>
    struct enable_if {};

    template <typename T>
    struct enable_if<true, T> { using type = T; };

    template <bool B, typename T = void>
    using enable_if_t = typename enable_if<B, T>::type;
}


// 编译期多返回类型
// 运行期函数返回值不同，编译器无法推导，无法通过编译
auto wrap1(bool Check) {
    if(Check) return (int)0;
    else return (double)0;
}

// 通过std::enable_if编译期分支，可以支持不同类型返回值，编译器可以推导
// check不匹配时，因为enable_if的SFINAE特性，返回void*的模版会被剔除编译
template <bool Check, std::enable_if_t<Check>* = nullptr> // void*可以当模板参数使用，不影响前面的参数，并且触发SFINAE。nullptr是语法上赋予的默认值
auto fun() {
    return (int)0;
}

template <bool Check, std::enable_if_t<!Check>* = nullptr>
auto fun() {
    return (double)0;
}

template <bool Check>
auto wrap2() {
    return fun<Check>();
}

// 使用示例
std::cout << wrap2<true>() << std::endl; // 输出0，类型为int
std::cout << wrap2<false>() << std::endl; // 输出0，类型为double

// C++17引入了if constexpr，简化了编译期分支的实现
// if constexpr必须接收编译期常量表达式，编译器会条件只编译对应的分支代码
template <bool Check>
auto wrap3() {
    if constexpr (Check) { return (int)0; }
    else { return (double)0; }
}

std::cout << wrap3<true>() << std::endl; // 输出0，类型为int
std::cout << wrap3<false>() << std::endl; // 输出0，类型为double

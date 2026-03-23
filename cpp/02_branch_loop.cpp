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

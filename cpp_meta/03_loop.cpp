#include <iostream>
// 在编译期操作到更多是常量、类型、，模版，往往使用递归来实现循环

// 使用元函数计算一个数二进制表示中1的个数
template <size_t Input>
constexpr size_t OnesCount = (Input % 2) + OnesCount<Input / 2>;

template <> constexpr size_t OnesCount<0> = 0;

constexpr size_t res = OnesCount<45>; 

// 循环累加数组
template <size_t... Inputs> // ...是参数包，表示可以接受任意数量的size_t参数
constexpr size_t Accumulate = 0;

template <size_t CurInput, size_t... Inputs>
constexpr size_t Accumulate<CurInput, Inputs...> = CurInput + Accumulate<Inputs...>;

constexpr size_t res = Accumulate<1, 2, 3, 4, 5>;

// C++17提供fold expression，简化了递归实现的循环
template <size_t... values>
constexpr size_t fun() {
    return (... + values);
}

constexpr size_t res = fun<1, 2, 3, 4, 5>();


// 引入短路逻辑，减少编译期实例化
template <size_t N>
constexpr bool is_odd = ((N % 2) == 1);

template <size_t N>
struct AllOdd_ {
    constexpr static bool is_cur_odd = is_odd<N>;
    constexpr static bool is_pre_odd = AllOdd_<N - 1>::value;
    constexpr static bool value = is_cur_odd && is_pre_odd;
};

template <>
struct AllOdd_<0> {
    constexpr static bool value = is_odd<0>;
};
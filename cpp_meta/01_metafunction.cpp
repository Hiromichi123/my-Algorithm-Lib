# include <iostream>
// 数值、类型、模版统称为"元数据"
// 维护系统的变量的时变函数为"副作用函数"

// 元函数（metafunction）示例
constexpr int fun(int a) { return a+1; } // 满足无副作用
// constexpr, C++11关键字，前缀表示该函数在编译期求值，去掉则只能用于运行时


// 反例
static int g = 0;
constexpr int fun2() { return g++; } // 引入运行时变量，不满足无副作用
// 此时constexpr会试图保持"无副作用"，所以无法通过编译


// 特化模版：编译器构建类型转换通道，避免运行时开销
template <typename T>
struct Fun_ { using type = T; };

template <>
struct Fun_<int> { using type = unsigned int; };

template <>
struct Fun_<long> { using type = unsigned long; };

Fun_<int>::type h = 3; // 语义等价于运行时int h = 3; h.to_unsignedInt();


// 取别名方便调用
template<tpyename T>
using Fun = typename Fun_<T>::type;
Fun<int> h = 3; // 更加简洁，不需要写::type

// 无参元函数
template <int a>
constexpr int fun = a+1;

// 多输出的元函数
template <>
struct Fun_<int> {
    using value_type = int;
    using reference_type = int&;
    using const_reference_type = const int&;
};


// type_traits库cpp11
std::remove_reference<int&>::type a; // type为int
std::remove_reference_t<int&> a; // type为int，_t版本更简洁
// 如果返回值要使用某种依赖型名称，命名为xxx_或者xxx_t，如果可以直接使用命名为xxx


// 模版作为元函数的输入
template <template <typename> class T1, typename T2>
struct Fun_ {
    using type = typename T1<T2>::type;
};

template <template <typename> class T1, typename T2>
using Fun = typename Fun_<T1, T2>::type;

Fun<std::remove_reference, int&> h = 3;
//Fun(T1,T2)=T1(2)是一个高阶函数，以另一个函数名作为输入


// 模版作为元函数的输出（延迟构造）
template <int flag> struct Fun_;

template <>
struct Fun_<0> {
    template <typename T>
    using type = vector<T>;
};

template <>
struct Fun_<1> {
    template <typename T>
    using type = list<T>;
};

template <typename T>
tmplate <int flag>
using Fun = typename Fun_<flag>::template type<T>;

//————以上是定义，以下是使用时选择————

template <typename T>
using Fun = typename Fun_<1>::template type<T>;
Fun<int> h; // h此刻是list<int>类型

template <typename T>
using Fun = typename Fun_<0>::template type<T>;
Fun<int> h; // h此刻是vector<int>类型


// C++11引入的变长模版参数（variadic template），声明中的...表示参数包，包含足够的编译期展开信息
template <int... Vals> struct IntContainer;
template <bool... Bools> struct BoolContainer;
template <typename... Types> struct TypeContainer;
template <auto... Vals> struct AutoContainer; // C++14引入的auto参数包，自动推导

template <template <typename> class... T> struct TemplateContainer;
// 存放模版作为参数，每个模版可以接收一个类型作为参数
template <template <typename...> class... T> struct VariadicTemplateContainer;
// 存放模版作为参数，每个模版可以接收任意数量的类型作为参数

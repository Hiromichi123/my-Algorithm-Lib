#include <iostream>
// 异类词典VarTypeDict是一个容器，异类指可以存储不同类型的元素

// 编译期具名参数
struct FParams : public VarTypeDict<A, B, Weight> {};
// 等价于
using FParams = VarTypeDict<A, B, Weight>;

template <typename TIn>
float Fun(const TIn& input) {
    // 从参数字典中获取参数值
    auto a = FParams::Get<A>();
    auto b = FParams::Get<B>();
    auto weight = FParams::Get<Weight>();

    // 使用参数进行计算
    return a * weight + b * (1 - weight);
}

int main() {
    std::cerr << "a: " << Fun(FParams::Create()
                                    .Set<A>(1.0f)
                                    .Set<B>(2.0f)
                                    .Set<Weight>(0.5f));
    // 如果是一般的std::map，参数顺序不同/不全，会发生运行时错误，且带有运行时开销

    return 0;
}

// ---------------------------------------------------------------------------

// VarTypeDict的实现：
// 用类型Tag作为key，值作为value
template <typename... TParameters> // Tag类型
struct VarTypeDict {
    template <typename... TTypes> // Value类型
    struct Values { // 具体存数值的容器
    public:
        template <typename TTag, typename TVal>
        auto Set(TValue&& value) && ; // &&表示只能对右值对象调用，链式set

        template <typename TTag>
        const auto& Get() const;
    };

public:
    static auto Create() {
        using namespace NSVarTypeDict;
        using type = typename Create_<sizeof...(TParameters), // key数量，sizeof...是编译期运算符，返回参数包中元素的数量N
                                                Values>::type; // 生成一个Values类型，包含所有参数的值
        return type{}; // 返回一个空Values对象
    }
};
// 执行后所构造的对象为：VarTypeDict<A, B, Weight>::Values<1.0f, 2.0f, 0.5f>
// A、B、Weight是Tag，1.0f、2.0f、0.5f是对应的Value

// NSVarTypeDict命名空间中定义了一个递归模板Create_，用于根据参数数量N生成一个Values类型
// N：表示还需要构造的元素数目
// TCont：容器类型。用于存储最终结构（值是类型的数组）
// T...：已经生成的类型序列
namespace NSVarTypeDict {
    template <size_t N, template<typename...> class TCont, typename...T>
    struct Create_ {
        using type = typename Create_<N - 1, TCont, NullParameter, T...>::type; // 递归填入NullParameter，直到N为0
    };

    // 终止条件的特化分支
    template <template<typename...> class TCont, typename...T>
    struct Create_<0, TCont, T...> {
        using type = TCont<T...>;
    };
}


// Values的主体：
template <typename... TParameters>
struct VarTypeDict {
    template <typename... TTypes>
    struct Values {
        Values() = default;

        Valuess(std::shared_ptr<void>(&&input) [sizeof...(TTypes)]) {
            for(size_t i = 0; i<sizeof...(TTypes); ++i) {
                m_tuple[i] = std::move(input[i]);
            }
        }

    public:
        template <typename TTag, typename TVal>
        auto Set(TVal&& val) && {
            using namespace NSVarTypeDict;
            constexpr static size_t TagPos = Tag2ID<TTag, TParameters...>::value; 

            using rawVal = std::decay_t<TVal>;
            rawVal* tmp = new rawVal(std::forword<TVal>(val));
            m_tuple[TagPos] = std::shared_ptr<void>(tmp,
                [](void* ptr) {
                rawVal* nptr = statuc_cast<rawVal*>(ptr);
                delete nptr;
            });

            using new_type = NewTupleType<rawVal, TagPos, Values, TTypes...>;
            return new_type(std::move(m_tuple));
        }

        template <typename TTag>
        auto& Get() const;
    
    private:
        std::shared_ptr<void> m_tuple[sizeof...(TTypes)];
    };
};

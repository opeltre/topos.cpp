#include <concepts>
#include <utility>

using namespace std;

template<class T, class Index=size_t> 
using Gets = decltype(declval<T>()[declval<Index>()]);

template<typename V>
concept Vector = requires(V const& v) {
    typename Gets<V const&>;
    { V( declval<Gets<V const&>(*)(size_t)> ) };
    //{ V([] (size_t) -> Gets<V const&>{}) };
};

template <Vector V> 
V operator + (const V& lhs, const V& rhs) {
    return V([&] (int i) {return lhs[i] + rhs[i];});
};


#include <concepts>
#include <utility>
#include <functional>

using namespace std;

template<class T, class Index=size_t> 
using Items = decltype(declval<T>()[declval<Index>()]);

template<typename V>
concept Vector = requires(V const& v, function<Items<V>(size_t)> f) {
    typename Items<V const&>;
    { V(f) };
    { v.size } -> convertible_to<size_t>;
};

/*---  - V  ---*/

template <Vector V>
V operator - (const V& v) {
    return V([&] (size_t i) {return -v[i];});
}

/*---  V `op` V  ---*/

template <Vector V> 
V operator + (const V& lhs, const V& rhs) {
    return V([&] (int i) {return lhs[i] + rhs[i];});
};
template <Vector V> 
V operator - (const V& lhs, const V& rhs) {
    return V([&] (int i) {return lhs[i] - rhs[i];});
};
template <Vector V> 
V operator * (const V& lhs, const V& rhs) {
    return V([&] (int i) {return lhs[i] * rhs[i];});
};
template <Vector V> 
V operator / (const V& lhs, const V& rhs) {
    return V([&] (int i) {return lhs[i] / rhs[i];});
};

/*---  V `op` k ---*/

template <Vector V>
V operator + (const V& lhs, Items<V const&> rhs) {
    return V([&] (int i) {return lhs[i] + rhs;});
};
template <Vector V>
V operator - (const V& lhs, Items<V const&> rhs) {
    return V([&] (int i) {return lhs[i] - rhs;});
};
template <Vector V>
V operator * (const V& lhs, Items<V const&> rhs) {
    return V([&] (int i) {return lhs[i] * rhs;});
};
template <Vector V>
V operator / (const V& lhs, Items<V const&> rhs) {
    return V([&] (int i) {return lhs[i] / rhs;});
};

/*---  k `op` V  ---*/

template <Vector V>
V operator + (Items<V const&> lhs, const V& rhs) {
    return V([&] (int i) {return lhs + rhs[i];});
};
template <Vector V>
V operator - (Items<V const&> lhs, const V& rhs) {
    return V([&] (int i) {return lhs - rhs[i];});
};
template <Vector V>
V operator * (Items<V const&> lhs, const V& rhs) {
    return V([&] (int i) {return lhs * rhs[i];});
};
template <Vector V>
V operator / (Items<V const&> lhs, const V& rhs) {
    return V([&] (int i) {return lhs / rhs[i];});
};

/*---  V `op=` V  ---*/ 

template <Vector V> 
V& operator += (V& a, const V& b) {
    return a.map([&] (Items<V> ai, size_t i) {return ai + b[i];});
};
template <Vector V> 
V& operator -= (V& a, const V& b) {
    return a.map([&] (Items<V> ai, size_t i) {return ai - b[i];});
};
template <Vector V> 
V& operator *= (V& a, const V& b) {
    return a.map([&] (Items<V> ai, size_t i) {return ai * b[i];});
};
template <Vector V> 
V& operator /= (V& a, const V& b) {
    return a.map([&] (Items<V> ai, size_t i) {return ai / b[i];});
};

/*---  V `op=` k  ---*/ 

template <Vector V> 
V& operator += (V& a, Items<V> b) {
    return a.fmap([&] (Items<V> ai) {return ai + b;});
};
template <Vector V> 
V& operator -= (V& a, Items<V> b) {
    return a.fmap([&] (Items<V> ai) {return ai - b;});
};
template <Vector V> 
V& operator *= (V& a, Items<V> b) {
    return a.fmap([&] (Items<V> ai) {return ai * b;});
};
template <Vector V> 
V& operator /= (V& a, Items<V> b) {
    return a.fmap([&] (Items<V> ai) {return ai / b;});
};

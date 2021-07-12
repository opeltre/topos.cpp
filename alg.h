#include <concepts>
#include <utility>
#include <functional>

namespace topos {

/*=== Type aliases ===*/

typedef std::size_t index_t;

typedef double dtype;

//template <typename Target, typename ... Sources>
//using function = std::function<Target(Sources...)>;

/*=== Items type ===*/ 

template<class T, class Index=index_t> 
using Items = decltype(std::declval<T>()[std::declval<Index>()]);

/*=== Vector types ===*/

template<typename V>
concept Vector = 
requires(V const& v, std::function<Items<V>(index_t)> f) {
    typename Items<V const&>;
    { V(f) };
    { v.size } -> std::convertible_to<index_t>;
};

/*=== Arithmetic ===*/

/*---  - V  ---*/

template <Vector V>
V operator - (const V& v) {
    return V([&] (index_t i) {return -v[i];});
}

/*---  V `op` V  ---*/

template <Vector V> 
V operator + (const V& lhs, const V& rhs) {
    return V([&] (index_t i) {return lhs[i] + rhs[i];});
};
template <Vector V> 
V operator - (const V& lhs, const V& rhs) {
    return V([&] (index_t i) {return lhs[i] - rhs[i];});
};
template <Vector V> 
V operator * (const V& lhs, const V& rhs) {
    return V([&] (index_t i) {return lhs[i] * rhs[i];});
};
template <Vector V> 
V operator / (const V& lhs, const V& rhs) {
    return V([&] (index_t i) {return lhs[i] / rhs[i];});
};

/*---  V `op` k ---*/

template <Vector V>
V operator + (const V& lhs, Items<V const&> rhs) {
    return V([&] (index_t i) {return lhs[i] + rhs;});
};
template <Vector V>
V operator - (const V& lhs, Items<V const&> rhs) {
    return V([&] (index_t i) {return lhs[i] - rhs;});
};
template <Vector V>
V operator * (const V& lhs, Items<V const&> rhs) {
    return V([&] (index_t i) {return lhs[i] * rhs;});
};
template <Vector V>
V operator / (const V& lhs, Items<V const&> rhs) {
    return V([&] (index_t i) {return lhs[i] / rhs;});
};

/*---  k `op` V  ---*/

template <Vector V>
V operator + (Items<V const&> lhs, const V& rhs) {
    return V([&] (index_t i) {return lhs + rhs[i];});
};
template <Vector V>
V operator - (Items<V const&> lhs, const V& rhs) {
    return V([&] (index_t i) {return lhs - rhs[i];});
};
template <Vector V>
V operator * (Items<V const&> lhs, const V& rhs) {
    return V([&] (index_t i) {return lhs * rhs[i];});
};
template <Vector V>
V operator / (Items<V const&> lhs, const V& rhs) {
    return V([&] (index_t i) {return lhs / rhs[i];});
};

/*---  V `op=` V  ---*/ 

template <Vector V> 
V& operator += (V& a, const V& b) {
    return a.map([&] (Items<V> ai, index_t i) {return ai + b[i];});
};
template <Vector V> 
V& operator -= (V& a, const V& b) {
    return a.map([&] (Items<V> ai, index_t i) {return ai - b[i];});
};
template <Vector V> 
V& operator *= (V& a, const V& b) {
    return a.map([&] (Items<V> ai, index_t i) {return ai * b[i];});
};
template <Vector V> 
V& operator /= (V& a, const V& b) {
    return a.map([&] (Items<V> ai, index_t i) {return ai / b[i];});
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

}//topos

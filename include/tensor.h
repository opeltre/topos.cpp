#include <iostream>
#include <functional> 
#include <string> 

namespace topos {

template<typename S, typename T, Vector Vec>
struct MultiDim : public Vec {

    //--- N-dim indexing ---
    //  
    //  Given a `Vector V` instance, 
    //  define a child class MultiDim<shape> of N-ary functions
    //  with `operator () (size_t i0, ..., size_t iN)`
    //  returning row-major indexing of the underlying vector.

    /*--- Shape type ---*/
    using Vec::Vec;
    using shape = S;
    static constexpr index_t dim = shape::dim;

    /*--- N-ary call ---*/

    template<typename ... Is, Indices<shape, Is...> = true>
    T operator () (Is ... is) {
        index_t js [dim] = {static_cast<index_t>(is)...};
        return Vec::operator[](shape::index(js));
    }
    template<typename Index>
    T operator () (Index js[dim]) {
        return Vec::operator[](shape::index(js));
    }
    T operator () (std::initializer_list<index_t> js) {
        return Vec::operator[](shape::index(js));
    }
};

/*------ Tensor ------*/

template<typename S, typename T=dtype> 
using Tensor = MultiDim<S, T, Vect<S::size, T>>;

/*--- show ---*/

template <typename shape, typename T=dtype> 
std::string to_string (Tensor<shape,T> v) {
    index_t n = shape::size;
    std::string str = "Tensor " + std::to_string(shape::dim) + " [";
    for (index_t i = 0; i < n; i++) {
        str += std::to_string(v.values[i]);
        str += (i == n  - 1 ?  "]" : ", ");
    }
    return str;
}

}//topos

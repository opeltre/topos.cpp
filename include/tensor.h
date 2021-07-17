#include <iostream>
#include <functional> 
#include <string> 

namespace topos {

template<typename S, typename T, template<size_t, typename> typename Vec>
struct MultiDim;

template<
    typename T, 
    template<size_t, typename> typename Vec,
    index_t n, index_t ... ns>

struct  MultiDim<Shape<n, ns...>, T, Vec>
    :   public Vec<Shape<n, ns...>::size, T> {

    //--- N-dim indexing ---
    //  
    //  Given a `Vector V` instance, 
    //  define a child class MultiDim<shape> of N-ary functions
    //  with `operator () (size_t i0, ..., size_t iN)`
    //  returning row-major indexing of the underlying vector.

    /*--- Shape type ---*/
    using shape = Shape<n, ns...>;
    using Vec<shape::size, T>::Vec;

    template <typename S>
    using  Type = MultiDim<S, T, Vec>;

    /*
    using sliced = 
        MultiDim<typename S::sliced, T, Vec>;
    */

    static constexpr index_t dim = shape::dim;

    /*--- N-ary call ---*/

    template<typename ... Is, Indices<shape, Is...> = true>
    T operator () (Is ... is) {
        index_t js [dim] = {static_cast<index_t>(is)...};
        return this->operator[](shape::index(js));
    }
    template<typename Index>
    T operator () (Index js[dim]) {
        return this->operator[](shape::index(js));
    }
    T operator () (std::initializer_list<index_t> js) {
        return this->operator[](shape::index(js));
    }
    
    auto slice (index_t i) {
        return MultiDim<Shape<ns...>, T, Vec> 
            ([&] (index_t j) {
                return this->operator[](Shape<ns...>::size * i + j);
            });
    };
   
    /*--- Pull-back ---*/

    template<typename Arrow>
    auto pull () {
        return Type<typename Arrow::src>
            ([&] (index_t i) {
                return this->operator[](Arrow::map(i));
            });
    }

    /*--- Otimes ---*/
    
    template<typename S2>
    auto operator >> (const MultiDim<S2, T, Vec>& t2) const {
        return otimes(*this, t2);
    }
};

/*------ Tensor ------*/

template<typename S, typename T=dtype> 
using Tensor = MultiDim<S, T, Vect>;

/*--- show ---*/

template <typename shape, typename T=dtype> 
std::string to_string (const Tensor<shape,T>& v) {
    return "Tensor " + shape::show() + " " + _str(v);
}

/*------ Tensor Product ------*/ 

template<typename S1, typename S2, typename T,
        template <size_t,typename> typename Vec>
auto otimes (
    const MultiDim<S1, T, Vec>& t1, 
    const MultiDim<S2, T, Vec>& t2 
){
    return MultiDim<Times<S1, S2>, T, Vec> 
        ([&] (index_t i) {
            return t1[i / S2::size] * t2[i % S2::size]; 
        });
}

template<typename T, typename ... Ts>
auto oprod (const T& t, const Ts& ... ts) {
    return (t >> ... >> ts);
}

}//topos

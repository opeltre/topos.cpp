#include <iostream>
#include <functional> 
#include <string> 

namespace topos {

/*------ Tensor ------*/

template<typename Domain, typename T=dtype> 
struct Tensor : public Vect<Domain::size, T> {

    using Vect<Domain::size, T>::Vect;
    using shape = Domain;
    static constexpr index_t dim = shape::dim;
    static constexpr index_t size = shape::size;

    /* --- Access ---*/
    
    template<typename ... Is, Indices<shape, Is...> = true>
    T operator () (Is ... is) {
        index_t js [dim] = {static_cast<index_t>(is)...};
        return this->values[shape::index(js)];
    }

    template<typename Index>
    T operator () (Index js[dim]) {
        return this->values[shape::index(js)];
    }
    T operator () (std::initializer_list<index_t> js) {
        return this->values[shape::index(js)];
    }
};

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

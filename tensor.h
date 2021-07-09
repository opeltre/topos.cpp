#include <iostream>
#include <functional> 
#include <string> 

using namespace std;

/*------ Tensor ------*/

template<typename Domain, typename T=dtype> 
struct Tensor : public Vect<Domain::size, T> {

    using Vect<Domain::size, T>::Vect;
    using shape = Domain;

    static constexpr size_t dim = Domain::dim;
    static constexpr size_t size = Domain::size;

    /* --- Access ---*/
    
    template<typename Index>
    T operator () (Index js[dim]) {
        return this->values[shape::index(js)];
    }
    T operator () (initializer_list<size_t> js) {
        return this->values[shape::index(js)];
    }

    template<typename ... Is> 
    using Indices = std::enable_if_t<
        sizeof...(Is) == dim 
        &&  (convertible_to<Is, size_t> && ...), bool
    >;

    template<typename ... Is, Indices<Is...> = true>
    T operator () (Is ... is) {
        size_t js [dim] = {static_cast<size_t>(is)...};
        return this->values[shape::index(js)];
    }

};

/*--- show ---*/

template <typename shape, typename T=dtype> 
string to_string (Tensor<shape,T> v) {
    size_t n = shape::size;
    string str = "Tensor " + to_string(shape::dim) + " [";
    for (size_t i = 0; i < n; i++) {
        str += to_string(v.values[i]);
        str += (i == n  - 1 ?  "]" : ", ");
    }
    return str;
}

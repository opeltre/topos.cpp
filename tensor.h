#include <iostream>
#include <functional> 
#include <string> 
#include <cstdarg>

using namespace std;

/*------ Tensor ------*/

template<typename shape, typename T=dtype> 
struct Tensor : public Vect<shape::size, T> {

    using Vect<shape::size, T>::Vect;

    static constexpr size_t dim = shape::dim;
    static constexpr size_t size = shape::size;

    T operator () (size_t js[dim]) {
        return this->values[shape::index(js)];
    }

    T operator () (size_t js...) {
        size_t is [dim];
        is[0] = js;
        va_list args;
        va_start(args, js);
        for (size_t d = 1; d < dim; d++) {
            size_t i_d = va_arg(args, size_t);
            is[d] = i_d;
        }
        va_end(args);
        return this->values[shape::index(is)];
    }

    T operator () (initializer_list<size_t> js) {
        size_t is [dim];
        copy(js.begin(), js.begin() + dim, is);
        return this->values[shape::index(is)];
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

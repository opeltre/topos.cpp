#include <iostream>
#include <functional> 
#include <string> 
#include <type_traits>
#include <cstdarg>

#include "vect.h"

using namespace std;

/*------ Shape ------*/

using int_ = const size_t &;

template<size_t... ns>
struct Shape {

    typedef size_t Index[0];

    enum {
        dim = 0, 
        size = 1
    };
};

template<size_t n, size_t... ns> 
struct Shape<n, ns...> {

    Shape () {}
    
    static constexpr size_t shape [1 + sizeof...(ns)] = {n, ns...};

    enum {
        dim = 1 + sizeof...(ns),
        size = n * Shape<ns...>::size
    };
    
    typedef size_t Index[dim];

    // row-major index
    static size_t index (const size_t js [dim]) {
        size_t i = js[0];
        for (size_t d = 1; d < dim; d++) {
            i = i * shape[d] + js[d];
        }
        return i;
    };
};

/*------ Tensor ------*/

template<typename shape, typename T=dtype> 
struct Tensor : public Vect<shape::size, T> {

    Tensor () {}

    Tensor (Vect<shape::size, T>& val) 
        {this->values = val.values;}

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


int main () {
    typedef Shape<3, 3, 3> X;
    Tensor<X> t;

    cout << "t.dim \t: "
        << t.dim << endl;
    cout << "t.size \t: "
        << t.size << endl;

    t.map([&] (double x, size_t i) {return (double)i / t.dim;});
    cout << "t \t: "
        << to_string(t) << endl;

    cout << "t(0, 2, 2)\t:"
        << t(0, 2, 2) << endl;

    cout << to_string(t + t) << endl;
    return 0;
}

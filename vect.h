#include <iostream>
#include <functional> 
#include <string> 

#include "alg.h"

using namespace std;

typedef double dtype;

template <size_t n, typename T=dtype> 
struct Vect {

    /* --- Constructors --- */

    Vect () {}

    Vect (T* val) : values(val) {}

    Vect (initializer_list<T> val) {
        allocate();
        copy(val.begin(), val.end(), values);
    }

    Vect (function<T(size_t)> f) {
        allocate();
        for (size_t i = 0; i < n; i++) {
            values[i] = f(i);
        }
    }

    T* values; 

    /* --- Memory --- */

    void allocate () {
        values = (T*)malloc(n * sizeof(T));
    }

    void operator~ () {
        free(values);
    }

    /* --- Access --- */ 

    T operator [] (size_t i) const {
        return values[i];
    }

    /* --- Iteration --- */ 

    Vect& forEach (function <void(T, size_t)> f) {
        for (size_t i = 0; i < n; i++) {
            f(values[i], i);
        }
        return *this;
    }

    Vect& fmap (function<T(T)> f) {
        for (size_t i = 0; i < n; i++) {
            values[i] = f(values[i]);
        }
        return *this;
    }

    Vect& map (function<T(T, size_t)> f) {
        for (size_t i = 0; i < n; i++) {
            values[i] = f(values[i], i);
        }
        return *this;
    }
    
    template <typename T2=T>
    Vect& zipWith (Vect<n, T2> b, function<T(T, T2)> f) {
        for (size_t i = 0; i < n; i++) {
            values[i] = f(values[i], b[i]);
        }
        return *this;
    }
};

/* ------ ranges ------ */

template <size_t n, typename T=dtype> 
Vect<n, T> range () {
    return Vect<n, T>([] (size_t i) {return i;});
}

template <size_t n, typename T=dtype>
Vect<n, T> linspace (T x0, T x1) {
    T step = (x1 - x0) / (n - 1);
    return Vect<n, T>([&] (size_t i) {return x0 + step * i;});
}

/* ------ fmap ------ */ 

template <size_t n, typename S=dtype, typename T=S>
using F_Vect = function<Vect<n, T> (Vect<n, S>)>;

template <size_t n, typename S=dtype, typename T=S>
F_Vect<n, S, T> fmap (function<T(S)> f) {
    return [&] (Vect<n, S> v) {
        return Vect<n, T> ([&] (size_t i) {return f(v[i]);});
    };
}

/* ------ zipWith ------ */

template <size_t n, typename S1=dtype, typename S2=S1, typename T=S1> 
using F2_Vect = function<Vect<n, T> (Vect<n, S1>, Vect<n, S2>)>;

template <size_t n, typename S1=dtype, typename S2=S1, typename T=S1> 
F2_Vect<n, S1, S2, T> zipWith (function<T(S1, S2)> f) {
    return [&] (Vect<n, S1> v1, Vect<n, S2> v2) {
        return Vect<n, T> ([&] (size_t i) {return f(v1[i], v2[i]);});
    };
}

/* ------ show ------ */ 

template <size_t n, typename T=dtype> 
string to_string (Vect<n,T> v) {
    string str = "Vect " + to_string(n) + " [";
    for (size_t i = 0; i < n; i++) {
        str += to_string(v.values[i]);
        str += (i == n  - 1 ?  "]" : ", ");
    }
    return str;
}

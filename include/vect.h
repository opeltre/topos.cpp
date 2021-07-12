#include <iostream>
#include <functional> 
#include <string> 
#include "string.h"

namespace topos{

template <index_t n, typename T=dtype> 
struct Vect {
    
    static constexpr index_t size = n;

    /* --- Constructors --- */

    Vect () {
        allocate();
        std::cout << "> allocating empty array" << std::endl;
    }

    Vect (std::initializer_list<T> val) {
        allocate();
        copy(val.begin(), val.end(), values);
    }

    Vect (std::function<T(index_t)> f) {
        std::cout << "> mapping" << std::endl;
        allocate();
        for (index_t i = 0; i < n; i++) {
            values[i] = f(i);
        }
    }

    T* values; 

    /* --- Move Constructor --- */

    Vect (Vect&& v) {
        values = v.values;
        v.values = nullptr;
        std::cout << "> moving" << std::endl;
    }
    Vect (Vect& v) {
        allocate();
        memcpy(values, v.values, n * sizeof(T));
        std::cout << "> copying" << std::endl;
    }

    /* --- Copy --- */
    Vect& operator= (Vect v) {
        std::cout << "> swapping" << std::endl;
        swap(values, v.values);
        return *this;
    }

    /* --- Memory --- */

    void allocate () {
        values = (T*)malloc(n * sizeof(T));
    }

    void operator~ () {
        free(values);
    }

    /* --- Access --- */ 

    T operator [] (index_t i) const {
        return values[i];
    }

    /* --- Iteration --- */ 

    Vect& forEach (std::function <void(T, index_t)> f) {
        for (index_t i = 0; i < n; i++) {
            f(values[i], i);
        }
        return *this;
    }

    Vect& fmap (std::function<T(T)> f) {
        for (index_t i = 0; i < n; i++) {
            values[i] = f(values[i]);
        }
        return *this;
    }

    Vect& map (std::function<T(T, index_t)> f) {
        for (index_t i = 0; i < n; i++) {
            values[i] = f(values[i], i);
        }
        return *this;
    }
    
    template <typename T2=T>
    Vect& zipWith (Vect<n, T2> b, std::function<T(T, T2)> f) {
        for (index_t i = 0; i < n; i++) {
            values[i] = f(values[i], b[i]);
        }
        return *this;
    }
};

/* ------ ranges ------ */

template <index_t n, typename T=dtype> 
Vect<n, T>& range () {
    return Vect<n, T>([] (index_t i) {return i;});
}

template <index_t n, typename T=dtype>
Vect<n, T>& linspace (T x0, T x1) {
    T step = (x1 - x0) / (n - 1);
    return Vect<n, T>([&] (index_t i) {return x0 + step * i;});
}

/* ------ fmap ------ */ 

template <index_t n, typename S=dtype, typename T=S>
using F_Vect = std::function<Vect<n, T> (const Vect<n, S>&)>;

template <index_t n, typename S=dtype, typename T=S>
F_Vect<n, S, T> fmap (std::function<T(S)> f) {
    return [&] (const Vect<n, S>& v) {
        return Vect<n, T> ([&] (index_t i) {return f(v[i]);});
    };
}

/* ------ zipWith ------ */

template <index_t n, typename S1=dtype, typename S2=S1, typename T=S1> 
using F2_Vect = 
    std::function<Vect<n, T> (const Vect<n, S1>&, const Vect<n, S2>&)>;

template <index_t n, typename S1=dtype, typename S2=S1, typename T=S1> 
F2_Vect<n, S1, S2, T> zipWith (std::function<T(S1, S2)> f) {
    return [&] (const Vect<n, S1>& v1, const Vect<n, S2>& v2) {
        return Vect<n, T> ([&] (index_t i) {return f(v1[i], v2[i]);});
    };
}

/* ------ show ------ */ 

template <index_t n, typename T=dtype> 
std::string to_string (const Vect<n,T>& v) {
    return "Vect " + std::to_string(n) + " " + _str(v);
}

}//topos

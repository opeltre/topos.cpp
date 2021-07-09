#include <iostream>
#include <functional> 
#include <string> 
#include "string.h"

using namespace std;

typedef double dtype;

template <size_t n, typename T=dtype> 
struct Vect {
    
    static constexpr size_t size = n;

    /* --- Constructors --- */

    Vect () {
        allocate();
        cout << "> allocating empty array" << endl;
    }

    Vect (initializer_list<T> val) {
        allocate();
        copy(val.begin(), val.end(), values);
    }

    Vect (function<T(size_t)> f) {
        cout << "> mapping" << endl;
        allocate();
        for (size_t i = 0; i < n; i++) {
            values[i] = f(i);
        }
    }

    T* values; 

    /* --- Move Constructor --- */

    Vect (Vect&& v) {
        values = v.values;
        v.values = nullptr;
        cout << "> moving" << endl;
    }
    Vect (Vect& v) {
        allocate();
        memcpy(values, v.values, n * sizeof(T));
        cout << "> copying" << endl;
    }

    /* --- Copy --- */
    Vect& operator= (Vect v) {
        cout << "> swapping" << endl;
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
Vect<n, T>& range () {
    return Vect<n, T>([] (size_t i) {return i;});
}

template <size_t n, typename T=dtype>
Vect<n, T>& linspace (T x0, T x1) {
    T step = (x1 - x0) / (n - 1);
    return Vect<n, T>([&] (size_t i) {return x0 + step * i;});
}

/* ------ fmap ------ */ 

template <size_t n, typename S=dtype, typename T=S>
using F_Vect = function<Vect<n, T> (const Vect<n, S>&)>;

template <size_t n, typename S=dtype, typename T=S>
F_Vect<n, S, T> fmap (function<T(S)> f) {
    return [&] (const Vect<n, S>& v) {
        return Vect<n, T> ([&] (size_t i) {return f(v[i]);});
    };
}

/* ------ zipWith ------ */

template <size_t n, typename S1=dtype, typename S2=S1, typename T=S1> 
using F2_Vect = 
    function<Vect<n, T> (const Vect<n, S1>&, const Vect<n, S2>&)>;

template <size_t n, typename S1=dtype, typename S2=S1, typename T=S1> 
F2_Vect<n, S1, S2, T> zipWith (function<T(S1, S2)> f) {
    return [&] (const Vect<n, S1>& v1, const Vect<n, S2>& v2) {
        return Vect<n, T> ([&] (size_t i) {return f(v1[i], v2[i]);});
    };
}

/* ------ show ------ */ 

template <size_t n, typename T=dtype> 
string to_string (const Vect<n,T>& v) {
    return "Vect " + to_string(n) + " " + _str(v);
}

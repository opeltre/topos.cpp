#include <iostream>
#include <functional> 
#include <string> 

using namespace std;

typedef double dtype;

template <size_t n, typename T=dtype> 
struct Vect {
    
    using type = Vect<n, T>;

    /* --- Constructors --- */

    Vect () {}

    Vect (T& val) : values(val) {}

    Vect (initializer_list<T> val) {
        copy(val.begin(), val.end(), values);
    }

    Vect (function<T(size_t)> f) {
        for (size_t i = 0; i < n; i++) {
            values[i] = f(i);
        }
    }
    
    T values [n];
  
    /* --- Access --- */ 

    T& operator [] (size_t i) {
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
    
    template <typename T2>
    Vect& zipWith (Vect<n, T2> b, function<T(T, T2)> f) {
        for (size_t i = 0; i < n; i++) {
            values[i] = f(values[i], b[i]);
        }
        return *this;
    }

    /* --- Arithmetic --- */
   
    //      +       //

    // in place
    Vect& operator += (Vect& b) {
        return zipWith<T>(b, [&] (T ai, T bi) {return ai + bi;});
    }
    Vect& operator += (T b) {
        return fmap([&] (T ai) {return ai + b;});
    }
    // pure
    Vect operator + (Vect& b) {
        return Vect([&] (size_t i) {return values[i] + b[i];});
    }
    Vect operator + (T b) {
        return Vect([&] (size_t i) {return values[i] + b;});
    }

    //      -       // 

    // in place
    Vect& operator -= (Vect& b) {
        return zipWith<T>(b, [&] (T ai, T bi) {return ai - bi;});
    }
    Vect& operator -= (T b) {
        return fmap([&] (T ai) {return ai - b;});
    }
    // pure
    Vect operator - (Vect& b) const {
        return Vect([&] (size_t i) {return values[i] - b[i];});
    }
    Vect operator - (T b) const {
        return Vect([&] (size_t i) {return values[i] - b;});
    }
    Vect operator - () const {
        return Vect([&] (size_t i) {return -values[i];});
    }

    //      *       //
    
    // in place
    Vect& operator *= (Vect& b) {
        return zipWith<T>(b, [&] (T ai, T bi) {return ai * bi;});
    }
    Vect& operator *= (T b) {
        return fmap([&] (T ai) {return ai * b;});
    }

    // pure
    Vect operator * (Vect&& b) const {
        return Vect([&] (size_t i) {return values[i] * b[i];});
    }
    Vect operator * (T b) const {
        return Vect([&] (size_t i) {return values[i] * b;});
    }

    //      /       // 

    // in place
    Vect& operator /= (Vect& b) {
        return zipWith<T>(b, [&] (T ai, T bi) {return ai / bi;});
    }
    Vect& operator /= (T b) {
        return fmap([&] (T ai) {return ai / b;});
    }
    // pure
    Vect operator / (Vect& b) const {
        return Vect([&] (size_t i) {return values[i] / b[i];});
    }
    Vect operator / (T b) const {
        return Vect([&] (size_t i) {return values[i] / b;});
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
    F_Vect<n, S, T> F; 
    F = [&] (Vect<n, S> v) {
        Vect<n, T> Fv;
        for (size_t i = 0; i < n; i++) {
            Fv[i] = f(v[i]);
        }
        return Fv;
    };
    return F;
}

/* ------ zipWith ------ */

template <size_t n, typename S1=dtype, typename S2=S1, typename T=S1> 
using F2_Vect = function<Vect<n, T> (Vect<n, S1>, Vect<n, S2>)>;

template <size_t n, typename S1=dtype, typename S2=S1, typename T=S1> 
F2_Vect<n, S1, S2, T> zipWith (function<T(S1, S2)> f) {
    F2_Vect<n, S1, S2, T> F;
    F = [&] (Vect<n, S1> v1, Vect<n, S2> v2) {
        Vect<n, T> Fv; 
        for (size_t i = 0; i < n; i++) {
            Fv.values[i] = f(v1.values[i], v2.values[i]);
        }
        return Fv;
    };
    return F;
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

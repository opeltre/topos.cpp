#include <iostream>
#include <string>
#include "main.h"

using namespace std;

int main () {

    const int n=10;
    typedef double _t;

    cout << "Examples in Vect<6>:" << endl;

    Vect<n> u ([&] (size_t i) {return (_t)i / (_t)n;});
    //Vect<n> u = linspace<n>(0.0, 1.0);
    log("u = linspace<n>(0, 1)", u); 

    // f = (*n) 
    function<_t(_t)> f = 
        [] (_t x) {return 3 * x;};
    
    // in-place map
    u.fmap(f);
    log("u.fmap(*3)", u);

    // pure map 
    Vect<n> v = fmap<n>(f)(u); 
    log("v = fmap(*3)(u)", v);

    // addition 
    function<_t(_t, _t)> add = 
        [] (_t x, _t y) {return x + y;};

    Vect<n> sum = zipWith<n>(add)(u, v);
    log("s = zipWith(+)(u, v)", sum);

    u += v;
    log("u += v", u);
   
    Vect<n> w = (u - 2) * (1.0 + v); 
    log("w = (-u + 2) * (1 + v)", w);

    w /= 100;
    log("w /= 100", w);

    log("- w", -w);
    
    Vect<n> sum2 = u + w;
    log("u+w", sum2);

    // TENSORS // 
    
    cout << "Tensors:" << endl << endl;

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
    
    cout << "t + t\t:"  
        << to_string(t + t) << endl;

    return 0;
}

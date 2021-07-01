#include <iostream>
#include <string>
#include "vect.cpp"

using namespace std;

template<typename Value>
Value& log (string s, Value& v) {
    cout    << endl
            << s << endl 
            << to_string(v) << endl << endl;
    return v;
}

int main () {

    const int n=10;
    typedef double _t;

    cout << "Examples in Vect<6>:" << endl;

    Vect<n> u = linspace<n>(0.0, 1.0);
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
   
    Vect<n> w = (-u + 2) * (v + 1); 
    log("w = (-u + 2) * (v + 1)", w);

    w /= 100;
    log("w /= 100", w);

    return 0;
}

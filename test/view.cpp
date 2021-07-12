#include <iostream>
#include <string>
#include "topos.h"

using namespace std;
using namespace topos;

int main () {

    typedef Shape<3, 3> D;

    cout << "Examples in View (3, 3):" << endl;

    View <D> v ([&] (size_t i) { return i * i; });
    log("v = View (3,3) \\i => i * i", v);

    View <D> s = v + v;
    log("s = v + v", s);

    Items<View<D>> sum_v = sum(v); 
    log("sum v", sum_v);
};

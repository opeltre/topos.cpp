# topos 

C++ implementation of the topos library for tensor algebra 
and tensor networks. 

Tensors are statically typed with shape prescribed at compile time.

## Usage 

```cpp
 
# include "main.h"

int main () {
    
    typedef Shape<3, 3> X;
    
    Tensor<X, int> t 
        ([&] (size_t i) {return i;});

    //--- Equivalent to `t = t * t - 1`: ---

    std::function<int(int)> f = 
        ([&] (int p) {return p * p - 1;});

    t.fmap(f);  // Use fmap(f)(t) for the pure operation

    cout << t << endl;

    //--- Equivalent to `s = sum(t)`: ---

    int s = foldl([&] (int ai, int bi) {return ai + bi;})(v);

    cout << s << endl;

    return 0;
}
``` 

    
    
    
    

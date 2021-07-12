# topos 

C++ implementation of the topos library for tensor algebra 
and tensor networks (in progress).

Tensors are statically typed with shape prescribed at compile time.

The library is header only, include `topos.h` with the include directory
available to import the namespace. 

Build and run tests with `$ make test`.
 
**Example:**

```cpp
 
# include "topos.h"

int main () {
    
    typedef topos::Shape<3, 3> X;
    typedef topos::Tensor<X, int> Tensor_X;
    
    Tensor_X t ([&] (size_t i) {return i;});
    Tensor_X s = t * t - 1;

    std::cout << topos::sum(t2) << std::endl;
}
``` 

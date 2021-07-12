#include <cstdarg>
#include <type_traits>

namespace topos {

template<index_t... ns>
struct Shape {

    typedef index_t Index[0];

    enum {
        dim = 0, 
        size = 1
    };
};

template<index_t n, size_t... ns> 
struct Shape<n, ns...> {

    Shape () {}
    
    static constexpr index_t shape [1 + sizeof...(ns)] = {n, ns...};

    enum {
        dim = 1 + sizeof...(ns),
        size = n * Shape<ns...>::size
    };
    
    typedef index_t Index[dim];

    //--  Row-major index --
    
    template<std::unsigned_integral Nat=index_t> 
    static index_t index (const Nat js [dim]) {
        index_t i = js[0];
        for (index_t d = 1; d < dim; d++) {
            i = i * shape[d] + js[d];
        }
        if ( i > size ) 
            throw std::invalid_argument(
                    "out of bounds: " + std::to_string(i));
        return i;
    };

    static index_t index (std::initializer_list<size_t> js) {
        index_t is [dim];
        copy(js.begin(), js.begin() + dim, is);
        return index(is);
    }

    static std::string show() {
        std::string str = "(";
        for (index_t i = 0; i < dim; i ++) {
            str += std::to_string(shape[i]) 
                + (i < dim - 1? ", ": ")");
        }
        return str;
    }

};

template<typename shape, typename ... Is> 
using Indices = std::enable_if_t<
    sizeof...(Is) == shape::dim 
    &&  (std::convertible_to<Is, index_t> && ...), bool
>;

/*
template<typename T> 
concept MultiDim = requires (T t) {
    requires Vector<T>;
    { t.dim }           -> same_as<index_t>;
    { t.shape };
};
*/

}//topos

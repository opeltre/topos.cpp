#include <cstdarg>
#include <type_traits>

template<size_t... ns>
struct Shape {

    typedef size_t Index[0];

    enum {
        dim = 0, 
        size = 1
    };
};

template<size_t n, size_t... ns> 
struct Shape<n, ns...> {

    Shape () {}
    
    static constexpr size_t shape [1 + sizeof...(ns)] = {n, ns...};

    enum {
        dim = 1 + sizeof...(ns),
        size = n * Shape<ns...>::size
    };
    
    typedef size_t Index[dim];

    //--  Row-major index --
    
    template<unsigned_integral Nat=size_t> 
    static size_t index (const Nat js [dim]) {
        size_t i = js[0];
        for (size_t d = 1; d < dim; d++) {
            i = i * shape[d] + js[d];
        }
        if ( i > size ) 
            throw invalid_argument("out of bounds: " + to_string(i));
        return i;
    };

    static size_t index (initializer_list<size_t> js) {
        size_t is [dim];
        copy(js.begin(), js.begin() + dim, is);
        return index(is);
    }

    static string show() {
        string str = "(";
        for (size_t i = 0; i < dim; i ++) {
            str += to_string(shape[i]) 
                + (i < dim - 1? ", ": ")");
        }
        return str;
    }

};

template<typename shape, typename ... Is> 
using Indices = std::enable_if_t<
    sizeof...(Is) == shape::dim 
    &&  (convertible_to<Is, size_t> && ...), bool
>;

/*
template<typename T> 
concept MultiDim = requires (T t) {
    requires Vector<T>;
    { t.dim }           -> same_as<size_t>;
    { t.shape };
};
*/

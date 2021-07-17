#include <tuple>

namespace topos {

template <typename S>
concept ShapeN = requires (S s) {
    { S::dim }      -> std::convertible_to<index_t>;
    { S::size }     -> std::convertible_to<index_t>;
    { S::shape }    -> std::convertible_to<index_t[S::dim]>;
};

//--- N-ary indices ---
//
// Template constraint on n-ary index packs (i0, ..., iN) 
//
//      template<typename ... Is, Indices<shape, Is...> = true>
//      T operator (Is ... is) { //impl }

template<ShapeN S, typename... Is> 
using Indices = std::enable_if_t<
    sizeof...(Is) == S::dim 
    &&  (std::convertible_to<Is, index_t> && ...), 
bool>;

//--- Row-major Index ---

template <index_t dim>
index_t row_major (const index_t shape [dim], const index_t js [dim]) {
    index_t i = js[0];
    for (index_t d = 1; d < dim; d++) {
        i = i * shape[d] + js[d];
    };
    return i;
};

//--- Shape Types ---

template<index_t... ns>
struct Shape {
    
    static constexpr index_t dim = 0;
    static constexpr index_t size = 1;
    static constexpr index_t shape [] = {}; 

    typedef index_t Point[0];
   
    static std::string show() {
        return "()";
    }

};

template<index_t n, index_t... ns> 
struct Shape<n, ns...> {

    static constexpr index_t dim    = 1 + sizeof...(ns);
    static constexpr index_t size   = (n  * ... * ns);
    static constexpr index_t shape [dim] = {n, ns...};
    
    typedef index_t Point[dim];
    
    using sliced = Shape<ns...>;

    //--  Row-major index --
    
    static index_t index (size_t js [dim]) {
        return row_major<dim>(shape, js);
    };

    static index_t index (std::initializer_list<size_t> js) {
        index_t is [dim];
        std::copy(js.begin(), js.begin() + dim, is);
        return row_major<dim>(shape, is);
    };

    //-- Show --
    static std::string show() {
        std::string str = "(";
        for (index_t i = 0; i < dim; i ++) {
            str += std::to_string(shape[i]) 
                + (i < dim - 1? ", ": ")");
        }
        return str;
    }
};

}//topos

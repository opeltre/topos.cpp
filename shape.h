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

    // row-major index
    static size_t index (const size_t js [dim]) {
        size_t i = js[0];
        for (size_t d = 1; d < dim; d++) {
            i = i * shape[d] + js[d];
        }
        return i;
    };
};


template<typename Domain, typename T=dtype>
struct View {

    using shape = Domain;
    static constexpr size_t dim = shape::dim;
    static constexpr size_t size = shape::size;

    /*--- Constructor ---*/

    View (function<T(size_t)> f) :
        read (f) {}
    
    function<T(size_t)> read;

    /*--- Access ---*/

    T operator [] (size_t i) const {
        return read(i);
    };

    /*--- n-ary Indices ---*/

    template<typename ... Is, Indices<shape, Is...> = true>
    T operator () (Is ... is) {
        size_t js [dim] = {static_cast<size_t>(is)...};
        return this[shape::index(js)];
    }
    template<typename Index>
    T operator () (Index js[dim]) {
        return this[shape::index(js)];
    }
    T operator () (initializer_list<size_t> js) {
        return this[shape::index(js)];
    }
};

template <typename shape, typename T=dtype> 
string to_string (const View<shape,T>& v) {
    return "View " + shape::show() + " " + _str(v);
}

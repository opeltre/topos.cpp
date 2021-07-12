namespace topos {

template<typename Domain, typename T=dtype>
struct View {

    using shape = Domain;
    static constexpr index_t dim = shape::dim;
    static constexpr index_t size = shape::size;

    /*--- Constructor ---*/

    View (std::function<T(index_t)> f) :
        read (f) {}
    
    std::function<T(index_t)> read;

    /*--- Access ---*/

    T operator [] (index_t i) const {
        return read(i);
    };

    /*--- n-ary Indices ---*/

    template<typename ... Is, Indices<shape, Is...> = true>
    T operator () (Is ... is) {
        index_t js [dim] = {static_cast<index_t>(is)...};
        return this[shape::index(js)];
    }
    template<typename Index>
    T operator () (Index js[dim]) {
        return this[shape::index(js)];
    }
    T operator () (std::initializer_list<index_t> js) {
        return this[shape::index(js)];
    }
};

template <typename shape, typename T=dtype> 
std::string to_string (const View<shape,T>& v) {
    return "View " + shape::show() + " " + _str(v);
}

}//topos

template<size_t n, typename T=dtype>  
struct View {
    
    static constexpr size_t size = n;

    View (function<T(size_t)> f) :
        read (f) {}
    
    function<T(size_t)> read;


    T operator [] (size_t i) const {
        return read(i);
    };
};

template <size_t n, typename T=dtype> 
string to_string (const View<n,T>& v) {
    return "View " + to_string(n) + " " + _str(v);
}

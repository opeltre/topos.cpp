namespace topos {

/*------ Tensor views ------ 

  Tensor views behave like ordinary as tensors for value access,
  except `view[i]` makes a call to `view.read(i)`. 

  A view is created with the functional constructor 
  `View(std::function<T(std::size_t)>)`, except the
  reader function will not be called at creation time
  but instead may hold a capture of other tensor elements.  


  Because they behave like tensors, they are part of
  the `Vector` concept and inherit the same arithmetic 
  and functional operations. 
*/

//--- Vector instance ---

template <index_t n, typename T=dtype>
struct View1D {

    static constexpr index_t size = n;

    /*--- Constructor ---*/

    View1D (std::function<T(index_t)> f) 
        : read (f) {}
    
    template <Vector V>
    View1D (const V& v) 
        : read ([&] (index_t i) {return v[i];}) {}
    
    std::function<T(index_t)> read;

    /*--- Access ---*/

    T operator [] (index_t i) const {
        return read(i);
    };
};

//--- MultiDim instance ---

template<typename S, typename T=dtype>
using View = MultiDim<S, T, View1D>;

template <typename shape, typename T=dtype> 
std::string to_string (const View<shape,T>& v) {
    return "View " + shape::show() + " " + _str(v);
}

}//topos

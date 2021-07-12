namespace topos{

template <Vector V> 
std::function<void(const V&)> forEach (std::function <void(Items<V>, index_t i)>) {
    return [&] (const V& v) {
        for (index_t i = 0; i < v.size; i ++) {
            f(v[i], i);
        }
    };
};

template <typename Acc, Vector V> 
std::function<Acc(Acc, const V&)> foldl (std::function<Acc(Acc, Items<V>)> f) {
    return [&] (Acc acc, const V& v) {
        for (index_t i = 0; i < v.size; i ++) {
            acc = f(acc, v[i]);
        }
        return acc;
    };
};

template <Vector V> 
Items<V> sum (const V& v) {
   return foldl<Items<V>, V>
       ([] (Items<V> ai, Items<V> bi) {return ai + bi;})
       (0, v);
}

}//topos

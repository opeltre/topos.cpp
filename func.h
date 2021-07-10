template <Vector V> 
function<void(const V&)> forEach (function <void(Items<V>, size_t i)>) {
    return [&] (const V& v) {
        for (size_t i = 0; i < v.size; i ++) {
            f(v[i], i);
        }
    };
};

template <typename Acc, Vector V> 
function<Acc(Acc, const V&)> foldl (function<Acc(Acc, Items<V>)> f) {
    return [&] (Acc acc, const V& v) {
        for (size_t i = 0; i < v.size; i ++) {
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

#include <iostream>
#include <string>

template<typename Value>
const Value& log (string s, const Value& v) {
    cout    << endl
            << s << endl 
            << to_string(v) << endl << endl;
    return v;
};

template <Vector V>
string _str (const V& v) {
    size_t n = v.size;
    string str = "["; 
    for (size_t i = 0; i < n; i++) {
        str += to_string(v[i]);
        str += (i == n - 1 ?  "]" : ", ");
    }
    return str;
}

template <Vector V> 
ostream& operator << (ostream& os, const V& v) {
    return os << to_string(v);
}

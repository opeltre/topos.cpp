#include <iostream>
#include <string>

namespace topos {

template <Vector V> 
std::string to_string (const V& v);

template<typename Value>
const Value& log (std::string s, const Value& v) {
    std::cout    << std::endl
                << s << std::endl 
                << v << std::endl << std::endl;
    return v;
};

template <Vector V>
std::string _str (const V& v) {
    index_t n = v.size;
    std::string str = "["; 
    for (size_t i = 0; i < n; i++) {
        str += std::to_string(v[i]);
        str += (i == n - 1 ?  "]" : ", ");
    }
    return str;
}

template <Vector V> 
std::ostream& operator << (std::ostream& os, const V& v) {
    return os << to_string(v);
}

}//topos

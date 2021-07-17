#include <ostream>
#include <array>

#include "topos.h"

template <size_t N, typename T=size_t>
using Array = std::array<T, N>;

template<typename Seq, typename Arr, Arr ns>
struct Slice_impl;

template<size_t ... is, 
    size_t N, typename T, Array<N, T> ns>
struct Slice_impl<std::index_sequence<is...>, Array<N, T>, ns> {
    using shape = topos::Shape<ns.at(is)...>;
};

template<size_t N, typename T, Array<N, T> ns>
using Slice = 
    Slice_impl<std::make_index_sequence<N>, Array<N, T>, ns>::shape;


int main () {

    constexpr std::array<size_t, 2> ns {3, 3};
    constexpr Array<2, size_t> ms = ns;

    using shape = Slice<2, size_t, ms>;

    std::cout << shape::show() << std::endl;
    
    return 0;
}

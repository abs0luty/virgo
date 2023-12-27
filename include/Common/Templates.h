#ifndef VIRGO_TEMPLATES_H
#define VIRGO_TEMPLATES_H

#include <type_traits>

namespace virgo::common {
// https://stackoverflow.com/a/30848101
#if __GNUC__ < 5 && ! defined __clang__
    // https://stackoverflow.com/a/28967049/1353549
    template <typename...>
    struct voider
    {
        using type = void;
    };
    template <typename...Ts>
    using void_t = typename voider<Ts...>::type;
#else
    template <typename...>
using void_t = void;
#endif

    template<class, template<class> class, class = void_t<>>
    struct IsDetected : std::false_type {
    };

    template<class T, template<class> class C>
    struct IsDetected<T, C, void_t<C<T>>> : std::true_type {
    };

    template <class T>
    using Assign = decltype(std::declval<T&>() == std::declval<const T&>());

    template <class T>
    using Assignable = IsDetected<T, Assign>;
}

#endif //VIRGO_TEMPLATES_H

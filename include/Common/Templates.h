#ifndef VIRGO_TEMPLATES_H
#define VIRGO_TEMPLATES_H

#include <type_traits>

namespace virgo::common {
    template<class, template<class> class, class = std::void_t<>>
    struct IsDetected : std::false_type {
    };

    template<class T, template<class> class C>
    struct IsDetected<T, C, std::void_t<C<T>>> : std::true_type {
    };
}

#endif //VIRGO_TEMPLATES_H

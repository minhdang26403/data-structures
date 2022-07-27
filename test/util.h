#ifndef UTIL_H_
#define UTIL_H_

#include <iostream>

#include "vector.h"

template<typename Type>
std::ostream& operator<<(std::ostream& s, const ds::Vector<Type>& v) {
    s.put('[');
    char comma[3] = {'\0', ' ', '\0'};
    for (uint32_t i = 0; i < v.Size(); ++i) {
        s << comma << v[i];
        comma[0] = ',';
    }
    return s << ']';
}

constexpr int MAX_ELEMENTS = 10;

#endif // UTIL_H_
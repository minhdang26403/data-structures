#ifndef CONCEPTS_H_
#define CONCEPTS_H_

#include <concepts>

namespace stl {
template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;
}

#endif // CONCEPTS_H_
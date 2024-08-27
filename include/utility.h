#ifndef UTILITY_H_
#define UTILITY_H_

#include "type_traits.h"

namespace stl {

// Use `remove_reference_t<T>` to force user to specify template type parameter
// when using forward since compiler cannot deduce type of `T` with
// `remove_reference_t<T>`
template <typename T>
constexpr T&& forward(remove_reference_t<T>& t) noexcept {
  return static_cast<T&&>(t);
}

template <typename T>
constexpr T&& forward(remove_reference_t<T>&& t) noexcept {
  static_assert(is_lvalue_reference_v<T>,
                "cannot forward an rvalue as an lvalue");
  return static_cast<T&&>(t);
}

template <typename T>
constexpr remove_reference_t<T>&& move(T&& t) noexcept {
  return static_cast<remove_reference_t<T>&&>(t);
}

};  // namespace stl

#endif  // UTILITY_H_

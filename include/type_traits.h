#ifndef TYPE_TRAITS_H_
#define TYPE_TRAITS_H_

#include <utility>

namespace stl {

using nullptr_t = decltype(nullptr);
using size_t = decltype(sizeof(unsigned int));
using ptrdiff_t = decltype(sizeof(long long));

/*============================================================
==========================Declaration=========================
=============================================================*/

/*========================Base classes=======================*/

// integral_constant
template <typename T, T v> struct integral_constant {
  static constexpr T value = v;
  using value_type = T;
  using type = integral_constant; // injected class name

  constexpr operator value_type() const noexcept { return v; }
  constexpr value_type operator()() const noexcept { return v; }
};

// bool_constant
template <bool B> using bool_constant = integral_constant<bool, B>;

using true_type = bool_constant<true>;
using false_type = bool_constant<false>;

/*============================================================
========================Type property=========================
==============================================================*/

/*===================Primary type categories==================*/

// is_void
template <typename T> struct is_void;
template <typename T> inline constexpr bool is_void_v = is_void<T>::value;

// is_null_pointer
template <typename T> struct is_null_pointer;
template <typename T>
inline constexpr bool is_null_pointer_v = is_null_pointer<T>::value;

// is_integral
template <typename T> struct is_integral;
template <typename T>
inline constexpr bool is_integral_v = is_integral<T>::value;

// is_floating_point
template <typename T> struct is_floating_point;
template <typename T>
inline constexpr bool is_floating_point_v = is_floating_point<T>::value;

// is_array
template <typename T> struct is_array;
template <typename T> inline constexpr bool is_array_v = is_array<T>::value;

// is_enum
template <typename T> struct is_enum;
template <typename T> inline constexpr bool is_enum_v = is_enum<T>::value;

// is_union
template <typename T> struct is_union;
template <typename T> inline constexpr bool is_union_v = is_union<T>::value;

// is_class
template <typename T> struct is_class;
template <typename T> inline constexpr bool is_class_v = is_class<T>::value;

// is_function
template <typename T> struct is_function;
template <typename T>
inline constexpr bool is_function_v = is_function<T>::value;

// is_pointer
template <typename T> struct is_pointer;
template <typename T> inline constexpr bool is_pointer_v = is_pointer<T>::value;

// is_lvalue_reference
template <typename T> struct is_lvalue_reference;
template <typename T>
inline constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;

// is_rvalue_reference
template <typename T> struct is_rvalue_reference;
template <typename T>
inline constexpr bool is_rvalue_reference_v = is_rvalue_reference<T>::value;

// is_member_object_pointer
template <typename T> struct is_member_object_pointer;
template <typename T>
inline constexpr bool is_member_object_pointer_v =
    is_member_object_pointer<T>::value;

// is_member_function_pointer
template <typename T> struct is_member_function_pointer;
template <typename T>
inline constexpr bool is_member_function_pointer_v =
    is_member_function_pointer<T>::value;

/*==================Composite type categories=================*/

// is_fundamental
template <typename T> struct is_fundamental;
template <typename T>
inline constexpr bool is_fundamental_v = is_fundamental<T>::value;

// is_arithmetic
template <typename T> struct is_arithmetic;
template <typename T>
inline constexpr bool is_arithmetic_v = is_arithmetic<T>::value;

// is_scalar
template <typename T> struct is_scalar;
template <typename T> inline constexpr bool is_scalar_v = is_scalar<T>::value;

// is_object
template <typename T> struct is_object;
template <typename T> inline constexpr bool is_object_v = is_object<T>::value;

// is_compound
template <typename T> struct is_compound;
template <typename T>
inline constexpr bool is_compound_v = is_compound<T>::value;

// is_reference
template <typename T> struct is_reference;
template <typename T>
inline constexpr bool is_reference_v = is_reference<T>::value;

// is_member_pointer
template <typename T> struct is_member_pointer;
template <typename T>
inline constexpr bool is_member_pointer_v = is_member_pointer<T>::value;

/*=======================Type properties======================*/

// is_const
template <typename T> struct is_const;
template <typename T> inline constexpr bool is_const_v = is_const<T>::value;

// is_volatile
template <typename T> struct is_volatile;
template <typename T>
inline constexpr bool is_volatile_v = is_volatile<T>::value;

// is_trivial
template <typename T> struct is_trivial;
template <typename T> inline constexpr bool is_trivial_v = is_trivial<T>::value;

// is_trivially_copyable
template <typename T> struct is_trivially_copyable;
template <typename T>
inline constexpr bool is_trivially_copyable_v = is_trivially_copyable<T>::value;

// is_standard_layout
template <typename T> struct is_standard_layout;
template <typename T>
inline constexpr bool is_standard_layout_v = is_standard_layout<T>::value;

// is_pod
template <typename T> struct is_pod;
template <typename T> inline constexpr bool is_pod_v = is_pod<T>::value;

// is_empty
template <typename T> struct is_empty;
template <typename T> inline constexpr bool is_empty_v = is_empty<T>::value;

// is_polymorphic
template <typename T> struct is_polymorphic;
template <typename T>
inline constexpr bool is_polymorphic_v = is_polymorphic<T>::value;

// is_abstract
template <typename T> struct is_abstract;
template <typename T>
inline constexpr bool is_abstract_v = is_abstract<T>::value;

// is_final
template <typename T> struct is_final;
template <typename T> inline constexpr bool is_final_v = is_final<T>::value;

// is_aggregate
template <typename T> struct is_aggregate;
template <typename T>
inline constexpr bool is_aggregate_v = is_aggregate<T>::value;

// is_signed
template <typename T> struct is_signed;
template <typename T> inline constexpr bool is_signed_v = is_signed<T>::value;

// is_unsigned
template <typename T> struct is_unsigned;
template <typename T>
inline constexpr bool is_unsigned_v = is_unsigned<T>::value;

// is_bounded_array
template <typename T> struct is_bounded_array;
template <typename T>
inline constexpr bool is_bounded_array_v = is_bounded_array<T>::value;

// is_unbounded_array
template <typename T> struct is_unbounded_array;
template <typename T>
inline constexpr bool is_unbounded_array_v = is_unbounded_array<T>::value;

/*====================Supported operations====================*/

// is_constructible
template <typename T, typename... Args> struct is_constructible;
template <typename T, typename... Args>
inline constexpr bool is_constructible_v = is_constructible<T, Args...>::value;

// is_trivially_constructible
template <typename T, typename... Args> struct is_trivially_constructible;
template <typename T, typename... Args>
inline constexpr bool is_trivially_constructible_v =
    is_trivially_constructible<T, Args...>::value;

// is_nothrow_constructible
template <typename T, typename... Args> struct is_nothrow_constructible;
template <typename T, typename... Args>
inline constexpr bool is_nothrow_constructible_v =
    is_nothrow_constructible<T, Args...>::value;

// is_default_constructible
template <typename T> struct is_default_constructible;
template <typename T>
inline constexpr bool is_default_constructible_v =
    is_default_constructible<T>::value;

// is_trivially_default_constructible,
template <typename T> struct is_trivially_default_constructible;
template <typename T>
inline constexpr bool is_trivially_default_constructible_v =
    is_trivially_default_constructible<T>::value;

// is_nothrow_default_constructible
template <typename T> struct is_nothrow_default_constructible;
template <typename T>
inline constexpr bool is_nothrow_default_constructible_v =
    is_nothrow_default_constructible<T>::value;

// is_copy_constructible
template <typename T> struct is_copy_constructible;
template <typename T>
inline constexpr bool is_copy_constructible_v = is_copy_constructible<T>::value;

// is_trivially_copy_constructible
template <typename T> struct is_trivially_copy_constructible;
template <typename T>
inline constexpr bool is_trivially_copy_constructible_v =
    is_trivially_copy_constructible<T>::value;

// is_nothrow_copy_constructible
template <typename T> struct is_nothrow_copy_constructible;
template <typename T>
inline constexpr bool is_nothrow_copy_constructible_v =
    is_nothrow_copy_constructible<T>::value;

// is_move_constructible
template <typename T> struct is_move_constructible;
template <typename T>
inline constexpr bool is_move_constructible_v = is_move_constructible<T>::value;

// is_trivially_move_constructible
template <typename T> struct is_trivially_move_constructible;
template <typename T>
inline constexpr bool is_trivially_move_constructible_v =
    is_trivially_move_constructible<T>::value;

// is_nothrow_move_constructible
template <typename T> struct is_nothrow_move_constructible;
template <typename T>
inline constexpr bool is_nothrow_move_constructible_v =
    is_nothrow_move_constructible<T>::value;

// is_assignable
template <typename T, typename U> struct is_assignable;
template <typename T, typename U>
inline constexpr bool is_assignable_v = is_assignable<T, U>::value;

// is_trivially_assignable
template <typename T, typename U> struct is_trivially_assignable;
template <typename T, typename U>
inline constexpr bool is_trivially_assignable_v =
    is_trivially_assignable<T, U>::value;

// is_nothrow_assignable
template <typename T, typename U> struct is_nothrow_assignable;
template <typename T, typename U>
inline constexpr bool is_nothrow_assignable_v =
    is_nothrow_assignable<T, U>::value;

// is_copy_assignable
template <typename T> struct is_copy_assignable;
template <typename T>
inline constexpr bool is_copy_assignable_v = is_copy_assignable<T>::value;

// is_trivially_copy_assignable
template <typename T> struct is_trivially_copy_assignable;
template <typename T>
inline constexpr bool is_trivially_copy_assignable_v =
    is_trivially_copy_assignable<T>::value;

// is_nothrow_copy_assignable
template <typename T> struct is_nothrow_copy_assignable;
template <typename T>
inline constexpr bool is_nothrow_copy_assignable_v =
    is_nothrow_copy_assignable<T>::value;

// is_move_assignable
template <typename T> struct is_move_assignable;
template <typename T>
inline constexpr bool is_move_assignable_v = is_move_assignable<T>::value;

// is_trivially_move_assignable
template <typename T> struct is_trivially_move_assignable;
template <typename T>
inline constexpr bool is_trivially_move_assignable_v =
    is_trivially_move_assignable<T>::value;

// is_nothrow_move_assignable
template <typename T> struct is_nothrow_move_assignable;
template <typename T>
inline constexpr bool is_nothrow_move_assignable_v =
    is_nothrow_move_assignable<T>::value;

// is_destructible
template <typename T> struct is_destructible;
template <typename T>
inline constexpr bool is_destructible_v = is_destructible<T>::value;

// is_trivially_destructible
template <typename T> struct is_trivially_destructible;
template <typename T>
inline constexpr bool is_trivially_destructible_v =
    is_trivially_destructible<T>::value;

// is_nothrow_destructible
template <typename T> struct is_nothrow_destructible;
template <typename T>
inline constexpr bool is_nothrow_destructible_v =
    is_nothrow_destructible<T>::value;

// has_virtual_destructor
template <typename T> struct has_virtual_destructor;
template <typename T>
inline constexpr bool has_virtual_destructor_v =
    has_virtual_destructor<T>::value;

/*======================Property queries======================*/

// alignment_of
template <typename T> struct alignment_of;
template <typename T>
inline constexpr size_t alignment_of_v = alignment_of<T>::value;

// rank
template <typename T> struct rank;
template <typename T> inline constexpr size_t rank_v = rank<T>::value;

// extent
template <typename T, unsigned N = 0> struct extent;
template <typename T, unsigned N = 0>
inline constexpr size_t extent_v = extent<T, N>::value;

/*======================Type relationships====================*/

// is_same
template <typename T, typename U> struct is_same;
template <typename T, typename U>
inline constexpr bool is_same_v = is_same<T, U>::value;

// is_base_of
template <typename Base, typename Derived> struct is_base_of;
template <typename Base, typename Derived>
inline constexpr bool is_base_of_v = is_base_of<Base, Derived>::value;

// is_convertible
template <typename From, typename To> struct is_convertible;
template <typename From, typename To>
inline constexpr bool is_convertible_v = is_convertible<From, To>::value;

// is_invocable
template <typename Fn, typename... ArgTypes> struct is_invocable;
template <typename Fn, typename... ArgTypes>
inline constexpr bool is_invocable_v = is_invocable<Fn, ArgTypes...>::value;

// is_invocable_r
template <typename R, typename Fn, typename... ArgTypes> struct is_invocable_r;
template <typename R, typename Fn, typename... ArgTypes>
inline constexpr bool is_invocable_r_v =
    is_invocable_r<R, Fn, ArgTypes...>::value;

/*=====================Operations on traits===================*/

// conjunction
template <typename... B> struct conjunction;
template <typename... B>
inline constexpr bool conjunction_v = conjunction<B...>::value;

// disjunction
template <typename... B> struct disjunction;
template <typename... B>
inline constexpr bool disjunction_v = disjunction<B...>::value;

// negation
template <typename B> struct negation;
template <typename B> inline constexpr bool negation_v = negation<B>::value;

/*============================================================
======================Type modifications======================
==============================================================*/

/*=================Const-volatility specifiers================*/

// remove_cv
template <typename T> struct remove_cv;
template <typename T> using remove_cv_t = typename remove_cv<T>::type;

// remove_const
template <typename T> struct remove_const;
template <typename T> using remove_const_t = typename remove_const<T>::type;

// remove_volatile
template <typename T> struct remove_volatile;
template <typename T>
using remove_volatile_t = typename remove_volatile<T>::type;

// add_cv
template <typename T> struct add_cv;
template <typename T> using add_cv_t = typename add_cv<T>::type;

// add_const
template <typename T> struct add_const;
template <typename T> using add_const_t = typename add_const<T>::type;

// add_volatile
template <typename T> struct add_volatile;
template <typename T> using add_volatile_t = typename add_volatile<T>::type;

/*========================References==========================*/

// remove_reference
template <typename T> struct remove_reference;
template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

// add_lvalue_reference
template <typename T> struct add_lvalue_reference;
template <typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

// add_rvalue_reference
template <typename T> struct add_rvalue_reference;
template <typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

/*==========================Pointers===========================*/

// remove_pointer
template <typename T> struct remove_pointer;
template <typename T> using remove_pointer_t = typename remove_pointer<T>::type;

// add_pointer
template <typename T> struct add_pointer;
template <typename T> using add_pointer_t = typename add_pointer<T>::type;

/*======================Sign modifiers=========================*/

// make_signed
template <typename T> struct make_signed;
template <typename T> using make_signed_t = typename make_signed<T>::type;

// make_unsigned
template <typename T> struct make_unsigned;
template <typename T> using make_unsigned_t = typename make_unsigned<T>::type;

/*===========================Arrays============================*/

// remove_extent
template <typename T> struct remove_extent;
template <typename T> using remove_extent_t = typename remove_extent<T>::type;

// remove_all_extents
template <typename T> struct remove_all_extents;
template <typename T>
using remove_all_extents_t = typename remove_all_extents<T>::type;

/*================Miscellaneous transformations===============*/

// decay
template <typename T> struct decay;
template <typename T> using decay_t = typename decay<T>::type;

// remove_cvref
template <typename T> struct remove_cvref;
template <typename T> using remove_cvref_t = typename remove_cvref<T>::type;

// enable_if
template <bool B, typename T = void> struct enable_if;
template <bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;

// conditional
template <bool B, typename T, typename F> struct conditional;
template <bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;

// common_type
template <typename... T> struct common_type;
template <typename... T> using common_type_t = typename common_type<T...>::type;

// void_t
template <typename...> using void_t = void;

// type_identity
template <typename T> struct type_identity;
template <typename T> using type_identity_t = typename type_identity<T>::type;

/*============================================================
=========================Implementation=======================
==============================================================*/

/*============================================================
=========================Type property========================
==============================================================*/

/*===================Primary type categories==================*/

// is_void
template <typename T> struct is_void : is_same<void, remove_cv_t<T>> {};

// is_null_pointer
template <typename T>
struct is_null_pointer : is_same<nullptr_t, remove_cv_t<T>> {};

// is_integral
template <typename T> struct is_integral : bool_constant<__is_integral(T)> {};

// is_floating_point
template <typename T>
struct is_floating_point
    : bool_constant<is_same_v<float, remove_cv_t<T>> ||
                    is_same_v<double, remove_cv_t<T>> ||
                    is_same_v<long double, remove_cv_t<T>>> {};

// is_array
template <typename T> struct is_array : false_type {};
template <typename T> struct is_array<T[]> : true_type {};
template <typename T, size_t N> struct is_array<T[N]> : true_type {};

// is_enum
template <typename T> struct is_enum : bool_constant<__is_enum(T)> {};

// is_union
template <typename T> struct is_union : bool_constant<__is_union(T)> {};

// is_class
template <typename T> struct is_class : bool_constant<__is_class(T)> {};

// is_function
template <typename T> struct is_function : bool_constant<__is_function(T)> {};

// is_pointer
template <typename T> struct is_pointer : false_type {};
template <typename T> struct is_pointer<T *> : true_type {};
template <typename T> struct is_pointer<T *const> : true_type {};
template <typename T> struct is_pointer<T *volatile> : true_type {};
template <typename T> struct is_pointer<T *const volatile> : true_type {};

// is_lvalue_reference
template <typename T> struct is_lvalue_reference : false_type {};
template <typename T> struct is_lvalue_reference<T &> : true_type {};

// is_rvalue_reference
template <typename T> struct is_rvalue_reference : false_type {};
template <typename T> struct is_rvalue_reference<T &&> : true_type {};

// is_member_object_pointer
template <typename T>
struct is_member_object_pointer
    : bool_constant<is_member_pointer_v<T> &&
                    !is_member_function_pointer_v<T>> {};

// is_member_function_pointer
template <typename T> struct is_member_function_pointer_impl : false_type {};
template <typename T, typename U>
struct is_member_function_pointer_impl<T U::*> : is_function<T> {};
template <typename T>
struct is_member_function_pointer
    : is_member_function_pointer_impl<remove_cv_t<T>> {};

/*==================Composite type categories=================*/

// is_fundamental
template <typename T>
struct is_fundamental : bool_constant<is_arithmetic_v<T> || is_void_v<T> ||
                                      is_null_pointer_v<T>> {};

// is_arithmetic
template <typename T>
struct is_arithmetic
    : bool_constant<is_integral_v<T> || is_floating_point_v<T>> {};

// is_scalar
template <typename T>
struct is_scalar
    : bool_constant<is_arithmetic_v<T> || is_enum_v<T> || is_pointer_v<T> ||
                    is_member_pointer_v<T> || is_null_pointer_v<T>> {};

// is_object
template <typename T>
struct is_object : bool_constant<is_scalar_v<T> || is_array_v<T> ||
                                 is_union_v<T> || is_class_v<T>> {};

// is_compound
template <typename T>
struct is_compound : bool_constant<!is_fundamental_v<T>> {};

// is_reference
template <typename T>
struct is_reference
    : bool_constant<is_lvalue_reference_v<T> || is_rvalue_reference_v<T>> {};

// is_member_pointer
template <typename T> struct is_member_pointer_impl : false_type {};
template <typename T, typename U>
struct is_member_pointer_impl<T U::*> : true_type {};
template <typename T>
struct is_member_pointer : is_member_pointer_impl<remove_cv_t<T>> {};

/*=======================Type properties======================*/

// is_const
template <typename T> struct is_const : false_type {};
template <typename T> struct is_const<const T> : true_type {};

// is_volatile
template <typename T> struct is_volatile : false_type {};
template <typename T> struct is_volatile<volatile T> : true_type {};

// is_trivial
template <typename T> struct is_trivial : bool_constant<__is_trivial(T)> {};

// is_trivially_copyable
template <typename T>
struct is_trivially_copyable : bool_constant<__is_trivially_copyable(T)> {};

// is_standard_layout
template <typename T>
struct is_standard_layout : bool_constant<__is_standard_layout(T)> {};

// // is_pod
template <typename T> struct is_pod : bool_constant<__is_pod(T)> {};

// is_empty
template <typename T> struct is_empty : bool_constant<__is_empty(T)> {};

// is_polymorphic
template <typename T>
true_type detect_is_polymorphic(
    decltype(dynamic_cast<const volatile void *>(static_cast<T *>(nullptr))));

template <typename T> false_type detect_is_polymorphic(...);

template <typename T>
struct is_polymorphic : decltype(detect_is_polymorphic<T>(nullptr)) {};

// is_abstract
template <typename T> struct is_abstract : bool_constant<__is_abstract(T)> {};

// is_final
template <typename T> struct is_final : bool_constant<__is_final(T)> {};

// is_aggregate
template <typename T> struct is_aggregate : bool_constant<__is_aggregate(T)> {};

// is_signed
template <typename T, bool = is_arithmetic_v<T>>
struct is_signed_impl : bool_constant<T(-1) < T(0)> {};
template <typename T> struct is_signed_impl<T, false> : false_type {};
template <typename T> struct is_signed : is_signed_impl<T>::type {};

// is_unsigned
template <typename T, bool = is_arithmetic_v<T>>
struct is_unsigned_impl : bool_constant<T(0) < T(-1)> {};
template <typename T> struct is_unsigned_impl<T, false> : false_type {};
template <typename T> struct is_unsigned : is_unsigned_impl<T>::type {};

// is_bounded_array
template <typename T> struct is_bounded_array : false_type {};
template <typename T, size_t N> struct is_bounded_array<T[N]> : true_type {};

// // is_unbounded_array
template <typename T> struct is_unbounded_array : false_type {};
template <typename T> struct is_unbounded_array<T[]> : true_type {};

/*====================Supported operations====================*/

// is_constructible

// function overloads approach
// struct is_constructible_helper {
//   template <typename T, typename... Args,
//             typename = decltype(T(std::declval<Args>()...))>
//   static true_type test(int);
//   template <typename, typename...>
//   static false_type test(...);
// };

// template <typename T, typename... Args>
// struct is_constructible
//     : decltype(is_constructible_helper::test<T, Args...>(0)) {};

// partial specializations approach
template <typename AlwaysVoid, typename T, typename... Args>
struct is_constructible_impl : false_type {};
template <typename T, typename... Args>
struct is_constructible_impl<void_t<decltype(T(std::declval<Args>()...))>, T,
                             Args...> : true_type {};

template <typename T, typename... Args>
struct is_constructible : is_constructible_impl<void, T, Args...> {};

// is_trivially_constructible
template <typename T, typename... Args>
struct is_trivially_constructible
    : bool_constant<__is_trivially_constructible(T, Args...)> {};

// is_nothrow_constructible
template <typename T, typename... Args>
struct is_nothrow_constructible
    : bool_constant<__is_nothrow_constructible(T, Args...)> {};

// is_default_constructible
template <typename T> struct is_default_constructible : is_constructible<T> {};

// is_trivially_default_constructible
template <typename T>
struct is_trivially_default_constructible : is_trivially_constructible<T> {};

// is_nothrow_default_constructible
template <typename T>
struct is_nothrow_default_constructible : is_nothrow_constructible<T> {};

// is_copy_constructible
template <typename T>
struct is_copy_constructible
    : is_constructible<T, add_lvalue_reference_t<add_const_t<T>>> {};

// is_trivially_copy_constructible
template <typename T>
struct is_trivially_copy_constructible
    : is_trivially_constructible<T, add_lvalue_reference_t<add_const_t<T>>> {};

// is_nothrow_copy_constructible
template <typename T>
struct is_nothrow_copy_constructible
    : is_nothrow_constructible<T, add_lvalue_reference_t<add_const_t<T>>> {};

// is_move_constructible
template <typename T>
struct is_move_constructible : is_constructible<T, add_rvalue_reference_t<T>> {
};

// is_trivially_move_constructible
template <typename T>
struct is_trivially_move_constructible
    : is_trivially_constructible<T, add_rvalue_reference_t<T>> {};

// is_nothrow_move_constructible
template <typename T>
struct is_nothrow_move_constructible
    : is_nothrow_constructible<T, add_rvalue_reference_t<T>> {};

// is_assignable
// function overloads approach
// struct is_assignable_helper {
//   template <typename T, typename U,
//             typename = decltype(std::declval<T>() = std::declval<U>())>
//   static true_type test(int);
//   template <typename, typename>
//   static false_type test(...);
// };

// template <typename T, typename U>
// struct is_assignable : decltype(is_assignable_helper::test<T, U>(0)) {};

// partial specializations approach
template <typename T, typename U, typename = void>
struct is_assignable_impl : false_type {};
template <typename T, typename U>
struct is_assignable_impl<
    T, U, void_t<decltype(std::declval<T>() = std::declval<U>())>> : true_type {
};

template <typename T, typename U>
struct is_assignable : is_assignable_impl<T, U> {};

// is_trivially_assignable
template <typename T, typename U>
struct is_trivially_assignable
    : bool_constant<__is_trivially_assignable(T, U)> {};

// is_nothrow_assignable
template <typename T, typename U>
struct is_nothrow_assignable : bool_constant<__is_nothrow_assignable(T, U)> {};

// is_copy_assignable
template <typename T>
struct is_copy_assignable : is_assignable<add_lvalue_reference_t<T>,
                                          add_lvalue_reference_t<const T>> {};

// is_trivially_copy_assignable
template <typename T>
struct is_trivially_copy_assignable
    : is_trivially_assignable<add_lvalue_reference_t<T>,
                              add_lvalue_reference_t<const T>> {};

// is_nothrow_copy_assignable
template <typename T>
struct is_nothrow_copy_assignable
    : is_nothrow_assignable<add_lvalue_reference_t<T>,
                            add_lvalue_reference_t<const T>> {};

// is_move_assignable
template <typename T>
struct is_move_assignable
    : is_assignable<add_lvalue_reference_t<T>, add_rvalue_reference_t<T>> {};

// is_trivially_move_assignable
template <typename T>
struct is_trivially_move_assignable
    : is_trivially_assignable<add_lvalue_reference_t<T>,
                              add_rvalue_reference_t<T>> {};

// is_nothrow_move_assignable
template <typename T>
struct is_nothrow_move_assignable
    : is_nothrow_assignable<add_lvalue_reference_t<T>,
                            add_rvalue_reference_t<T>> {};

// is_destructible
//  if it's a reference, return true
//  if it's a function, return false
//  if it's   void,     return false
//  if it's an array of unknown bound, return false
//  Otherwise, return "declval<U&>().~U()" is well-formed
//    where U is remove_all_extents<T>::type
// struct is_destructible_helper {
//   template <typename U, typename = decltype(std::declval<U&>().~U())>
//   static true_type test(int);
//   template <typename, typename>
//   static false_type test(...);
// };

// template <typename T>
// struct is_destructible
//     : conditional_t<is_reference_v<T>, true_type,
//                     conditional_t<is_void_v<T> || is_function_v<T> ||
//                                       is_unbounded_array_v<T>,
//                                   false_type,
//                                   decltype(is_destructible_helper::test<
//                                            remove_all_extents_t<T>>(0))>> {};

template <typename U, typename = void>
struct is_destructible_impl : false_type {};
template <typename U>
struct is_destructible_impl<U, void_t<decltype(std::declval<U &>().~U())>>
    : true_type {};

template <typename T>
struct is_destructible
    : conditional_t<
          is_reference_v<T>, true_type,
          conditional_t<
              is_void_v<T> || is_function_v<T> || is_unbounded_array_v<T>,
              false_type,
              typename is_destructible_impl<remove_all_extents_t<T>>::type>> {};

// is_trivially_destructible
template <typename T>
struct is_trivially_destructible
    : bool_constant<__is_trivially_destructible(T)> {};

// is_nothrow_destructible
template <typename T, bool> struct is_nothrow_destructible_impl : false_type {};
template <typename T>
struct is_nothrow_destructible_impl<T, true>
    : bool_constant<noexcept(std::declval<T &>().~T())> {};

template <typename T>
struct is_nothrow_destructible
    : is_nothrow_destructible_impl<T, is_destructible_v<T>> {};
template <typename T, size_t N>
struct is_nothrow_destructible<T[N]> : is_nothrow_destructible<T> {};
template <typename T> struct is_nothrow_destructible<T &> : true_type {};
template <typename T> struct is_nothrow_destructible<T &&> : true_type {};

// has_virtual_destructor
template <typename T>
struct has_virtual_destructor : bool_constant<__has_virtual_destructor(T)> {};

/*======================Property queries======================*/

// alignment_of
template <typename T>
struct alignment_of : integral_constant<size_t, alignof(T)> {};

// rank
template <typename T> struct rank : integral_constant<size_t, 0> {};
template <typename T>
struct rank<T[]> : integral_constant<size_t, rank_v<T> + 1> {};
template <typename T, size_t N>
struct rank<T[N]> : integral_constant<size_t, rank_v<T> + 1> {};

// extent
template <typename T, unsigned N>
struct extent : integral_constant<size_t, 0> {};
template <typename T> struct extent<T[], 0> : integral_constant<size_t, 0> {};
template <typename T, unsigned N> struct extent<T[], N> : extent<T, N - 1> {};
template <typename T, std::size_t I>
struct extent<T[I], 0> : std::integral_constant<std::size_t, I> {};
template <typename T, std::size_t I, unsigned N>
struct extent<T[I], N> : std::extent<T, N - 1> {};

/*======================Type relationships====================*/

// is_same
template <typename T, typename U> struct is_same : false_type {};
template <typename T> struct is_same<T, T> : true_type {};

// is_base_of
struct is_base_of_helper {
  template <typename B> static true_type test_ptr_conv(const volatile B *);
  template <typename> static false_type test_ptr_conv(const volatile void *);

  template <typename B, typename D>
  static auto test_is_base_of(int)
      -> decltype(test_ptr_conv<B>(static_cast<D *>(nullptr)));
  template <typename, typename>
  static auto test_is_base_of(...) -> true_type; // private or ambiguous base

  template <typename B, typename D>
  static constexpr bool test_is_base_of_v =
      decltype(test_is_base_of<B, D>(0))::value;
};

template <typename Base, typename Derived>
struct is_base_of
    : bool_constant<is_class_v<Base> && is_class_v<Derived> &&
                    is_base_of_helper::test_is_base_of_v<Base, Derived>> {};

// is_convertible

// conversion to function or array type is now allowed
// conversion from void to void is allowed
template <typename From, typename To,
          bool = is_void_v<To> || is_array_v<To> || is_function_v<To>>
struct is_convertible_helper {
  using type = bool_constant<is_void_v<From> && is_void_v<To>>;
};

template <typename From, typename To>
struct is_convertible_helper<From, To, false> {
  static void aux(To);

  template <typename F, typename = decltype(aux(std::declval<F>()))>
  static true_type test(int);
  template <typename> static false_type test(...);

  using type = decltype(test<From>(0));
};

template <typename From, typename To>
struct is_convertible : is_convertible_helper<From, To>::type {};

// is_invocable

// not a type
struct nat {
  nat() = delete;
  nat(const nat &) = delete;
  nat &operator=(const nat &) = delete;
  nat(nat &&) = delete;
  nat &operator=(nat &&) = delete;
  ~nat() = delete;
};

template <typename R, typename Fn, typename... ArgTypes>
struct is_invocable_helper {
  template <typename F, typename... Args>
  static auto try_call(int)
      -> decltype(std::invoke(std::declval<F>(), std::declval<Args>()...));
  template <typename F, typename... Args> static nat try_call(...);

  using result = decltype(try_call<Fn, ArgTypes...>(0));

  using type = conditional_t<
      !is_same_v<nat, result>,
      conditional_t<is_void_v<R>, true_type, is_convertible<result, R>>,
      false_type>;
};

template <typename Fn, typename... ArgTypes>
struct is_invocable : is_invocable_helper<void, Fn, ArgTypes...>::type {};

// is_invocable_r
template <typename R, typename Fn, typename... ArgTypes>
struct is_invocable_r : is_invocable_helper<R, Fn, ArgTypes...>::type {};

/*=====================Operations on traits===================*/

// conjunction
template <typename...> struct conjunction : true_type {};
template <typename B1> struct conjunction<B1> : B1 {};
template <typename B1, typename... Bn>
struct conjunction<B1, Bn...>
    : conditional_t<bool(B1::value), conjunction<Bn...>, B1> {};

// disjunction
template <typename...> struct disjunction : false_type {};
template <typename B1> struct disjunction<B1> : B1 {};
template <typename B1, typename... Bn>
struct disjunction<B1, Bn...>
    : conditional_t<bool(B1::value), B1, disjunction<Bn...>> {};

// negation
template <typename B> struct negation : bool_constant<!bool(B::value)> {};

/*============================================================
======================Type modifications======================
==============================================================*/

// remove_cv
template <typename T> struct remove_cv {
  using type = remove_const_t<remove_volatile_t<T>>;
};

// remove_const
template <typename T> struct remove_const {
  using type = T;
};
template <typename T> struct remove_const<const T> {
  using type = T;
};

// remove_volatile
template <typename T> struct remove_volatile {
  using type = T;
};
template <typename T> struct remove_volatile<volatile T> {
  using type = T;
};

// add_cv
template <typename T> struct add_cv {
  using type = const volatile T;
};

// add_const
template <typename T> struct add_const {
  using type = const T;
};

// add_volatile
template <typename T> struct add_volatile {
  using type = volatile T;
};

// remove_reference
template <typename T> struct remove_reference {
  using type = T;
};
template <typename T> struct remove_reference<T &> {
  using type = T;
};
template <typename T> struct remove_reference<T &&> {
  using type = T;
};

// add_lvalue_reference
template <typename T> // `cv void&` is a substitution failure
auto try_add_lvalue_reference(int) -> type_identity<T &>;
template <typename T> // Handle T = cv void case
auto try_add_lvalue_reference(...) -> type_identity<T>;
template <typename T>
struct add_lvalue_reference : decltype(try_add_lvalue_reference<T>(0)) {};

// add_rvalue_reference
template <typename T> auto try_add_rvalue_reference(int) -> type_identity<T &&>;
template <typename T> auto try_add_rvalue_reference(...) -> type_identity<T>;
template <typename T>
struct add_rvalue_reference : decltype(try_add_rvalue_reference<T>(0)) {};

// remove pointer
template <typename T> struct remove_pointer {
  using type = T;
};
template <typename T> struct remove_pointer<T *> {
  using type = T;
};
template <typename T> struct remove_pointer<T *const> {
  using type = T;
};
template <typename T> struct remove_pointer<T *volatile> {
  using type = T;
};
template <typename T> struct remove_pointer<T *const volatile> {
  using type = T;
};

// add_pointer
template <typename T>
auto try_add_pointer(int) -> type_identity<remove_reference_t<T> *>;
template <typename T> auto try_add_pointer(...) -> type_identity<T>;
template <typename T> struct add_pointer : decltype(try_add_pointer<T>(0)) {};

// remove_extent
template <typename T> struct remove_extent {
  using type = T;
};
template <typename T> struct remove_extent<T[]> {
  using type = T;
};
template <typename T, size_t N> struct remove_extent<T[N]> {
  using type = T;
};

// remove_all_extents
template <typename T> struct remove_all_extents {
  using type = T;
};
template <typename T> struct remove_all_extents<T[]> {
  using type = remove_all_extents_t<T>;
};
template <typename T, size_t N> struct remove_all_extents<T[N]> {
  using type = remove_all_extents_t<T>;
};

// decay
template <typename T> struct decay {
private:
  using U = remove_reference_t<T>;

public:
  using type = conditional_t<
      is_array_v<U>, add_pointer_t<remove_extent_t<U>>,
      conditional_t<is_function_v<U>, add_pointer_t<U>, remove_cv_t<U>>>;
};

// remove_cvref
template <typename T> struct remove_cvref {
  using type = remove_cv_t<remove_reference_t<T>>;
};

// enable_if
template <bool B, typename T> struct enable_if {};
template <typename T> struct enable_if<true, T> {
  using type = T;
};

// conditional
template <bool B, class T, class F> struct conditional {
  using type = T;
};
template <class T, class F> struct conditional<false, T, F> {
  using type = F;
};

// common_type
template <typename...> struct common_type {};
template <typename T> struct common_type<T> : common_type<T, T> {};

namespace common_type_impl {

template <typename T1, typename T2>
using conditional_result_t =
    decltype(false ? std::declval<T1>() : std::declval<T2>());

// SFINAE Out Partial Specializations approach
template <typename, typename, typename = void>
struct decay_conditional_result {};
template <typename T1, typename T2>
struct decay_conditional_result<T1, T2, void_t<conditional_result_t<T1, T2>>>
    : decay<conditional_result_t<T1, T2>> {};

template <typename T1, typename T2, typename = void>
struct common_type_2_impl {};
template <typename T1, typename T2>
struct common_type_2_impl<T1, T2, void_t<conditional_result_t<T1, T2>>>
    : decay_conditional_result<T1, T2> {};

template <typename AlwaysVoid, typename T1, typename T2, typename... Ts>
struct common_type_multi_impl {};
template <typename T1, typename T2, typename... Ts>
struct common_type_multi_impl<void_t<common_type_t<T1, T2>>, T1, T2, Ts...>
    : common_type<common_type_t<T1, T2>, Ts...> {};

}; // namespace common_type_impl

// two types
template <typename T1, typename T2>
struct common_type<T1, T2>
    : conditional_t<is_same_v<T1, decay_t<T1>> && is_same_v<T2, decay_t<T2>>,
                    common_type_impl::common_type_2_impl<T1, T2>,
                    common_type<decay_t<T1>, decay_t<T2>>> {};

// +3 types
template <typename T1, typename T2, typename... Ts>
struct common_type<T1, T2, Ts...>
    : common_type_impl::common_type_multi_impl<void, T1, T2, Ts...> {};

// type_identity
template <typename T> struct type_identity {
  using type = T;
};

}; // namespace stl

#endif // TYPE_TRAITS_H_
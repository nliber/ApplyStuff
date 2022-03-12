#include <cool/std.h>
#include <tuple>

#if 0
template<typename... Ts>
void f(Ts&&...) { std::cout << __PRETTY_FUNCTION__ << '\n'; }

#else
inline void f(int, int, int) { std::cout << __PRETTY_FUNCTION__ << '\n'; }
inline void f(int, int, int, int) { std::cout << __PRETTY_FUNCTION__ << '\n'; }
#endif

template<typename T, size_t I>
struct Identity {
    using type = T;
};

template<typename T, size_t I>
using Identity_t = typename Identity<T, I>::type;

template <typename F, typename A, size_t... I>
constexpr decltype(auto) apply_impl(F&& f, A&& a, std::index_sequence<I...>) {
    return static_cast<F&&>(f)(static_cast<A&&>(a)[I]...);
}

template <typename F, typename A>
constexpr decltype(auto) apply(F&& f, A&& a) {
    return apply_impl(
        static_cast<F&&>(f), static_cast<A&&>(a),
        std::make_index_sequence<
            std::tuple_size<std::remove_reference_t<A>>::value>());
}

template <typename F, typename T, size_t N>
constexpr decltype(auto) apply(F&& f, T (&array)[N]) {
    return apply_impl(static_cast<F&&>(f), array, std::make_index_sequence<N>());
}

template<typename T, size_t N, size_t... I>
constexpr decltype(auto) apply_to_f_impl(T (&array)[N], std::index_sequence<I...>) {
    //static_cast<void(Identity_t<T, I>...)>(f)(array[I]...);
    apply(static_cast<void(*)(Identity_t<T, I>...)>(f), array);
    //apply(static_cast<void(*)(int,int,int)>(f), array);
}


template<typename T, size_t N>
constexpr decltype(auto) apply_to_f(T (&array)[N]) {
    return apply_to_f_impl(array, std::make_index_sequence<N>());
}

extern int Main(int /* argc */, char const* const /* argv */[]);
int Main(int /* argc */, char const* const /* argv */[]) {
    int a[3];
    apply_to_f(a);

    int b[4];
    apply_to_f(b);
    return 0;
}


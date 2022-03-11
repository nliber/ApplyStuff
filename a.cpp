#include <cool/std.h>
#include <tuple>

inline void f(int, int, int) { std::cout << __PRETTY_FUNCTION__ << '\n'; }

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

template <class T, std::size_t N>
constexpr std::size_t size(const T (&array)[N]) noexcept;

template <typename F, typename T, size_t N>
constexpr decltype(auto) apply(F&& f, T (&array)[N]) {
    return apply_impl(static_cast<F&&>(f), array, std::make_index_sequence<N>());
}

extern int Main(int /* argc */, char const* const /* argv */[]);
int Main(int /* argc */, char const* const /* argv */[]) {
    int a[3];
    apply(f, a);
    return 0;
}


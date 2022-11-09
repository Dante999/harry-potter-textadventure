#ifndef HPTA_ALGORITHMS_HPP
#define HPTA_ALGORITHMS_HPP

#include <algorithm>
#include <random>

namespace hpta {

template <typename T>
bool is_between_or_equal(T min, T max, T value)
{
    return (min <= value && value <= max);
}

template <typename T>
T get_middlepoint(T a, T b)
{
    return (a + b) / 2;
}

template <typename T>
T get_distance(T a, T b)
{
    return std::abs(a - b);
}

template <typename T>
auto get_random_entry(const T &values)
{
    /* @todo FIX ME */
    // T::iterator out;
    T out;
    std::sample(std::begin(values), std::end(values), std::back_inserter(out), 1, std::mt19937{std::random_device{}()});

    return out.at(0);

    // return values.at(0);
}

} // namespace hpta

#endif // HPTA_ALGORITHMS_HPP

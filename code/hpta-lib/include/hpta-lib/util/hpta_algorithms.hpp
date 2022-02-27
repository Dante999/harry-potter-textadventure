#ifndef HPTA_ALGORITHMS_HPP
#define HPTA_ALGORITHMS_HPP

#include <algorithm>

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

} // namespace hpta

#endif // HPTA_ALGORITHMS_HPP

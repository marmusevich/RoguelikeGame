#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <cmath>
#include <cstdlib>
#include <type_traits>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

//Magnitude
//typedef Vector2<int>          Vector2i;
//typedef Vector2<unsigned int> Vector2u;
//typedef Vector2<float>        Vector2f;


constexpr const float PI = 3.141592653589793238462643383279502884f;


inline float RadToGrad(float rad);

inline float GradToRad(float grad);



/**
 * Linear interpolation.
 * \tparam - scalar type of functions (int, float ant etc.)
 * \param x - the number to map
 * \param in_min - the lower bound of the value's current range
 * \param in_max - the upper bound of the value's current range
 * \param out_min - the lower bound of the value's target range
 * \param out_max - the upper bound of the value's target range
 * \return The mapped value.
 *
 * NOTE ReWrite discriptions
 * Re-maps a number from one range to another. That is, a value of fromLow would get mapped to toLow,
 * a value of fromHigh to toHigh, values in-between to values in-between, etc.
 *
 * Does not constrain values to within the range, because out-of-range values are sometimes intended and useful.
 * The constrain() function may be used either before or after this function, if limits to the ranges are desired.
 *
 * Note that the "lower bounds" of either range may be larger or smaller than the "upper bounds"
 * so the map() function may be used to reverse a range of numbers, for example
 *
 * y = map(x, 1, 50, 50, 1);
 * The function also handles negative numbers well, so that this example
 * y = map(x, 1, 50, 50, -100);
 * is also valid and works well.
 *
 * The map() function uses integer math so will not generate fractions, when the math might indicate that it
 * should do so. Fractional remainders are truncated, and are not rounded or averaged.
  */
template <typename T>
inline T LinearInterpolation(T x, T in_min, T in_max, T out_min, T out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


/*
* 2D Vectors
*/

inline float Magnitude(sf::Vector2f vec);

inline float AngleBetweenVectors(sf::Vector2f vec1, sf::Vector2f vec2);

inline sf::Vector2f Normalize(sf::Vector2f vec);

/**
 * Calculates the distance between two points
 * @param position1 The position of the first point.
 * @param position2 The position of the second item.
 * @return The distance between the two points.
 */
float DistanceBetweenPoints(sf::Vector2f poit1, sf::Vector2f poit2);


/*
* RANDOM NUMER
*/

/**
 * Seeds the pseudo-random number generator by current system time.
 */
void RandomSeedByTime();

/**
 * Seeds the pseudo-random number generator.
 * \seed - the seed
 */
inline void RandomSeed(unsigned int seed)
{
    std::srand(seed);
}


/**
 * Retern random boolean value (true or false).
 */
inline bool Random()
{
    return static_cast<bool>(std::rand() % 2);
}

/**
 * The random function generates pseudo-random numbers.
 * \param max - upper bound of the random value, exclusive
 * \return a random number between 0 and max-1
 */
template <typename T>
inline T Random(T max)
{
	T ret = static_cast<T>(0);
	if (static_cast<int>(max) + 1 != 0)
	{
		ret = static_cast<T>(std::rand() % (static_cast<int>(max) + 1));
	}
	return ret;
}

template <typename T>
inline  T RandomEnum(T max)
{
	T ret = static_cast<T>(0);
	if (static_cast<int>(max) != 0)
	{
		ret = static_cast<T>(std::rand() % (static_cast<int>(max)));
	}
	return ret;
}


// TODO  make specilization to ENUMS and FLOAT (DOUBLE), avoid not numeric spec

//template <typename T, std::size_t, typename = void>
//template <typename T/*, typename = void*/>
//inline T Random(T max);
//
//template <typename T>
//inline typename std::enable_if< std::is_integral<T>::value, T >::type Random <>(T max)
////typename std::enable_if<std::is_integral<T>::value, bool>::type
////inline Random(T max) 
//{
//	T ret = static_cast<T>(0);
//	if (static_cast<int>(max) + 1 != 0)
//	{
//	ret = static_cast<T>(std::rand() % (static_cast<int>(max) + 1));
//	}
//	return ret;
//}
//
//template <typename T>
//inline typename std::enable_if< std::is_enum<T>::value, T >::type Random<>(T max)
////typename std::enable_if<std::is_enum<T>::value, bool>::type
////inline Random(T max)
//{
//	T ret = static_cast<T>(0);
//	if (static_cast<int>(max) != 0)
//	{
//		ret = static_cast<T>(std::rand() % (static_cast<int>(max) ));
//	}
//	return ret;
//}

//template <typename T>
//inline T Random< T, typename std::enable_if< std::is_floating_point<T>::value >::type >(T max)
//{
//	T ret = static_cast<T>(0);
//	if (static_cast<int>(max) != 0)
//	{
//		ret = static_cast<T>(std::rand() % (static_cast<int>(max)));
//	}
//	return ret;
//}


/**
 * The random function generates pseudo-random numbers.
 * \param min - lower bound of the random value, inclusive (optional)
 * \param max - upper bound of the random value, exclusive
 * \return a random number between min and max-1
 */
template <typename T>
inline T Random(T min, T max)
{
	if (min >= max) 
	{
	return min;
	}
	const T diff = max - min;
	return Random(diff) + min;
}

/**
 * Reorders the elements in the given range [first, last)
 * such that each possible permutation of those elements has equal probability of appearance.
 * see https://en.cppreference.com/w/cpp/algorithm/random_shuffle
 */
template< class RandomIt >
void RandomShuffle(RandomIt first, RandomIt last)
{
	typename std::iterator_traits<RandomIt>::difference_type i, n;
	n = last - first;
	for (i = n - 1; i > 0; --i) {
		using std::swap;
		swap(first[i], first[std::rand() % (i + 1)]);
		// rand() % (i+1) isn't actually correct, because the generated number
		// is not uniformly distributed for most values of i. A correct implementation
		// will need to essentially reimplement C++11 std::uniform_int_distribution,
		// which is beyond the scope of this example.
	}
}

inline sf::Color RandomColor(sf::Uint8 from, sf::Uint8 to)
{
	return sf::Color(Random(from, to), Random(from, to), Random(from, to), 255);
}


#endif
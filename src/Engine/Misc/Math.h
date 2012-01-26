#ifndef MATH_H
#define MATH_H

#include <algorithm>
#include <math.h>
#include <SFML/System.hpp>

namespace Math{

	template<class T>
	bool isBetween(const T& min, const T& max, const T& elem)
	{
		return elem <= max && elem >= min;
	}

	
}

#endif


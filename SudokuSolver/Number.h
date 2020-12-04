#pragma once

#include <iostream>

enum class Number
{
	None = 0,
	One = 1 << 0,
	Two = 1 << 1,
	Three = 1 << 2,
	Four = 1 << 3,
	Five = 1 << 4,
	Six = 1 << 5,
	Seven = 1 << 6,
	Eight = 1 << 7,
	Nine = 1 << 8,
	All = One | Two | Three | Four | Five | Six | Seven | Eight | Nine
};


inline std::ostream& operator<<(std::ostream& out, Number num) {
	int n = static_cast<int>(num);
	if (((n - 1) & n) != 0)
		out << ' ';
	else
	{
		int i = 0;
		for (int n = static_cast<int>(num); n > 0; n >>= 1)
			i++;
		out << i;
	}
	return out;
}

inline Number operator&(Number left, Number right) {
	return static_cast<Number>(static_cast<int>(left) & static_cast<int>(right));
}
inline Number operator|(Number left, Number right) {
	return static_cast<Number>(static_cast<int>(left) | static_cast<int>(right));
}
inline Number operator^(Number left, Number right) {
	return static_cast<Number>(static_cast<int>(left) ^ static_cast<int>(right));
}
inline Number operator<<(Number left, int right) {
	return static_cast<Number>(static_cast<int>(left) << right);
}

inline Number operator-(Number left, Number right) {
	return (left | right) ^ right;
}


inline Number operator|=(Number& left, Number right) {
	return left = left | right;
}
inline Number operator<<=(Number& left, int right) {
	return left = left << right;
}

inline Number operator-=(Number& left, Number right) {
	return left = left - right;
}

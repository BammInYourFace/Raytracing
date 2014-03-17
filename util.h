#ifndef UTIL_H
#define UTIL_H

#include <SFML\Graphics.hpp>
#include <math.h>
#include <sstream>

template<class T> 
inline std::string toStr(T x)
{
    std::stringstream type;
    type << x;
    return type.str();
}

inline float dot(const sf::Vector3f& a, const sf::Vector3f& b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

inline sf::Vector3f cross(const sf::Vector3f& a, const sf::Vector3f& b)
{
	return sf::Vector3f(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

inline float squaredLength(const sf::Vector3f& vec)
{
	return abs(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

inline float length(const sf::Vector3f& vec)
{
	return sqrt(abs(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

inline sf::Vector3f normalize(const sf::Vector3f& vec)
{
	if(length(vec) > 0.0f)
	{
		return sf::Vector3f(vec.x/length(vec), vec.y/length(vec), vec.z/length(vec));
	}
	else
	{
		return sf::Vector3f(0.0f, 0.0f, 0.0f);
	}
}

inline float randFloat(float a, float b) 
{
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

inline int randInt(int a, int b)
{
	if(a==b)
	{
		return a;
	}
	if(a<b)
	{
		return rand()%(b-a) + a;
	}
	else
	{
		return rand()%(a-b) + b;
	}
}

#endif //UTIL_H
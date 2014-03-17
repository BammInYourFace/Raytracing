#include <SFML/Graphics.hpp>
#include "light.h"

Light::Light(const sf::Vector3f& newPosition, const sf::Color& newColor, float newRange, float newIntensity)
	:position(newPosition),
	color(newColor),
	range(newRange),
	intensity(newIntensity)
{
	//
}

const sf::Vector3f& Light::getPosition() const
{
	return position;
}

const sf::Color& Light::getColor() const
{
	return color;
}

const float Light::getRange() const
{
	return range;
}

const float Light::getIntensity() const
{
	return intensity;
}

PointLight::PointLight(const sf::Vector3f& newPosition, const sf::Color& newColor, float newRange, float newIntensity)
	:Light(newPosition, newColor, newRange, newIntensity)
{

}
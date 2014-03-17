#ifndef LIGHT_H
#define LIGHT_H



class Light
{
protected:
	sf::Vector3f position;
	sf::Color color;
	float range;
	float intensity;
public:
	Light(const sf::Vector3f& newPosition, const sf::Color& newColor, float newRange, float newIntensity);
	const sf::Vector3f& getPosition() const;
	const sf::Color& getColor() const;
	const float getRange() const;
	const float getIntensity() const;
	
};

class PointLight : public Light
{
public:
	PointLight(const sf::Vector3f& newPosition, const sf::Color& newColor, float newRange, float newIntensity);
};


#endif //LIGHT_H
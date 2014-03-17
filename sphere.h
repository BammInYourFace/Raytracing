#ifndef SPHERE_H
#define SPHERE_H

class RenderObject;

class Sphere : public RenderObject
{
private:
public:
	Sphere(Material& newMaterial);
	int testRay(const sf::Vector3f& origin, const sf::Vector3f& direction, sf::Vector3f& hitPosition, sf::Vector2f& UVCoordinates) override;
	const sf::Vector3f getNormal(const sf::Vector3f& point) const override;
	const sf::Vector3f getNormal() const override;
};

#endif //SPHERE_H
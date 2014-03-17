#ifndef TRIANGLE_H
#define TRIANGLE_H

class RenderObject;
struct Vertex;

class Triangle : public RenderObject
{
private:
	std::vector<Vertex> vertices;
public:
	Triangle(Material& newMaterial);
	int testRay(const sf::Vector3f& origin, const sf::Vector3f& direction, sf::Vector3f& hitPosition, sf::Vector2f& UVCoordinates) override;
	const sf::Vector3f getNormal(const sf::Vector3f& point) const override;
	const sf::Vector3f getNormal() const override;

	void setVertex(unsigned int number,const sf::Vector3f& position);
	void setVertex(unsigned int number,const sf::Vector3f& position, const sf::Vector2f& UVPosition);
	const Vertex getVertex(unsigned int Number) const;
};

#endif //TRIANGLE_H
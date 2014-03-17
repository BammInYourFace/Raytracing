#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H
////////////////////////////////////////////////////////////
/// Defines the appearance of an object
////////////////////////////////////////////////////////////
struct Material
{
private:
public:
	sf::Color diffuse;
	sf::Color specular;
	float reflection;
	sf::Image* texture;
	sf::Image* normalMap;
	Material();
	void setTexture(sf::Image* newTexture);
	const sf::Color& getColorByTexture(const sf::Vector2f& UVcoordinates) const;
	void setNormalMap(sf::Image* newNormalMap);
	float getNormalByNormalMap(const sf::Vector2f& UVcoordinates);
};

////////////////////////////////////////////////////////////
/// Defines the location, scale and rotation of an object in the world
////////////////////////////////////////////////////////////
struct Transform
{
private:
public:
	sf::Vector3f position;
	sf::Vector3f scale;
	sf::Vector3f rotation;
	Transform();
};

////////////////////////////////////////////////////////////
/// Defines a point in the world and its texturecoordinates
////////////////////////////////////////////////////////////
struct Vertex
{
private:
public:
	sf::Vector3f position;
	sf::Vector2f UVposition;
	Vertex();
};

class Renderer;


////////////////////////////////////////////////////////////
/// Defines a object, that can be rendered
////////////////////////////////////////////////////////////
class RenderObject
{
protected:
	Transform transform;
	Material& material;
public:
	RenderObject(Material& newMaterial);

	virtual int testRay(const sf::Vector3f& origin, const sf::Vector3f& direction, sf::Vector3f& hitPosition, sf::Vector2f& UVCoordinates) = 0;
	virtual const sf::Vector3f getNormal(const sf::Vector3f& point) const = 0;
	virtual const sf::Vector3f getNormal() const  = 0;

	void setTransform(const Transform& newTransform);
	Transform&  getTransform();

	void setMaterial(Material& newMaterial);
	Material& getMaterial();
};

#endif //RENDEROBJECT_H
#include <SFML\Graphics.hpp>
#include <renderObject.h>

Material::Material()
	:diffuse(sf::Color::White),
	specular(sf::Color::White),
	reflection(0.0f),
	texture(),
	normalMap()
{
}

void Material::setTexture(sf::Image* newTexture)
{
	texture = newTexture;
}

const sf::Color& Material::getColorByTexture(const sf::Vector2f& UVcoordinates) const
{
	if(texture)
	{
		return diffuse*texture->getPixel(static_cast<int>(UVcoordinates.x * texture->getSize().x), static_cast<int>(UVcoordinates.y * texture->getSize().y));
	}
	else
	{
		return diffuse;
	}
}

void Material::setNormalMap(sf::Image* newNormalMap)
{
	normalMap = newNormalMap;
}

float Material::getNormalByNormalMap(const sf::Vector2f& UVcoordinates)
{
	if(normalMap)
	{
		sf::Color color = normalMap->getPixel(static_cast<int>(UVcoordinates.x * normalMap->getSize().x), static_cast<int>(UVcoordinates.y * normalMap->getSize().y));
		return (color.r/255+color.g/255+color.b/255)/3.0f;
	}
	else
	{
		return 1.0f;
	}
}

Transform::Transform()
	:position(0.0f, 0.0f, 0.0f),
	scale(1.0f, 1.0f, 1.0f),
	rotation(0.0f, 0.0f, 0.0f)
{
	//
}


Vertex::Vertex()
	:position(0.0f, 0.0f, 0.0f),
	UVposition(0.0f, 0.0f)
{
	//
}


RenderObject::RenderObject(Material& newMaterial)
	:transform(Transform()),
	material(newMaterial)
{

}


//Transform
//SETTER
void RenderObject::setTransform(const Transform& newTransform)
{
	transform = newTransform;
}

//GETTER
Transform& RenderObject::getTransform()
{
	return transform;
}

//Material
//SETTER
void RenderObject::setMaterial(Material& newMaterial)
{
	material = newMaterial;
}

//GETTER
Material& RenderObject::getMaterial()
{
	return material;
}
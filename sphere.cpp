#include <SFML\Graphics.hpp>
#include <math.h>
#include <renderer.h>
#include <renderObject.h>
#include <util.h>
#include <sphere.h>


Sphere::Sphere(Material& newMaterial)
	:RenderObject(newMaterial)
{
}

int Sphere::testRay(const sf::Vector3f& origin, const sf::Vector3f& direction, sf::Vector3f& hitPosition, sf::Vector2f& UVCoordinates)
{
	float factor = -dot((origin-transform.position), direction);
	sf::Vector3f x = origin + factor * direction;
	float distance = sqrt((transform.scale.x/2 * transform.scale.x/2) - squaredLength(x-transform.position));
	if(factor > distance)
	{
		hitPosition = origin + (factor - distance) * direction;
		sf::Vector2f UVs(0.0f, 0.0f);
		if(material.texture)
		{
			sf::Vector3f yAxis(0.0f, 1.0f, 0.0f);
			sf::Vector3f zAxis(0.0f, 0.0f, -1.0f);
			sf::Vector3f normal = getNormal(hitPosition);
			float phi = acos( -dot( yAxis, normal ));
			UVs.y = phi / 3.14f;

			float theta = (acos( dot( normal, zAxis) / sin( phi ))) / ( 2 * 3.14f);
			if ( dot(cross( yAxis, zAxis), normal ) > 0 )
			{
				UVs.x = theta;
			}
			else
			{
				UVs.x = 1 - theta;
			}
		}
		UVCoordinates = UVs;
		return 1;
	}
	else if(factor + distance > 0)
	{
		hitPosition = origin + (factor + distance) * direction;
		return -1;
	}
	else
	{
		return 0;
	}
}


const sf::Vector3f Sphere::getNormal(const sf::Vector3f& point) const
{
	sf::Vector3f normal = point-transform.position;
	return normalize(normal);
}

const sf::Vector3f Sphere::getNormal() const
{
	return sf::Vector3f(0.0f, 0.0f, 0.0f);
}
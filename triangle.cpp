#include <SFML\Graphics.hpp>
#include <math.h>
#include <iostream>
#include <conio.h>
#include <renderer.h>
#include <renderObject.h>
#include <util.h>
#include <triangle.h>


Triangle::Triangle(Material& newMaterial)
	:RenderObject(newMaterial),
	vertices(std::vector<Vertex>(3))
{

}

int Triangle::testRay(const sf::Vector3f& origin, const sf::Vector3f& direction, sf::Vector3f& hitPosition, sf::Vector2f& UVCoordinates)
{
	sf::Vector3f normal = getNormal();
	if(dot(normal, direction)!=0)
	{
		sf::Vector3f vertexPositions[3];
		vertexPositions[0] = vertices.at(0).position + transform.position;
		vertexPositions[1] = vertices.at(1).position + transform.position;
		vertexPositions[2] = vertices.at(2).position + transform.position;
		float factor = dot(normal, vertexPositions[0]-origin)/dot(normal, direction);
		if(factor >= 0)
		{
			hitPosition = origin + direction * factor;
			sf::Vector3f u = vertexPositions[1] - vertexPositions[0];
			sf::Vector3f v = vertexPositions[2] - vertexPositions[0];
			sf::Vector3f w = hitPosition - vertexPositions[0];
			float denominator = (dot(u, v) *  dot(u, v) - dot(u, u) * dot(v, v));
			float s = (dot(u, v) * dot(w, v) - dot(v, v) * dot(w, u)) / denominator;
			float t = (dot(u, v) * dot(w, u) - dot(u, u) * dot(w, v)) / denominator;
			if(s >= 0 && t >= 0 && s + t <= 1)
			{		
				s *= abs(vertices.at(1).UVposition.x - vertices.at(0).UVposition.x);
				t *= abs(vertices.at(2).UVposition.y - vertices.at(0).UVposition.y);
				UVCoordinates = sf::Vector2f(s,t);
				return 1;
			}
		}
	}
	return 0;
}


const sf::Vector3f Triangle::getNormal(const sf::Vector3f& point) const
{
	return normalize(cross(vertices[1].position-vertices[0].position, vertices[2].position-vertices[0].position));
}

const sf::Vector3f Triangle::getNormal() const
{
	return normalize(cross(vertices[1].position-vertices[0].position, vertices[2].position-vertices[0].position));
}

void Triangle::setVertex(unsigned int number, const sf::Vector3f& position)
{
	try
	{
		vertices.at(number).position = position;
	}
	catch(const std::out_of_range& oor)
	{
		 std::cerr<<"Out of Range error: "<< oor.what()<<std::endl;
	}
}

void Triangle::setVertex(unsigned int number,const sf::Vector3f& position, const sf::Vector2f& UVPosition)
{
	try
	{
		vertices.at(number).position = position;
		vertices.at(number).UVposition = UVPosition;
	}
	catch(const std::out_of_range& oor)
	{
		 std::cerr<<"Out of Range error: "<< oor.what()<<std::endl;
	}
}

const Vertex Triangle::getVertex(unsigned int number) const
{
	try
	{
		return vertices.at(number);
	}
	catch(const std::out_of_range& oor)
	{
		 std::cerr<<"Out of Range error: "<< oor.what()<<std::endl;
	}
	return Vertex();
}
#include <SFML\Graphics.hpp>
#include <iostream>
#include <util.h>
#include <renderObject.h>
#include <scene.h>
#include <renderer.h>
#include <thread>
#include <light.h>

Renderer::Renderer(sf::RenderWindow& newWindow)
	:window(newWindow),
	renderObjects(nullptr),
	lights(nullptr),
	position(0.0f, 0.0f, 0.0f),
	direction(0.0f, 0.0f, 1.0f),
	renderResult(),
	backgroundColor(0,0,0),
	pixels(new sf::Uint8[window.getSize().x * window.getSize().y * 4]),
	objectsCount(),
	lightsCount(),
	renderTime(),
	font()
{
	font.loadFromFile("Data/wonderland.ttf");
	objectsCount.setFont(font);
	lightsCount.setFont(font);
	renderTime.setFont(font);
}


void Renderer::renderLine(int line)
{
	for(unsigned int x = 0; x < window.getSize().x; ++x)
		{
			sf::Vector3f curDirection = normalize(sf::Vector3f(x-window.getSize().x/2.0f, window.getSize().y/2.0f-line, 400.0f));
			sf::Color pixelColor = colorAt(position, curDirection, 5);
			pixels[(x + line * window.getSize().x) * 4]     = pixelColor.r;
            pixels[(x + line * window.getSize().x) * 4 + 1] = pixelColor.g;
            pixels[(x + line * window.getSize().x) * 4 + 2] = pixelColor.b;
            pixels[(x + line * window.getSize().x) * 4 + 3] = pixelColor.a;
		}
}

sf::Color Renderer::colorAt(const sf::Vector3f& position, const sf::Vector3f& direction, unsigned int reflectionTimes)
{
	float nearestDistance = 100.0f;
	RenderObject* nearestObject = nullptr;
	sf::Vector3f nearestPoint = position;
	sf::Vector2f nearestUVCoordinates = sf::Vector2f(0.0f, 0.0f);
	for(auto& curObject : *renderObjects)
	{
		sf::Vector3f curPoint;
		sf::Vector2f curUVCoordinates;
		int outside = curObject->testRay(position, direction, curPoint, curUVCoordinates);
		if(outside>0)
		{
			float curDistance = length(curPoint - position);
			if(curDistance < nearestDistance)
			{
				nearestDistance = curDistance;
				nearestObject = curObject;
			}
		}
	}
	sf::Color color = sf::Color::Black;
	if(nearestObject != nullptr)
	{
		nearestObject->testRay(position, direction, nearestPoint, nearestUVCoordinates);
		for(auto& light : *lights)
		{
			float lightRange = light->getRange();
			if(lightRange * lightRange > squaredLength(light->getPosition() - nearestPoint))
			{
				sf::Vector3f normal = nearestObject->getNormal(nearestPoint);
				sf::Vector3f directionToLight = normalize(light->getPosition()-nearestPoint);
				sf::Color curColor = nearestObject->getMaterial().getColorByTexture(nearestUVCoordinates);
				bool lighten = true;
				for(auto& curObject : *renderObjects)
				{
					sf::Vector3f curPoint; //wird übergeben
					sf::Vector2f curUVCoordinates; //wird übergeben
					int outside = curObject->testRay(nearestPoint + 0.00001f * normal , directionToLight, curPoint, curUVCoordinates);
					if(outside>0 && squaredLength(curPoint - nearestPoint) < squaredLength(light->getPosition() - nearestPoint))
					{
						curColor = sf::Color::Black;
						lighten = false;
						break;
					}
				}
				if(lighten)
				{
					float dotProduct = dot(normal, directionToLight);
					if(dotProduct>0)
					{
						curColor = sf::Color(static_cast<sf::Uint8>(curColor.r * dotProduct), 
									static_cast<sf::Uint8>(curColor.g * dotProduct), 
									static_cast<sf::Uint8>(curColor.b * dotProduct));
					}
					else
					{
						curColor = sf::Color::Black;
					}
					float refl = nearestObject->getMaterial().reflection;
					if(refl>0 && reflectionTimes > 0)
					{
							sf::Vector3f reflected = direction - 2.0f * dot(direction, normal) * normal;
							sf::Color reflectedColor = colorAt(nearestPoint, reflected, --reflectionTimes);
							curColor += sf::Color(static_cast<sf::Uint8>(reflectedColor.r * refl), 
										static_cast<sf::Uint8>(reflectedColor.g * refl), 
										static_cast<sf::Uint8>(reflectedColor.b * refl));
					}
				}
				float intensity = light->getIntensity();
				float rangeFactor = (lightRange * lightRange - squaredLength(light->getPosition()-nearestPoint)) / (lightRange * lightRange);
				sf::Color lightColor = light->getColor();
				curColor *= sf::Color(static_cast<sf::Uint8>(lightColor.r * intensity * rangeFactor), 
							static_cast<sf::Uint8>(lightColor.g * intensity * rangeFactor), 
							static_cast<sf::Uint8>(lightColor.b * intensity * rangeFactor));
				color += curColor;
			}
		}
	}
	else
	{
		color = backgroundColor;
	}
	return color;
}

void Renderer::render(Scene* scene)
{
	renderObjects = scene->getRenderObjects();
	lights = scene->getLights();
	sf::Clock clock;
	clock.restart();
	std::vector<std::thread> threads;
	for(unsigned int y = 0; y < window.getSize().y; ++y)
	{
		threads.push_back(std::thread(&Renderer::renderLine, this, y));
	}
	for (auto& th : threads)
	{
		th.join();
	}
	objectsCount.setString(toStr(renderObjects->size())+" objects");
	objectsCount.setPosition(window.getSize().x-objectsCount.getLocalBounds().width, 0);
	lightsCount.setString(toStr(lights->size())+" lights");
	lightsCount.setPosition(window.getSize().x-lightsCount.getLocalBounds().width, 30);
	float time = clock.getElapsedTime().asSeconds();
	renderTime.setString(toStr(time)+"s to render");
	renderTime.setPosition(window.getSize().x-renderTime.getLocalBounds().width, 60);
	sf::Image image;
	image.create(window.getSize().x, window.getSize().y, pixels);
	renderResult.loadFromImage(image);
	window.draw(sf::Sprite(renderResult));
	window.draw(objectsCount);
	window.draw(lightsCount);
	window.draw(renderTime);
}

#ifndef RENDERER_H
#define RENDERER_H


#include <vector>
class RenderObject;
class Light;
class Scene;

class Renderer
{
private:
	sf::RenderWindow& window;
	std::vector<RenderObject*>* renderObjects;
	std::vector<Light*>* lights;
	sf::Vector3f position;
	sf::Vector3f direction;
	sf::Texture renderResult;
	sf::Color backgroundColor;
	sf::Uint8* pixels;
	sf::Text objectsCount;
	sf::Text lightsCount;
	sf::Text renderTime;
	sf::Font font;
public:
	Renderer(sf::RenderWindow& newWindow);
	////////////////////////////////////////////////////////////
	/// Returns the color from a specific direction
	/// position -> startposition of the ray
	/// direction -> direction of the ray)
	/// reflectionTimes -> how often the ray will be reflected when it hits something reflective
	////////////////////////////////////////////////////////////
	sf::Color colorAt(const sf::Vector3f& position, const sf::Vector3f& direction, unsigned int reflectionTimes);
	////////////////////////////////////////////////////////////
	/// Render the picture
	////////////////////////////////////////////////////////////
	void render(Scene* scene);
	////////////////////////////////////////////////////////////
	/// Render one line
	////////////////////////////////////////////////////////////
	void renderLine(int line);

	

};

#endif //RENDERER_H
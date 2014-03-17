#include <iostream>
#include <SFML\Graphics.hpp>
#include <util.h>
#include <renderer.h>
#include <renderObject.h>
#include <sphere.h>
#include <triangle.h>
#include <light.h>
#include <sceneManager.h>
#include <scene.h>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Raytracing");
	sf::Color background(0,50,50);
	Renderer renderer(window);
	SceneManager sceneManager(renderer);
	Scene scene1;
	sceneManager.addScene("Scene1", &scene1);


	//Lichter initilasieren
	PointLight* shadowMaker = new PointLight(sf::Vector3f(-1.0f, 10.0f, 3.0f), sf::Color::White, 20.0f, 1.0f);
	scene1.addLight(shadowMaker);
	PointLight* pointLight = new PointLight(sf::Vector3f(0.5f, 0.5f, 2.9f), sf::Color::Red, 3.0f, 1.0f);
	scene1.addLight(pointLight);
	PointLight* camLight = new PointLight(sf::Vector3f(0.0f, 0.0f, 0.0f), sf::Color::White, 5.0f, 0.25f);
	scene1.addLight(camLight);
	PointLight* pointLight3 = new PointLight(sf::Vector3f(-1.0f, -1.0f, 2.0f), sf::Color::Blue, 2.5f, 0.6f);
	scene1.addLight(pointLight3);
	PointLight* pointLight4 = new PointLight(sf::Vector3f(0.0f, 0.4f, 2.95f), sf::Color::Green, 5.0f, 1.0f);
	scene1.addLight(pointLight4);
	
	//Materials initialisieren
	Material stone;
	stone.diffuse = sf::Color::White;
	stone.reflection = 0.0f;
	sf::Image* image = new sf::Image();
	if(!image->loadFromFile("Data/testTexture.jpg"))
	{
		std::cout<<"Textureloading failed"<<std::endl;
		std::getchar();
		return 0;
	}
	else
	{
		stone.setTexture(image);
	}

	Material metal;
	metal.diffuse = sf::Color::Blue;
	metal.reflection = 0.8f;

	Material material3;
	material3.diffuse = sf::Color::Red;
	material3.reflection = 0.5f;

	Material material4;
	material4.diffuse = sf::Color::Green;
	material4.reflection = 0.2f;
	

	//RenderObjects initialisieren
	
	Sphere sphere1(metal);
	sphere1.getTransform().position = sf::Vector3f(-1.0f, -0.5f, 2.5f);
	scene1.addRenderObject(&sphere1);
	
	Sphere sphere2(material3);
	sphere2.getTransform().position = sf::Vector3f(1.0f, 0.0f, 2.0f);
	scene1.addRenderObject(&sphere2);

	Sphere sphere3(stone);
	sphere3.getTransform().position = sf::Vector3f(-1.0f, 1.5f, 3.0f);
	scene1.addRenderObject(&sphere3);
	
	
	Triangle triangle1(stone);
	triangle1.setVertex(0, sf::Vector3f(0.0f, 0.0f, 0.0f), sf::Vector2f(0.0f, 1.0f));
	triangle1.setVertex(1, sf::Vector3f(2.0f, 0.0f, 0.0f), sf::Vector2f(1.0f, 0.0f));
	triangle1.setVertex(2, sf::Vector3f(0.0f, -2.0f, 0.0f), sf::Vector2f(0.0f, 0.0f));
	triangle1.getTransform().position = sf::Vector3f(-1.0f, 1.0f, 3.0f);
	scene1.addRenderObject(&triangle1);
	sf::Vector3f normal = triangle1.getNormal();
	std::cout<<normal.x<<"|"<<normal.y<<"|"<<normal.z<<std::endl;

	/*
	Triangle triangle2(stone);
	triangle2.setVertex(0, sf::Vector3f(0.0f, 0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f));
	triangle2.setVertex(1, sf::Vector3f(-2.0f, 0.0f, 0.0f), sf::Vector2f(1.0f, 0.0f));
	triangle2.setVertex(2, sf::Vector3f(0.0f, 2.0f, 0.0f), sf::Vector2f(0.0f, 1.0f));
	triangle2.getTransform().position = sf::Vector3f(1.0f, -1.0f, 3.0f);
	scene1.addRenderObject(&triangle2);
	normal = triangle2.getNormal();
	std::cout<<normal.x<<"|"<<normal.y<<"|"<<normal.z<<std::endl;
	*/
	


	
	sf::Event windowEvent;
	while(window.isOpen())
	{
		while(window.pollEvent(windowEvent))
		{
			if(windowEvent.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear(background);
		sceneManager.renderScene("Scene1");
		window.display();
		std::cin.get();
	}
	delete(image);
	return 0;
}
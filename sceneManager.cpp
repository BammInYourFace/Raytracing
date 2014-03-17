#include <SFML\Graphics.hpp>
#include <renderer.h>
#include <scene.h>
#include <map>
#include <sceneManager.h>

SceneManager::SceneManager(Renderer& newRenderer)
	:scenes(),
	renderer(newRenderer)
{
}

void SceneManager::renderScene(std::string sceneName)
{
	renderer.render(scenes.at(sceneName));
}

void SceneManager::addScene(std::string sceneName, Scene* scene)
{
	scenes.insert(std::pair<std::string, Scene*>(sceneName, scene));
}
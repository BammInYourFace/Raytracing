#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

class Renderer;
class Scene;

class SceneManager
{
private:
	std::map<std::string, Scene*> scenes;
	Renderer renderer;
public:
	SceneManager(Renderer& newRenderer);
	void renderScene(std::string sceneName);
	void addScene(std::string sceneName, Scene* scene);
};

#endif //SCENEMANAGER
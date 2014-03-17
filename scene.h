#ifndef SCENE_H
#define SCENE_H

#include <vector>
class RenderObject;
class Light;

class Scene
{
private:
	std::vector<RenderObject*> renderObjects;
	std::vector<Light*> lights;
	//sf::Vector3f position;
	//sf::Vector3f direction;
public:
	Scene();
	~Scene();
	std::vector<RenderObject*>* getRenderObjects();
	std::vector<Light*>* getLights();
	//const Camera& getCamera();

	void addLight(Light* light);

	void addRenderObject(RenderObject* renderObject);
	void deleteRenderObject(const RenderObject& renderObject);
	void deleteAll();
};

#endif //SCENE_H
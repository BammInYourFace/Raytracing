#include <SFML\Graphics.hpp>
#include <renderObject.h>
#include <light.h>
#include <scene.h>

Scene::Scene()
	:renderObjects(),
	lights()
{

}

Scene::~Scene()
{
	deleteAll();
}

std::vector<RenderObject*>* Scene::getRenderObjects()
{
	return &renderObjects;
}

std::vector<Light*>* Scene::getLights()
{
	return &lights;
}


void Scene::addLight(Light* light)
{
	lights.push_back(light);
}

void Scene::addRenderObject(RenderObject* renderObject)
{
	renderObjects.push_back(renderObject);
}


void Scene::deleteRenderObject(const RenderObject& renderObject)
{
	for(std::vector<RenderObject*>::iterator itRenderObjects(renderObjects.begin()), itEnd(renderObjects.end());
		itRenderObjects!=itEnd;
		)
	{
		if(*itRenderObjects == &renderObject)
		{
			delete(*itRenderObjects);
			itRenderObjects = renderObjects.erase(itRenderObjects);
			itEnd = renderObjects.end();
		}
		else
		{
			++itRenderObjects;
		}
	}
}

void Scene::deleteAll()
{
	for(std::vector<RenderObject*>::iterator itRenderObjects(renderObjects.begin()), itEnd(renderObjects.end());
		itRenderObjects!=itEnd;
		)
	{
		delete(*itRenderObjects);
		itRenderObjects = renderObjects.erase(itRenderObjects);
		itEnd = renderObjects.end();
	}
	for(std::vector<Light*>::iterator itLights(lights.begin()), itEnd(lights.end());
		itLights!=itEnd;
		)
	{
		delete(*itLights);
		itLights = lights.erase(itLights);
		itEnd = lights.end();
	}
}

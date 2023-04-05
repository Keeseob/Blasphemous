#pragma once
#include "gameObject.h"
#include "scene.h"
#include "sceneManager.h"
#include "transformation.h"

namespace BP::obj
{
	template <typename T>
	static inline T* instantiate(eLayerType type, eSceneType scenetype)
	{
		T* gobj = new T();
		scene* scn = sceneManager::getActiveScene();
		scn->addGameObject(gobj, type);
		gobj->initialize();

		return gobj;
	}

	template<typename T>
	static inline T* instantiate(vector2 pos, eLayerType type, eSceneType scenetype)
	{
		T* gobj = new T();
		scene* scn = sceneManager::getActiveScene();
		scn->addGameObject(gobj, type);
		gobj->gameObject::getComponent<transformation>()->setPosition(pos);
		gobj->initialize();

		return gobj;
	}

	static void destroy(gameObject* gobj)
	{
		gobj->setState(gameObject::eState::death);
	}
}
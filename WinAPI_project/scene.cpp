#include "scene.h"
#include "sceneManager.h"

namespace BP
{
	scene::scene()
	{
		mLayer.reserve(5);
		mLayer.resize((UINT)eLayerType::end);
	}
	scene::~scene()
	{
	}

	void scene::initialize()
	{
		sceneManager::setActiveScene(this);
	}

	void scene::update()
	{
		for (layer& lyr : mLayer)
		{
			lyr.update();
		}
	}

	void scene::render(HDC hdc)
	{
		for (layer& lyr : mLayer)
		{
			lyr.render(hdc);
		}
	}

	void scene::destroy()
	{
		std::vector<gameObject*> deleteGameObjects = {};
		for (layer& lyr : mLayer)
		{
			std::vector<gameObject*>& gameObjects 
				= lyr.getGameObject();

			for (std::vector<gameObject*>::iterator iter 
				= gameObjects.begin();
				iter != gameObjects.end();)
			{
				if ((*iter)->getState() == gameObject::eState::death)
				{
					deleteGameObjects.push_back((*iter));
					iter = gameObjects.erase(iter);
				}
				else
				{
					iter++;
				}
			}
		}
		for (gameObject* deathObject : deleteGameObjects)
		{
			delete deathObject;
			deathObject = nullptr;
		}
	}

	void scene::release()
	{
	}

	void scene::onEnter()
	{
	}

	void scene::onExit()
	{
	}

	void scene::addGameObject(gameObject* gobj, eLayerType lyr)
	{
		mLayer[(UINT)lyr].addGameObject(gobj);
	}
	std::vector<gameObject*>& scene::getGameObject(eLayerType lyr)
	{
		return mLayer[(UINT)lyr].getGameObject();
	}
}
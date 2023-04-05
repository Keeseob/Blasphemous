#include "layer.h"

namespace BP
{
	layer::layer()
	{
	}
	layer::~layer()
	{
		for (gameObject* gobj: mGameObject)
		{
			delete gobj;
			gobj = nullptr;
		}
	}

	void layer::initialize()
	{
		for (gameObject* gobj : mGameObject)
		{
			if (gobj == nullptr)
			{
				continue;
			}
			if (gobj->getState() != gameObject::eState::active) 
			{
				continue;
			}
			gobj->initialize();
		}
	}
	void layer::update()
	{
		for (gameObject* gobj : mGameObject)
		{
			if (gobj == nullptr)
			{
				continue;
			}
			if (gobj->getState() != gameObject::eState::active)
			{
				continue;
			}
			gobj->update();
		}
	}
	void layer::render(HDC hdc)
	{
		for (gameObject* gobj : mGameObject)
		{
			if (gobj == nullptr)
			{
				continue;
			}
			if (gobj->getState() != gameObject::eState::active)
			{
				continue;
			}
			gobj->render(hdc);
		}
	}
	void layer::release()
	{
		//for (gameObject* gobj : mGameObject)
		//{
		//	if (gobj == nullptr)
		//	{
		//		continue;
		//	}
		//	gobj->release();
		//}
		////
	}
	void layer::addGameObject(gameObject* gobj)
	{
		if (gobj == nullptr)
		{
			return;
		}
		mGameObject.push_back(gobj);
	}
}
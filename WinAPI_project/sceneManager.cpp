#include "sceneManager.h"
#include "actionScene.h"
#include "titleScene.h"
#include "collisionManager.h"
#include "camera.h"
#include "toolScene.h"

namespace BP
{
	std::vector<scene*> sceneManager::mScene = {};
	scene* sceneManager::mActiveScene = nullptr;

	void sceneManager::initialize()
	{
		mScene.resize((UINT)eSceneType::end);
		mScene[(UINT)eSceneType::title] = new titleScene();
		mScene[(UINT)eSceneType::play] = new actionScene();
		mScene[(UINT)eSceneType::tool] = new toolScene();

		for (scene* scn : mScene)
		{
			if (scn == nullptr)
			{
				continue;
			}
			scn->initialize();
		}
		mActiveScene = mScene[(UINT)eSceneType::title];
	}

	void sceneManager::update()
	{
		mActiveScene->update();
	}

	void sceneManager::render(HDC hdc)
	{
		mActiveScene->render(hdc);
	}

	void sceneManager::destroy()
	{
		mActiveScene->destroy();
	}	

	void sceneManager::release()
	{
		for (scene* scn : mScene)
		{
			if (scn == nullptr)
			{
				continue;
			}
			delete scn;
			scn = nullptr;
		}
	}

	void sceneManager::loadScene(eSceneType type)
	{
		camera::clear();
		//ÇöÀç ¾À
		mActiveScene->onExit();
		collisionManager::clear();
		//´ÙÀ½ ¾À
		mActiveScene = mScene[(UINT)type];
		mActiveScene->onEnter();
	}
}
#include "titleScene.h"
#include "keyInput.h"
#include "sceneManager.h"
#include "crisantaMenu_fg_petals.h"
#include "crisanta.h"
#include "crisantaMenu_petals.h"
#include "crisantaBackground.h"
#include "penitentOne.h"
#include "elderBrother.h"
#include "collisionManager.h"
#include "bossBackground.h"
#include "camera.h"
#include "object.h"

namespace BP
{
	titleScene::titleScene()
	{
	}
	titleScene::~titleScene()
	{
	}

	void titleScene::initialize()
	{
		scene::initialize();

		//penitentOne* mPenitentOne = new penitentOne();
		//addGameObject(mPenitentOne, eLayerType::player);

		//obj::instantiate<penitentOne>(eLayerType::player);
		//obj::instantiate<elderBrother>(eLayerType::monster);
		obj::instantiate<crisantaMenu_fg_petals>(eLayerType::effect, eSceneType::title);
		obj::instantiate<crisanta>(eLayerType::test, eSceneType::title);
		obj::instantiate<crisantaMenu_petals>(eLayerType::projectile, eSceneType::title);
		obj::instantiate<crisantaBackground>(eLayerType::background, eSceneType::title);

		//elderBrother* elder = new elderBrother();
		//addGameObject(elder, eLayerType::monster);

		//crisanta* mCrisanta = new crisanta();
		//addGameObject(mCrisanta, eLayerType::test);
		//crisantaBackground* mCrisantaBackground = new crisantaBackground();
		//addGameObject(mCrisantaBackground, eLayerType::background);
	}
	void titleScene::update()
	{
		if (keyInput::getKeyState(eKeyCode::N) == eKeyState::down)
		{
			sceneManager::loadScene(eSceneType::play);
		}
		scene::update();
	}
	void titleScene::render(HDC hdc)
	{
		scene::render(hdc);
	}
	void titleScene::release()
	{
		scene::release();
	}
	void titleScene::onEnter()
	{
		collisionManager::setLayer(eLayerType::player, eLayerType::ground, true);
	}
	void titleScene::onExit()
	{
	}
}
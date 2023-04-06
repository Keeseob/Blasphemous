#include "actionScene.h"
#include "penitentOne.h"
#include "keyInput.h"
#include "sceneManager.h"
#include "elderBrother.h"
#include "collisionManager.h"
#include "bossBackground.h"
#include "transformation.h"
#include "camera.h"
#include "object.h"
#include "ground.h"
#include "application.h"

extern BP::application bp_application; //bp_application객체를 전역 변수 선언

namespace BP
{
	actionScene::actionScene()
	{
	}
	actionScene::~actionScene()
	{
	}

	void actionScene::initialize()
	{
		scene::initialize();

		obj::instantiate<penitentOne>(vector2(300.0f, 600.0f), eLayerType::player, eSceneType::play);
		obj::instantiate<elderBrother>(vector2(900.0f, 550.0f), eLayerType::monster, eSceneType::play);
		obj::instantiate<ground>(vector2(0.0f, 760.0f), eLayerType::ground, eSceneType::play);
		obj::instantiate<bossBackground>(vector2(0.0f, 0.0f), eLayerType::background, eSceneType::play);
	}

	void actionScene::update()
	{
		if (keyInput::getKeyState(eKeyCode::N) == eKeyState::down)
		{
			sceneManager::loadScene(eSceneType::title);
		}
		scene::update();
	}

	void actionScene::render(HDC hdc)
	{
		scene::render(hdc);
	}

	void actionScene::release()
	{
		scene::release();
	}

	void actionScene::onEnter()
	{
		//Camera::SetLookRange(Vector2{ (float)application.GetWidth() * 5.0f, -(float)application.GetHeight() * 5.0f }
		//);
		//Camera::SetTarget(hero);

		collisionManager::setLayer(eLayerType::player, eLayerType::monster, true);
		collisionManager::setLayer(eLayerType::player, eLayerType::ground, true);
		collisionManager::setLayer(eLayerType::monster, eLayerType::ground, true);
	}

	void actionScene::onExit()
	{
		//camera::setViewRange(vector2::zero);
		//camera::setTarget(nullptr);
		//mPenitentOne->setPosition(vector2{ 0.0f, 0.0f });
	}
}

#include "elderBrother.h"
#include "time.h"
#include "sceneManager.h"
#include "keyInput.h"
#include "bpResources.h"
#include "transformation.h"
#include "animator.h"
#include "collider.h"
#include "projectile.h"
#include "scene.h"
#include "animator.h"

namespace BP
{
	elderBrother::elderBrother()
	{
	}
	elderBrother::~elderBrother()
	{
	}

	void elderBrother::initialize()
	{
		//몬스터 위치와 크기
		//transformation* trns = getComponent<transformation>();
		//trns->setPosition(vector2(1600.0f, 900.0f));
		//trns->setScale(vector2(2.5f, 2.5f));

		mAnimator = addComponent<animator>();
		mAnimator->createAnimations(L"..\\Resource\\elderBrother_anim"
			, vector2::zero, 0.1f);
		
		mAnimator->play(L"ResourceelderBrother_anim", true);
		collider* coll = addComponent<collider>();
		coll->setCenter(vector2(70.0f, -50.0f));
		coll->setSize(vector2(170.0f, 240.0f));

		gameObject::initialize();
	}
	void elderBrother::update()
	{
		gameObject::update();
	}
	void elderBrother::render(HDC hdc)
	{

		gameObject::render(hdc);
	}
	void elderBrother::release()
	{
		gameObject::release();
	}
}
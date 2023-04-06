#include "crisanta.h"
#include "sceneManager.h"
#include "bpResources.h"
#include "animation.h"
#include "animator.h"
#include "scene.h"

namespace BP
{
	crisanta::crisanta()
	{
	}
	crisanta::~crisanta()
	{
	}

	void crisanta::initialize()
	{
		mAnimator = addComponent<animator>();
		mAnimator->createAnimations(L"..\\Resource\\crisantaMenu_anim", vector2(400.0f, 500.0f), 0.2f);
		mAnimator->play(L"ResourcecrisantaMenu_anim", true);

		gameObject::initialize();
	}

	void crisanta::update()
	{
		gameObject::update();
	}

	void crisanta::render(HDC hdc)
	{
		gameObject::render(hdc);
		//transformation* trns = getComponent<transformation>();
		//vector2 pos = trns->getPosition();

		//TransparentBlt(hdc, pos.x, pos.y
		//	, mCrisantaImage->getWidth() * 2.5f
		//	, mCrisantaImage->getHeight() * 2.5f
		//	, mCrisantaImage->getHdc(), 0, 0
		//	, mCrisantaImage->getWidth()
		//	, mCrisantaImage->getHeight()
		//	, RGB(255, 0, 255));
	}

	void crisanta::release()
	{
		gameObject::release();
	}
}

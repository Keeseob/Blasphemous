#include "crisanta.h"
#include "sceneManager.h"
#include "bpResources.h"
#include "transformation.h"
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
		//mCrisantaImage = bpResources::load<image>(L"crisanta", L"..\\Resource\\crisantaMenu_anim\\crisanta-main-menu-animation_0013_Capa-1.bmp");
		//image* Crisanta = bpResources::load<image>(L"crisantaMenu_anim_p", L"..\\Resource\\crisantaMenu_anim_p.bmp");
		mCrisantaImage = bpResources::load<image>(L"crisantaMenu_anim_p", L"..\\Resource\\crisantaMenu_anim\\crisanta-main-menu-animation_0013_Capa-1.bmp");

		//mAnimator->createAnimations(L"..\\Resource\\crisantaMenu_anim", vector2(0,0), 0.1f);
		transformation* trns = getComponent<transformation>();
		//mAnimator = addComponent<animator>();
		////mAnimator = addComponent<animator>();
		////mAnimator->createAnimations(L"..\\Resource\\crisantaMenu_anim", vector2::zero, 0.1f);
		//mAnimator->createAnimation(L"crisantaMenu_anim_p", Crisanta, vector2::zero, 0, 5, 5, vector2(0.0f, 0.0f), 0.1);
		//mAnimator->play(L"crisantaMenu_anim_p", true);

		vector2 pos = trns->getPosition();

		trns->setPosition(pos);

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

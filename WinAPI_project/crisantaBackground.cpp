#include "crisantaBackground.h"
#include "sceneManager.h"
#include "bpResources.h"
#include "animator.h"

namespace BP
{
	crisantaBackground::crisantaBackground()
	{
	}
	crisantaBackground::~crisantaBackground()
	{
	}

	void crisantaBackground::initialize()
	{
		mAnimator = addComponent<animator>();
		mAnimator->createAnimations(L"..\\Resource\\crisantaBackground", vector2(400.0f, 500.0f), 0.2f);
		mAnimator->play(L"ResourcecrisantaBackground", true);

		gameObject::initialize();
	}

	void crisantaBackground::update()
	{
		gameObject::update();
	}

	void crisantaBackground::render(HDC hdc)
	{
		gameObject::render(hdc);
	/*	transformation* trns = getComponent<transformation>();
		vector2 pos = trns->getPosition();

		TransparentBlt(hdc, pos.x, pos.y
			, mImage->getWidth() * 2.5f
			, mImage->getHeight() * 2.5f
			, mImage->getHdc(), 0, 0
			, mImage->getWidth()
			, mImage->getHeight()
			, RGB(255, 0, 255));*/
	}

	void crisantaBackground::release()
	{
		gameObject::release();
	}
}

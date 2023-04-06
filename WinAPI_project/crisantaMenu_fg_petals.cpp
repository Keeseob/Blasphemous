#include "crisantaMenu_fg_petals.h"
#include "sceneManager.h"
#include "bpResources.h"
#include "animator.h"

namespace BP
{
	crisantaMenu_fg_petals::crisantaMenu_fg_petals()
	{
	}
	crisantaMenu_fg_petals::~crisantaMenu_fg_petals()
	{
	}

	void crisantaMenu_fg_petals::initialize()
	{
		mAnimator = addComponent<animator>();
		mAnimator->createAnimations(L"..\\Resource\\crisantaMenu_fg_petals", vector2(400.0f, 500.0f), 0.12f);
		mAnimator->play(L"ResourcecrisantaMenu_fg_petals", true);

		gameObject::initialize();
	}

	void crisantaMenu_fg_petals::update()
	{
		gameObject::update();
	}

	void crisantaMenu_fg_petals::render(HDC hdc)
	{
		gameObject::render(hdc);
	}

	void crisantaMenu_fg_petals::release()
	{
		gameObject::release();
	}
}
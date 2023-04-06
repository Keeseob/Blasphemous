#include "crisantaMenu_petals.h"
#include "sceneManager.h"
#include "bpResources.h"
#include "animator.h"

namespace BP
{
	crisantaMenu_petals::crisantaMenu_petals()
	{
	}
	crisantaMenu_petals::~crisantaMenu_petals()
	{
	}

	void crisantaMenu_petals::initialize()
	{
		mAnimator = addComponent<animator>();
		mAnimator->createAnimations(L"..\\Resource\\crisantaMenu_petals", vector2(400.0f, 500.0f), 0.081f);
		mAnimator->play(L"ResourcecrisantaMenu_petals", true);

		gameObject::initialize();
	}

	void crisantaMenu_petals::update()
	{
		gameObject::update();
	}

	void crisantaMenu_petals::render(HDC hdc)
	{
		gameObject::render(hdc);
	}

	void crisantaMenu_petals::release()
	{
		gameObject::release();
	}
}
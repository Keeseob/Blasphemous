#include "brotherhoodForeground.h"
#include "sceneManager.h"
#include "bpResources.h"
#include "transformation.h"
#include "keyInput.h"
#include "time.h"

namespace BP
{
	brotherhoodForeground::brotherhoodForeground()
	{
	}
	brotherhoodForeground::~brotherhoodForeground()
	{
	}

	void brotherhoodForeground::initialize()
	{
		transformation* trns = getComponent<transformation>();
		mImage = bpResources::load<image>(L"brotherhood_foreground", L"..\\Resource\\background\\brotherhood\\brotherhood_foreground.bmp");

		vector2 pos = trns->getPosition();
		trns->setPosition(vector2(pos.x, pos.y - 20));

		mState = eBackgroundtState::bgRight;

		gameObject::initialize();
	}

	void brotherhoodForeground::update()
	{
		switch (mState)
		{
		case BP::brotherhoodForeground::eBackgroundtState::bgRight:bgRight();
			break;
		case BP::brotherhoodForeground::eBackgroundtState::bgLeft:bgLeft();
			break;
		default:
			break;
		}

		gameObject::update();
	}

	void brotherhoodForeground::render(HDC hdc)
	{
		transformation* trns = getComponent<transformation>();
		vector2 pos = trns->getPosition();

		TransparentBlt(hdc, pos.x, pos.y
			, mImage->getWidth() * 1.0f
			, mImage->getHeight() * 1.0f
			, mImage->getHdc(), 0, 0
			, mImage->getWidth()
			, mImage->getHeight()
			, RGB(255, 0, 255));

		gameObject::render(hdc);
	}

	void brotherhoodForeground::release()
	{
		gameObject::release();
	}

	void brotherhoodForeground::bgRight()
	{
		transformation* trns = getComponent<transformation>();
		vector2 pos = trns->getPosition();

		if (keyInput::getKey(eKeyCode::A))
		{
			mState = eBackgroundtState::bgLeft;
		}
		if (keyInput::getKey(eKeyCode::D))
		{
			//mRigidBody->addForce(vector2(100.0f, 0.0f));
			pos.x -= 50.0f * time::deltaTime();
		}
		trns->setPosition(pos);
	}

	void brotherhoodForeground::bgLeft()
	{
		transformation* trns = getComponent<transformation>();
		vector2 pos = trns->getPosition();

		if (keyInput::getKey(eKeyCode::D))
		{
			mState = eBackgroundtState::bgRight;
		}
		if (keyInput::getKey(eKeyCode::A))
		{
			//mRigidBody->addForce(vector2(100.0f, 0.0f));
			pos.x += 50.0f * time::deltaTime();
		}
		trns->setPosition(pos);
	}
}

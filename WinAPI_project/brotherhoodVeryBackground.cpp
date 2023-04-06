#include "brotherhoodVeryBackground.h"
#include "sceneManager.h"
#include "bpResources.h"
#include "transformation.h"
#include "keyInput.h"
#include "time.h"

namespace BP
{
	brotherhoodVeryBackground::brotherhoodVeryBackground()
	{
	}
	brotherhoodVeryBackground::~brotherhoodVeryBackground()
	{
	}

	void brotherhoodVeryBackground::initialize()
	{
		transformation* trns = getComponent<transformation>();
		mImage = bpResources::load<image>(L"brotherhood_very_background", L"..\\Resource\\brotherhood_background2\\brotherhood_very_background.bmp");

		vector2 pos = trns->getPosition();
		trns->setPosition(vector2(pos.x - 100, pos.y - 20));

		mState = eBackgroundtState::bgRight;

		gameObject::initialize();
	}

	void brotherhoodVeryBackground::update()
	{
		switch (mState)
		{
		case BP::brotherhoodVeryBackground::eBackgroundtState::bgRight:bgRight();
			break;
		case BP::brotherhoodVeryBackground::eBackgroundtState::bgLeft:bgLeft();
			break;
		default:
			break;
		}

		gameObject::update();
	}

	void brotherhoodVeryBackground::render(HDC hdc)
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

	void brotherhoodVeryBackground::release()
	{
		gameObject::release();
	}

	void brotherhoodVeryBackground::bgRight()
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
			pos.x -= 20.0f * time::deltaTime();
		}
		trns->setPosition(pos);
	}

	void brotherhoodVeryBackground::bgLeft()
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
			pos.x += 20.0f * time::deltaTime();
		}
		trns->setPosition(pos);
	}
}

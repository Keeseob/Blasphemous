#include "brotherhoodBackground2.h"
#include "sceneManager.h"
#include "bpResources.h"
#include "transformation.h"
#include "keyInput.h"
#include "time.h"

namespace BP
{
	brotherhoodBackground2::brotherhoodBackground2()
	{
	}
	brotherhoodBackground2::~brotherhoodBackground2()
	{
	}

	void brotherhoodBackground2::initialize()
	{
		transformation* trns = getComponent<transformation>();
		mImage = bpResources::load<image>(L"brotherhood_background2", L"..\\Resource\\brotherhood_background2\\brotherhood_background2.bmp");

		vector2 pos = trns->getPosition();
		trns->setPosition(vector2(pos.x - 100, pos.y - 20));

		mState = eBackgroundtState::bgRight;

		gameObject::initialize();
	}

	void brotherhoodBackground2::update()
	{
		switch (mState)
		{
		case BP::brotherhoodBackground2::eBackgroundtState::bgRight:bgRight();
			break;
		case BP::brotherhoodBackground2::eBackgroundtState::bgLeft:bgLeft();
			break;
		default:
			break;
		}

		gameObject::update();
	}

	void brotherhoodBackground2::render(HDC hdc)
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

	void brotherhoodBackground2::release()
	{
		gameObject::release();
	}

	void brotherhoodBackground2::bgRight()
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
			pos.x -= 30.0f * time::deltaTime();
		}
		trns->setPosition(pos);
	}

	void brotherhoodBackground2::bgLeft()
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
			pos.x += 30.0f * time::deltaTime();
		}
		trns->setPosition(pos);
	}
}

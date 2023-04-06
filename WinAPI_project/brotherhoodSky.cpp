#include "brotherhoodSky.h"
#include "sceneManager.h"
#include "bpResources.h"
#include "transformation.h"
#include "keyInput.h"
#include "time.h"

namespace BP
{
	brotherhoodSky::brotherhoodSky()
	{
	}
	brotherhoodSky::~brotherhoodSky()
	{
	}

	void brotherhoodSky::initialize()
	{
		transformation* trns = getComponent<transformation>();
		mImage = bpResources::load<image>(L"brotherhoodSky", L"..\\Resource\\brotherhood_background2\\brotherhood_Sky.bmp");

		vector2 pos = trns->getPosition();
		trns->setPosition(vector2(pos.x - 100, pos.y - 20));

		mState = eBackgroundtState::bgRight;

		gameObject::initialize();
	}

	void brotherhoodSky::update()
	{
		switch (mState)
		{
		case BP::brotherhoodSky::eBackgroundtState::bgRight:bgRight();
			break;
		case BP::brotherhoodSky::eBackgroundtState::bgLeft:bgLeft();
			break;
		default:
			break;
		}

		gameObject::update();
	}

	void brotherhoodSky::render(HDC hdc)
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

	void brotherhoodSky::release()
	{
		gameObject::release();
	}

	void brotherhoodSky::bgRight()
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

	void brotherhoodSky::bgLeft()
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

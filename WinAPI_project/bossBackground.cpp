#include "bossBackground.h"
#include "sceneManager.h"
#include "bpResources.h"
#include "transformation.h"
#include "keyInput.h"
#include "time.h"

namespace BP
{
	bossBackground::bossBackground()
	{
	}
	bossBackground::~bossBackground()
	{
	}

	void bossBackground::initialize()
	{
		transformation* trns = getComponent<transformation>();
		mImage = bpResources::load<image>(L"bossBackground", L"..\\Resource\\background\\brotherhood\\brotherhood_background.bmp");

		vector2 pos = trns->getPosition();
		trns->setPosition(vector2(pos.x, pos.y - 20));

		mState = eBackgroundtState::bgRight;

		gameObject::initialize();
	}

	void bossBackground::update()
	{
		switch (mState)
		{
		case BP::bossBackground::eBackgroundtState::bgRight:bgRight();
			break;
		case BP::bossBackground::eBackgroundtState::bgLeft:bgLeft();
			break;
		default:
			break;
		}

		gameObject::update();
	}

	void bossBackground::render(HDC hdc)
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

	void bossBackground::release()
	{
		gameObject::release();
	}

	void bossBackground::bgRight()
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
			//pos.x += 20.0f * time::deltaTime();
		}
		trns->setPosition(pos);
	}

	void bossBackground::bgLeft()
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
			//pos.x -= 20.0f * time::deltaTime();
		}
		trns->setPosition(pos);
	}
}

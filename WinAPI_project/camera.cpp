#include "camera.h"
#include "application.h"
#include "gameObject.h"
#include "transformation.h"
#include "keyInput.h"
#include "time.h"
#include "image.h"

extern BP::application bp_application;

namespace BP
{
	vector2 camera::mResolution = vector2::zero;
	vector2 camera::mLookPosition = vector2::zero;
	vector2 camera::mDistance = vector2::zero;
	vector2 camera::mViewRange = vector2::zero;
	gameObject* camera::mTarget = nullptr;

	camera::eCameraEffectType camera::mType = camera::eCameraEffectType::none;
	class image* camera::mCurtain = nullptr;
	float camera::mCurtainAlpha = 1.0f;
	float camera::mAlphaTime = 0.0f;
	float camera::mEndTime = 5.0f;

	void camera::initialize()
	{
		mResolution.x = bp_application.getWidth();
		mResolution.y = bp_application.getHeight();
		mLookPosition = (mResolution / 2.0f);

		mType = eCameraEffectType::fadeIn;
		mCurtain = image::create(L"curtain", mResolution.x, mResolution.y, RGB(0, 0, 0));
	}

	void camera::update()
	{
		if (keyInput::getKey(eKeyCode::left))
		{
			mLookPosition.x -= 100.0f * time::deltaTime();
		}
		if (keyInput::getKey(eKeyCode::right))
		{
			mLookPosition.x += 100.0f * time::deltaTime();
		}
		if (keyInput::getKey(eKeyCode::up))
		{
			mLookPosition.y -= 100.0f * time::deltaTime();
		}
		if (keyInput::getKey(eKeyCode::down))
		{
			mLookPosition.y += 100.0f * time::deltaTime();
		}

		if (mTarget != nullptr)
		{
			mLookPosition = mTarget->getComponent<transformation>()->getPosition();
		}

		//if (mLookPosition.x <= (mResolution.x / 2.0f))
		//	mLookPosition.x = (mResolution.x / 2.0f);
		//if (mLookPosition.x >= mViewRange.x - mResolution.x / 2.0f)
		//	mLookPosition.x = mViewRange.x - mResolution.x / 2.0f;
		//if (mLookPosition.y <= mViewRange.y + mResolution.y / 2.0f)
		//	mLookPosition.y = mViewRange.y + mResolution.y / 2.0f;
		//if (mLookPosition.y >= (mResolution.y / 2.0f))
		//	mLookPosition.y = (mResolution.y / 2.0f);

		mDistance = mLookPosition - (mResolution / 2.0f);



		if (mAlphaTime < mEndTime)
		{
			//255 = 1
			mAlphaTime += time::deltaTime();
			float ratio = (mAlphaTime / mEndTime);

			if (mType == eCameraEffectType::fadeIn)
			{
				mCurtainAlpha = 1.0 - ratio;
			}
			else if (mType == eCameraEffectType::fadeOut)
			{
				mCurtainAlpha = ratio;
			}
			else
			{

			}
		}
	}

	void camera::render(HDC hdc)
	{
		if (mAlphaTime < mEndTime && mType == eCameraEffectType::fadeIn)
		{
			BLENDFUNCTION blend = {};
			blend.BlendOp = AC_SRC_OVER;
			blend.BlendFlags = 0;
			blend.AlphaFormat = 0;
			blend.SourceConstantAlpha = (BYTE)(255.0f * mCurtainAlpha); //Åõ¸íµµ 0~255

			AlphaBlend(hdc, 0, 0
				, mResolution.x
				, mResolution.y
				, mCurtain->getHdc()
				, 0, 0
				, mCurtain->getWidth(), mCurtain->getHeight()
				, blend);
		}
	}

	void camera::clear()
	{
		mResolution.x = bp_application.getWidth();
		mResolution.y = bp_application.getHeight();
		mLookPosition = (mResolution / 2.0f);
		mDistance = vector2::zero;
	}
}
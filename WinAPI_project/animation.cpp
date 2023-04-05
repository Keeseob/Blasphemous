#include "animation.h"
#include "time.h"
#include "image.h"
#include "animator.h"
#include "transformation.h"
#include "gameObject.h"
#include "camera.h"

namespace BP
{
	animation::animation()
		: mAnimator(nullptr)
		, mSheetImage(nullptr)
		, mTime(0.0f)
		, mbComplete(false)
		, mSpriteIndex(0)
		, mAnimationName(L"")
	{
	}
	animation::~animation()
	{
	}

	void animation::initialize()
	{
	}

	void animation::update()
	{
		if (mbComplete == true)
		{
			return;
		}
		mTime += time::deltaTime();
		if (mSpriteSheet[mSpriteIndex].duration < mTime)
		{
			mTime = 0.0f;
			if (mSpriteSheet.size() <= mSpriteIndex + 1)
			{
				mbComplete = true;
			}
			else
			{
				mSpriteIndex++;
			}
		}
	}

	void animation::render(HDC hdc)
	{
		transformation* trns = mAnimator->getOwner()->getComponent<transformation>();
		vector2 scale = trns->getScale();

		//이미지는 위, 중간
		//캐릭터 발 기준 위치 계산
		vector2 pos = trns->getPosition();
		pos = camera::calculatePosition(pos);
		pos += mSpriteSheet[mSpriteIndex].offset;
		pos.x -= mSpriteSheet[mSpriteIndex].size.x / 2.0f;
		pos.y -= mSpriteSheet[mSpriteIndex].size.y;

		TransparentBlt(hdc, pos.x, pos.y
			, mSpriteSheet[mSpriteIndex].size.x * scale.x
			, mSpriteSheet[mSpriteIndex].size.y * scale.y
			, mSheetImage->getHdc()
			, mSpriteSheet[mSpriteIndex].leftTop.x, mSpriteSheet[mSpriteIndex].leftTop.y
			, mSpriteSheet[mSpriteIndex].size.x, mSpriteSheet[mSpriteIndex].size.y
			, RGB(255, 0, 255));

		//알파 블랜드
		//BLENDFUNCTION blend = {};
		//blend.BlendOp = AC_SRC_OVER;
		//blend.BlendFlags = 0;
		//blend.AlphaFormat = AC_SRC_ALPHA;
		//blend.SourceConstantAlpha = 255; //투명도 0~255
		//
		//AlphaBlend(hdc, pos.x, pos.y
		//	, mSpriteSheet[mSpriteIndex].size.x * scale.x
		//	, mSpriteSheet[mSpriteIndex].size.y * scale.y
		//	, mSheetImage->getHdc()
		//	, mSpriteSheet[mSpriteIndex].leftTop.x, mSpriteSheet[mSpriteIndex].leftTop.y
		//	, mSpriteSheet[mSpriteIndex].size.x, mSpriteSheet[mSpriteIndex].size.y
		//	, blend);
	}

	void animation::create(image* sheet, vector2 leftTop
		, UINT coulmn, UINT row, UINT spriteLength
		, vector2 offset, float duration)
	{
		mSheetImage = sheet;
		//UINT coulmn = mSheetImage->gerWidth() / size.x;
		vector2 size = vector2::one;
		size.x = mSheetImage->getWidth() / (float)coulmn;
		size.y = mSheetImage->getHeight() / (float)row;

		for (int i = 0; i < spriteLength; i++)
		{
			sprite spriteInfo;

			spriteInfo.leftTop.x = leftTop.x + (size.x * i);
			spriteInfo.leftTop.y = leftTop.y;
			spriteInfo.size = size;
			spriteInfo.offset = offset;
			spriteInfo.duration = duration;

			mSpriteSheet.push_back(spriteInfo);
		}
	}

	void animation::reset()
	{
		mSpriteIndex = 0;
		mTime = 0.0f;
		mbComplete = false;
	}
}
#pragma once
#include "entity.h"

namespace BP
{
	class image;
	class animator;
	class animation : public entity
	{
	public:
		struct sprite
		{
			vector2 leftTop; //게임에서는 0,0으로 지정하면 정확하게는 맞지 않는다.
			vector2 size;
			vector2 offset;
			float duration;

			sprite() :
				leftTop(vector2::zero)
				, size(vector2::zero)
				, offset(vector2::zero)
				, duration(0.0f)
			{
			}
		};

		animation();
		~animation();

		void initialize();
		void update();
		void render(HDC hdc);
		void create(image* sheet, vector2 leftTop, UINT coulmn, UINT row, UINT spriteLength, vector2 offset, float duration);
		void reset();

		bool isComplete() { return mbComplete; }
		void setAnimator(animator* anit) { mAnimator = anit; }
		void setAnimationName(const std::wstring& name) { mAnimationName = name; }
		std::wstring& getAnimationName() { return mAnimationName; }

	private:
		animator* mAnimator;
		image* mSheetImage;
		std::vector<sprite> mSpriteSheet;
		std::wstring mAnimationName;
		float mTime;
		bool mbComplete;
		int mSpriteIndex;
	};
}
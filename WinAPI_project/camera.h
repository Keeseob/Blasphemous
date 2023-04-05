#pragma once
#include "engine.h"
#include "application.h"

extern BP::application bp_application;

namespace BP
{
	class gameObject;
	class camera
	{
	public:
		enum class eCameraEffectType
		{
			none,
			fadeIn,
			fadeOut,
			end,
		};

		static void initialize();
		static void update();
		static void render(HDC hdc);
		static void clear();
		static void setTarget(gameObject* trg) { mTarget = trg; }
		static vector2 calculatePosition(vector2 pos) { return pos - mDistance; }
	private:
		static vector2 mResolution;
		static vector2 mLookPosition;
		static vector2 mDistance;
		static gameObject* mTarget;
		static vector2 mViewRange;

		static eCameraEffectType mType;
		static class image* mCurtain;
		static float mCurtainAlpha;
		static float mAlphaTime;
		static float mEndTime;
	};
}
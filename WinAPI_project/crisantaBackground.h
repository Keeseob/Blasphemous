#pragma once
#include "gameObject.h"
#include "image.h"

namespace BP
{
	class animator;
	class crisantaBackground : public gameObject
	{
	public:
		crisantaBackground();
		~crisantaBackground();

		virtual void initialize() override;
		virtual void update() override;
		virtual void render(HDC hdc) override;
		virtual void release() override;

	private:
		animator* mAnimator;
		image* mImage;
	};
}
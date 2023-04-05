#pragma once
#include "gameObject.h"

namespace BP
{
	class animator;
	class elderBrother : public gameObject
	{
	public:
		elderBrother();
		~elderBrother();

		virtual void initialize() override;
		virtual void update() override;
		virtual void render(HDC hdc) override;
		virtual void release() override;

	private:
		animator* mAnimator;
	};
}
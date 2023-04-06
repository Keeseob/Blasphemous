#pragma once
#include "gameObject.h"
#include "image.h"

namespace BP
{
	class animator;
	class crisantaMenu_petals : public gameObject
	{
	public:
		crisantaMenu_petals();
		~crisantaMenu_petals();

		virtual void initialize() override;
		virtual void update() override;
		virtual void render(HDC hdc) override;
		virtual void release() override;

	private:
		animator* mAnimator;
	};
}
#pragma once
#include "gameObject.h"
#include "image.h"

namespace BP
{
	class animator;
	class crisanta : public gameObject
	{
	public:
		crisanta();
		~crisanta();

		virtual void initialize() override;
		virtual void update() override;
		virtual void render(HDC hdc) override;
		virtual void release() override;

	private:
		animator* mAnimator;
	};
}
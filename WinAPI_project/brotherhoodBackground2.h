#pragma once
#include "gameObject.h"
#include "image.h"

namespace BP
{
	class rigidBody;
	class brotherhoodBackground2 : public gameObject
	{
	public:
		enum class eBackgroundtState
		{
			bgRight,
			bgLeft,
		};
		brotherhoodBackground2();
		~brotherhoodBackground2();

		virtual void initialize() override;
		virtual void update() override;
		virtual void render(HDC hdc) override;
		virtual void release() override;

	private:
		image* mImage;
		eBackgroundtState mState;
		rigidBody* mRigidBody;
		void bgRight();
		void bgLeft();
	};
}
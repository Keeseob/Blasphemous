#pragma once
#include "gameObject.h"
#include "image.h"

namespace BP
{
	class rigidBody;
	class bossBackground : public gameObject
	{
	public:
		enum class eBackgroundtState
		{
			bgRight,
			bgLeft,
		};
		bossBackground();
		~bossBackground();

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
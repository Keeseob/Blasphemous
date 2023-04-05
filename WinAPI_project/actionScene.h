#pragma once
#include "scene.h"

namespace BP
{
	class penitentOne;
	class bossBackground;
	class actionScene : public scene
	{
	public:
		actionScene();
		~actionScene();

		virtual void initialize() override;
		virtual void update() override;
		virtual void render(HDC hdc) override;
		virtual void release() override;

		virtual void onEnter() override;
		virtual void onExit() override;

	private:
		penitentOne* mPenitentOne;
		bossBackground* mBossBackground;
	};
}


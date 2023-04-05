#pragma once
#include "scene.h"

namespace BP
{
	class crisanta;
	class crisantaBackground;
	class titleScene : public scene
	{
	public:
		titleScene();
		~titleScene();

		virtual void initialize() override;
		virtual void update() override;
		virtual void render(HDC hdc) override;
		virtual void release() override;

		virtual void onEnter() override;
		virtual void onExit() override;

	private:
		crisanta* mCrisanta;
		crisantaBackground* mCrisantaBackground;
	};
}
#pragma once
#include "scene.h"

namespace BP
{
	class toolScene : public scene
	{
		public:
			toolScene();
			virtual ~toolScene();

			virtual void initialize() override;
			virtual void update() override;
			virtual void render(HDC hdc) override;
			virtual void release() override;

			virtual void onEnter() override;
			virtual void onExit() override;
		private:
	};
}
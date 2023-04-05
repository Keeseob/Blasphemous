#pragma once
#include "scene.h"

namespace BP
{
	class sceneManager
	{
	public:
		static void initialize();
		static void update();
		static void render(HDC hdc);
		static void destroy();
		static void release();

		static void loadScene(eSceneType type);
		static scene* getActiveScene() { return mActiveScene; }
		static void setActiveScene(scene* scn) { mActiveScene = scn; }

	private:
		static std::vector<scene*> mScene;
		static scene* mActiveScene;
	};
}
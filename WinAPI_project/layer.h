#pragma once
#include "entity.h"
#include "gameObject.h"

namespace BP
{
	class layer : public entity
	{
	public:
		layer();
		virtual ~layer();

		virtual void initialize();
		virtual void update();
		virtual void render(HDC hdc);
		virtual void release();

		void addGameObject(gameObject* gobj);
		std::vector<gameObject*>& getGameObject() { return mGameObject; }
	private:
		std::vector<gameObject*> mGameObject;
	};
}
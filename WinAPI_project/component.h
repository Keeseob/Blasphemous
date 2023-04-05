#pragma once
#include "entity.h"

namespace BP
{
	class gameObject;
	class component : public entity
	{
	public:
		component(eComponentType type);
		~component();

		virtual void initialize();
		virtual void update();
		virtual void render(HDC hdc);
		virtual void release();

		eComponentType getType() { return mType; }
		void setOwner(gameObject* owner) { mOwner = owner; }
		gameObject* getOwner() { return mOwner; }

	private:
		const eComponentType mType;
		gameObject* mOwner;
	};
}

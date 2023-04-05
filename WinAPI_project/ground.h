#pragma once
#include"gameObject.h"

namespace BP
{
	class ground : public gameObject
	{
	public:
		ground();
		virtual ~ground();

		virtual void initialize();
		virtual void update();
		virtual void render(HDC hdc);
		virtual void release();

		virtual void onCollisionEnter(class collider* other);
		virtual void onCollisionStay(class collider* other);
		virtual void onCollisionExit(class collider* other);

	private:
		class collider* mCollider;
	};
}
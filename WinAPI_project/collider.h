#pragma once
#include"component.h"

namespace BP
{
	class collider : public component
	{
	public:
		collider();
		~collider();

		virtual void initialize() override;
		virtual void update() override;
		virtual void render(HDC hdc) override;
		virtual void release() override;

		virtual void onCollisionEnter(collider* other);
		virtual void onCollisionStay(collider* other);
		virtual void onCollisionExit(collider* other);

		void setCenter(vector2 center) { mCenter = center; };
		void setSize(vector2 size) { mSize = size; };
		vector2 getPosition() { return mPosition; }
		vector2 getSize() { return mSize; }
		UINT getID() { return mID; }
		void clearCollisionCount() { mCollisionCount = 0; }

	private:
		static UINT colliderNumber;
		UINT mCollisionCount;
		UINT mID;
		vector2 mCenter;
		vector2 mSize;
		vector2 mPosition;
	};
}
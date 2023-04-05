#pragma once
#include "component.h"

namespace BP
{
	class rigidBody : public component
	{
	public:
		rigidBody();
		~rigidBody();

		virtual void initialize() override;
		virtual void update() override;
		virtual void render(HDC hdc) override;
		virtual void release() override;

		void setMass(float mass) { mMass = mass; };
		void addForce(vector2 force);
		void setGround(bool ground) { mbGround = ground; }
		void setVelocity(vector2 velocity) { mVelocity = velocity; }
		vector2 getVelocity() { return mVelocity; }

	private:
		float mMass;
		vector2 mForce;
		vector2 mAcceleration;
		vector2 mVelocity;
		vector2 mVelocityLimt;

		vector2 mGravity;
		float mFriction;
		bool mbGround;

		//float mKineticFriction;
		//float mCoefficientFriction;
		//float mNormalForce;
	};
}
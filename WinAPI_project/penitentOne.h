#pragma once
#include "gameObject.h"
#include "image.h"

namespace BP
{
	class rigidBody;
	class animator;
	class penitentOne : public gameObject
	{
	public:
		enum class ePenitentState
		{
			idleRight,
			idleLeft,

			runRight_start,
			runLeft_start,

			runRight,
			runLeft,

			jumpRight,
			jumpLeft,

			crouchRight,
			crouchLeft,

			attack,
			attackL,
			jumpAttack,

			death,
		};

		penitentOne();
		~penitentOne();

		virtual void initialize() override;
		virtual void update() override;
		virtual void render(HDC hdc) override;
		virtual void release() override;

		virtual void onCollisionEnter(class collider* other) override;
		virtual void onCollisionStay(class collider* other) override;
		virtual void onCollisionExit(class collider* other) override;

	private:
		void idleRight();
		void idleLeft();

		void runRight_start();
		void runLeft_start();

		void runRight();
		void runLeft();

		void jumpRight();
		void jumpLeft();

		void crouchRight();
		void crouchLeft();

		void attack();
		void attackL();

		void jumpAttack();

		void death();

		void idleCompleteEvent();

	private:
		ePenitentState mState;
		animator* mAnimator;
		static image* mImage;
		rigidBody* mRigidBody;
		float mInactiveTime;
		float mAnimTime;
	};
}
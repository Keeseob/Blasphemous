#include "rigidBody.h"
#include "time.h"
#include "transformation.h"
#include "gameObject.h"

namespace BP
{
	rigidBody::rigidBody() : component(eComponentType::rigidBody)
		, mMass(0.0f)
		, mForce(vector2::zero)
		, mAcceleration(vector2::zero)
		, mVelocity(vector2::zero)
	{
		mVelocityLimt.x = 100.0f;
		mVelocityLimt.y = 100.0f;
		mbGround = true;
		mGravity = vector2(0.0f, 800.0f);
		mFriction = 100.0f;
	}
	rigidBody::~rigidBody()
	{
	}

	void rigidBody::initialize()
	{
	}

	void rigidBody::update()
	{
		mAcceleration = mForce / mMass;

		mVelocity += mAcceleration * time::deltaTime();

		//땅 위에 있을 때
		if (mbGround)
		{
			vector2 gravity = mGravity;
			gravity.normalize();

			float dot = math::dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			mVelocity += mGravity * time::deltaTime();
		}

		//중력가속도 최대 속도
		vector2 gravity = mGravity;
		gravity.normalize();
		float dot = math::dot(mVelocity, gravity);
		gravity = gravity * dot;

		vector2 sideVelocity = mVelocity - gravity;
		if (mVelocityLimt.y < gravity.length())
		{
			gravity.normalize();
			gravity *= mVelocityLimt.y;
		}

		if (mVelocityLimt.x < sideVelocity.length())
		{
			sideVelocity.normalize();
			sideVelocity *= mVelocityLimt.x;
		}

		//마찰력
		if (!(mVelocity == vector2::zero))
		{
			//속도 반대방향으로 마찰력 적용
			vector2 friction = -mVelocity;
			friction = friction.normalize() * mFriction * mMass * time::deltaTime();

			//마찰력으로 인한 속도 감소가 현재 속도보다 큰 경우
			if (mVelocity.length() < friction.length())
			{
				mVelocity = vector2::zero;
			}
			else
			{
				mVelocity += friction;
			}
		}

		//속도에 맞춰서 이동
		transformation* trns = getOwner()->getComponent<transformation>();
		vector2 pos = trns->getPosition();
		pos = pos + mVelocity * time::deltaTime();
		
		//if (pos.y > 670.0f)
		//{
		//	mbGround = true;
		//}

		trns->setPosition(pos);
		mForce.clear();
	}
	void rigidBody::render(HDC hdc)
	{
	}
	void rigidBody::release()
	{
	}
	void rigidBody::addForce(vector2 force)
	{
		mForce += force;
	}
}
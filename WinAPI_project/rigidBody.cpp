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

		//�� ���� ���� ��
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

		//�߷°��ӵ� �ִ� �ӵ�
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

		//������
		if (!(mVelocity == vector2::zero))
		{
			//�ӵ� �ݴ�������� ������ ����
			vector2 friction = -mVelocity;
			friction = friction.normalize() * mFriction * mMass * time::deltaTime();

			//���������� ���� �ӵ� ���Ұ� ���� �ӵ����� ū ���
			if (mVelocity.length() < friction.length())
			{
				mVelocity = vector2::zero;
			}
			else
			{
				mVelocity += friction;
			}
		}

		//�ӵ��� ���缭 �̵�
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
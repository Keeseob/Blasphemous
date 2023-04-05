#include "ground.h"
#include "collider.h"
#include "penitentOne.h"
#include "rigidBody.h"
#include "transformation.h"

namespace BP
{
	ground::ground()
	{
	}
	ground::~ground()
	{
	}

	void ground::initialize()
	{
		mCollider = addComponent<collider>();
		mCollider->setSize(vector2(1600.0f, 50.0f));
		gameObject::initialize();
	}

	void ground::update()
	{
		gameObject::update();
	}

	void ground::render(HDC hdc)
	{
		gameObject::render(hdc);
	}

	void ground::release()
	{
	}

	void ground::onCollisionEnter(collider* other)
	{
		penitentOne* penitent = dynamic_cast<penitentOne*>(other->getOwner());
		if (penitent == nullptr)
		{
			return;
		}

		rigidBody* rgBody = penitent->getComponent<rigidBody>();
		rgBody->setGround(true);

		collider* penitentColl = penitent->getComponent<collider>();
		vector2 penitentPos = penitentColl->getPosition();

		collider* groundColl = this->getComponent<collider>();
		vector2 groundPos = groundColl->getPosition();

		float fLen = fabs(penitentPos.y - groundPos.y);
		float fSize = (penitentColl->getSize().y / 2.0f) + (groundColl->getSize().y / 2.0f);

		if (fLen < fSize)
		{
			transformation* penitentTrns = penitent->getComponent<transformation>();
			transformation* grTrns = this->getComponent<transformation>();

			vector2 penitentPos = penitentTrns->getPosition();
			vector2 grPos = grTrns->getPosition();

			penitentPos -= (fSize - fLen) -	1.0f;
			penitentTrns->setPosition(penitentPos);
		}
	}
	void ground::onCollisionStay(collider* other)
	{
	}
	void ground::onCollisionExit(collider* other)
	{
	}
}
#include "collider.h"
#include "transformation.h"
#include "gameObject.h"
#include "camera.h"

namespace BP
{
	UINT collider::colliderNumber = 0;
	collider::collider()
		: component(eComponentType::collider)
		, mCenter(vector2::zero)
		//, mScale(vector2::one)
		, mPosition(vector2::zero)
		, mSize(70.0f, 100.0f)
		, mID(colliderNumber++)
		, mCollisionCount(0)
	{
	}
	collider::~collider()
	{
	}	

	void collider::initialize()
	{
		transformation* trns = getOwner()->getComponent<transformation>();
		mPosition = trns->getPosition() + mCenter;
	}
	void collider::update()
	{
		transformation* trns = getOwner()->getComponent<transformation>();
		mPosition = trns->getPosition() + mCenter;
	}
	void collider::render(HDC hdc)
	{
		HPEN pen = NULL;
		if (mCollisionCount <= 0)
		{
			pen = CreatePen(BS_SOLID, 2, RGB(0, 255, 0));
		}
		else
		{
			pen = CreatePen(BS_SOLID, 2, RGB(255, 0, 0));
		}

		HPEN oldPen = (HPEN)SelectObject(hdc, pen);
		HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

		vector2 pos = camera::calculatePosition(mPosition);
		Rectangle(hdc, mPosition.x, mPosition.y, (mPosition.x + mSize.x), (mPosition.y + mSize.y));
		
		(HPEN)SelectObject(hdc, oldPen);
		(HBRUSH)SelectObject(hdc, oldBrush);
		DeleteObject(pen);

		mCollisionCount = 0;
	}
	void collider::release()
	{
	}
	void collider::onCollisionEnter(collider* other)
	{
		mCollisionCount++;
		getOwner()->onCollisionEnter(other);
	}
	void collider::onCollisionStay(collider* other)
	{
		mCollisionCount = 1;
		getOwner()->onCollisionStay(other);
	}
	void collider::onCollisionExit(collider* other)
	{
		mCollisionCount--;
		getOwner()->onCollisionExit(other);
	}
}
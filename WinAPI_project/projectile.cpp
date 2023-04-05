#include "projectile.h"
#include "transformation.h"
#include "time.h"
#include "object.h"

namespace BP
{
	projectile::projectile()
		: mTime(0.0f)
	{
	}
	projectile::~projectile()
	{
	}
	void projectile::initialize()
	{
	}
	void projectile::update()
	{
		transformation* trns = getComponent<transformation>();
		vector2 dir = vector2(100.0f, 0.0f);
		dir.normalize();

		//float x = dir.x * cosf(-PI / 10.0f) - dir.y * sin(-PI / 2.0f);
		//float y = dir.x * sin(-PI / 10.0f) + dir.y * cosf(-PI / 2.0f);

		vector2 pos = trns->getPosition();
		pos.x += 400.0f * dir.x * time::deltaTime();
		pos.y += 400.0f * dir.y * time::deltaTime();
		trns->setPosition(pos);

		mTime += time::deltaTime();
		if (mTime > 0.15f)
		{
			obj::destroy(this);
		}
	}
	void projectile::render(HDC hdc)
	{
		transformation* trns = getComponent<transformation>();

		HPEN pen = CreatePen(BS_SOLID, 2, RGB(255, 0, 0));
		vector2 position = trns->getPosition();

		HPEN oldPen = (HPEN)SelectObject(hdc, pen);
		HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

		Rectangle(hdc, position.x, position.y, position.x + 90, position.y + 50);

		(HPEN)SelectObject(hdc, oldPen);
		(HBRUSH)SelectObject(hdc, oldBrush);
		DeleteObject(pen);
	}
	void projectile::release()
	{
	}
}
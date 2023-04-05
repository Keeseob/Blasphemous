#include "crisantaBackground.h"
#include "sceneManager.h"
#include "bpResources.h"
#include "transformation.h"

namespace BP
{
	crisantaBackground::crisantaBackground()
	{
	}

	crisantaBackground::~crisantaBackground()
	{
	}

	void crisantaBackground::initialize()
	{
		mImage = bpResources::load<image>(L"backgroundMenu", L"..\\Resource\\crisantaBackground\\crisanta-bg-main-menu-animation_0000_Capa-15_0000_crisanta-bg-main-menu-animation_0014_Capa-1.bmp");

		gameObject::initialize();
		//transformation* trns = getComponent<transformation>();
		//vector2 pos = trns->getPosition();

		//pos.x = 0;
		//pos.y = 0;

		//trns->setPosition(pos);
	}

	void crisantaBackground::update()
	{
		gameObject::update();
	}

	void crisantaBackground::render(HDC hdc)
	{
		gameObject::render(hdc);
	/*	transformation* trns = getComponent<transformation>();
		vector2 pos = trns->getPosition();

		TransparentBlt(hdc, pos.x, pos.y
			, mImage->getWidth() * 2.5f
			, mImage->getHeight() * 2.5f
			, mImage->getHdc(), 0, 0
			, mImage->getWidth()
			, mImage->getHeight()
			, RGB(255, 0, 255));*/
	}

	void crisantaBackground::release()
	{
		gameObject::release();
	}
}

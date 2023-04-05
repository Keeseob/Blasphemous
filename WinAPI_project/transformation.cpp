#include "transformation.h"

namespace BP
{
	transformation::transformation() 
		: component(eComponentType::transformation)
		, mPosition(vector2::zero)
		, mScale(vector2::two)
	{
	}
	transformation::~transformation()
	{
	}

	void transformation::initialize()
	{
	}
	void transformation::update()
	{
	}
	void transformation::render(HDC hdc)
	{
	}
	void transformation::release()
	{
	}
}
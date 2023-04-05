#include "component.h"

namespace BP
{
	component::component(eComponentType type) : mType(type)
	{
	}
	component::~component()
	{
	}

 	void component::initialize()
	{
	}
	void component::update()
	{
	}
	void component::render(HDC hdc)
	{
	}
	void component::release()
	{
	}
}
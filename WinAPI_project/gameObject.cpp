#include "gameObject.h"
#include "transformation.h"

namespace BP
{
	gameObject::gameObject() 
		: mState(eState::active)
	{
		mComponent.resize((UINT)eComponentType::end);
		addComponent<transformation>(); //gameObject 실행 시, transformation도 같이 작동
	}
	gameObject::~gameObject()
	{
		for (component* comp : mComponent)
		{
			delete comp;
			comp = nullptr;
		}
	}

	void gameObject::initialize()	
	{
		for (component* comp : mComponent)
		{
			if (comp == nullptr)
			{
				continue;
			}
			comp->initialize();
		}
	}

	void gameObject::update()
	{
		for (component* comp : mComponent)
		{
			if (comp == nullptr)
			{
				continue;
			}
			comp->update();
		}
	}

	void gameObject::render(HDC hdc)
	{
		for (component* comp : mComponent)
		{
			if (comp == nullptr)
			{
				continue;
			}
			comp->render(hdc);
		}
	}

	void gameObject::release()
	{
	}

	void gameObject::onCollisionEnter(collider* other)
	{
	}
	void gameObject::onCollisionStay(collider* other)
	{
	}
	void gameObject::onCollisionExit(collider* other)
	{
	}
}
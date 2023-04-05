#pragma once
#include "gameObject.h"

namespace BP
{
	class projectile : public gameObject
	{
	public:
		projectile();
		~projectile();

		virtual void initialize() override;
		virtual void update() override;
		virtual void render(HDC hdc) override;
		virtual void release() override;

	private:
		float mTime;
	};
}

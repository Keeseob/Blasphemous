#pragma once
#include "component.h"

namespace BP
{
	class transformation : public component
	{
	public:
		transformation();
		~transformation();

		virtual void initialize() override;
		virtual void update() override;
		virtual void render(HDC hdc) override;
		virtual void release() override;

		void setPosition(vector2 pos) { mPosition = pos; }
		void setScale(vector2 scale) { mScale = scale; }
		vector2 getPosition() { return mPosition; }
		vector2 getScale() { return mScale; }

	private:
		vector2 mPosition;
		vector2 mScale;
	};
}
#pragma once
#include "component.h"
#include "animation.h"
#include "image.h"

namespace BP
{
	class animator : public component
	{
	public:
		struct event
		{
			void operator = (std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
				{
					mEvent();
				}
			}
			//함수포인터 형식: void(*name)(int, int)
			std::function<void()> mEvent;
		};
		//호출 한번에 event시작, 수행, 끝까지 모두 실행한다.
		struct events
		{
			event mStartEvent;
			event mCompleteEvent;
			event mEndEvent;
		};

		animator();
		~animator();

		virtual void initialize() override;
		virtual void update() override;
		virtual void render(HDC hdc) override;
		virtual void release() override;

		//모든 에니매이션이 힌 파일에 있는 경우
		void createAnimation(const std::wstring& name
			, image* sheet
			, vector2 leftTop
			, UINT coulmn
			, UINT row
			, UINT spriteLength
			, vector2 offset
			, float duration);

		//모든 에니매이션이 여러 파일에 나눠져 있는 경우
		void createAnimations(const std::wstring& path, vector2 offset, float duration);

		animation* findAnimation(const std::wstring& name);
		void play(const std::wstring& name, bool loop);

		events* findEvents(const std::wstring& name);
		std::function<void()>& getStartEvent(const std::wstring& name);
		std::function<void()>& getCompleteEvent(const std::wstring& name);
		std::function<void()>& getEndEvent(const std::wstring& name);
		bool isComplete() { return mActiveAnimation->isComplete(); }

	private:
		std::map<std::wstring, animation*> mAnimations;
		std::map<std::wstring, events*> mEvents;
		animation* mActiveAnimation;
		image* mSpriteSheet;
		bool mbLoop;
	};
}
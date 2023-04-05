
#include "animator.h"
#include "bpResources.h"

namespace BP
{
	animator::animator()
		: component(eComponentType::animator)
		, mActiveAnimation(nullptr)
		, mSpriteSheet(nullptr)
		, mbLoop(false)
	{
	}
	animator::~animator()
	{
		for (auto anim : mAnimations)
		{
			delete anim.second;
			anim.second = nullptr;
		}
		for (auto evns : mEvents)
		{
			delete evns.second;
			evns.second = nullptr;
		}
	}

	void animator::initialize()
	{
	}

	void animator::update()
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->update();
			if (mActiveAnimation->isComplete())
			{
				animator::events* evns = findEvents(mActiveAnimation->getName());
				if (evns != nullptr)
				{
					evns->mCompleteEvent();
				}
			}
			if (mbLoop && mActiveAnimation->isComplete())
			{
				mActiveAnimation->reset();
			}
		}
	}

	void animator::render(HDC hdc)
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->render(hdc);
		}
	}

	void animator::release()
	{
	}

	void animator::createAnimation(const std::wstring& name
		, image* sheet
		, vector2 leftTop
		, UINT coulmn
		, UINT row
		, UINT spriteLength
		, vector2 offset
		, float duration)
	{
		animation* animn = findAnimation(name);

		if (animn != nullptr)
		{
			return;
		}

		animn = new animation();
		animn->create(sheet, leftTop, coulmn, row, spriteLength, offset, duration);
		animn->setName(name);
		animn->setAnimator(this);

		mAnimations.insert(std::make_pair(name, animn));
		events* evns = new events();
		mEvents.insert(std::make_pair(name, evns));
	}

	void animator::createAnimations(const std::wstring& path, vector2 offset, float duration)
	{
		UINT width = 0;
		UINT height = 0;
		UINT fileCount = 0;

		std::filesystem::path fs(path);
		std::vector<image*> imgs = {};
		for (const auto& p : std::filesystem::recursive_directory_iterator(path))
		{
			std::wstring fileName = p.path().filename();
			std::wstring fullName = path + L"\\" + fileName;

			const std::wstring ext = p.path().extension();
			if (ext == L".png")
			{
				continue;
			}

			image* img = bpResources::load<image>(fileName, fullName);
			imgs.push_back(img);

			if (width < img->getWidth())
			{
				width = img->getWidth();
			}
			if (height < img->getHeight())
			{
				height = img->getHeight();
			}
			fileCount++;
		}

		std::wstring key = fs.parent_path().filename();
		key += fs.filename();
		mSpriteSheet = image::create(key, width * fileCount, height);

		int index = 0;
		for (image* img : imgs)
		{
			//폴더 내에 이미지 정렬
			int centerX = (width - img->getWidth()) / 2;
			int centerY = (height - img->getHeight());

			//이미지 위치 중앙으로 보정
			BitBlt(mSpriteSheet->getHdc()
				, width * index + centerX
				, 0 + centerY
				, img->getWidth(), img->getHeight()
				, img->getHdc(), 0, 0, SRCCOPY);

			index++;
		}
		createAnimation(key, mSpriteSheet, vector2::zero, index, 1, index, offset, duration);
	}

	animation* animator::findAnimation(const std::wstring& name)
	{
		std::map<std::wstring, animation*>::iterator iter = mAnimations.find(name);
		if (iter == mAnimations.end())
		{
			return nullptr;
		}
		return iter->second;
	}

	void animator::play(const std::wstring& name, bool loop)
	{
		if (mActiveAnimation != nullptr)
		{
			animator::events* prevEvents = findEvents(mActiveAnimation->getName());

			if (prevEvents != nullptr)
			{
				prevEvents->mEndEvent();
			}
		}
		mActiveAnimation = findAnimation(name);
		mActiveAnimation->reset();
		mbLoop = loop;

		animator::events* evns = findEvents(mActiveAnimation->getName());
		if (evns != nullptr)
		{
			evns->mStartEvent();
		}
	}

	animator::events* animator::findEvents(const std::wstring& name)
	{
		std::map<std::wstring, events*>::iterator iter = mEvents.find(name);
		if (iter == mEvents.end())
		{
			return nullptr;
		}

		return iter->second;
	}

	std::function<void()>& animator::getStartEvent(const std::wstring& name)
	{
		animation* anim = findAnimation(name);
		animator::events* evns = findEvents(anim->getName());

		return evns->mStartEvent.mEvent;
	}

	std::function<void()>& animator::getCompleteEvent(const std::wstring& name)
	{
		animation* anim = findAnimation(name);
		animator::events* evns = findEvents(anim->getName());

		return evns->mCompleteEvent.mEvent;
	}

	std::function<void()>& animator::getEndEvent(const std::wstring& name)
	{
		animation* anim = findAnimation(name);
		animator::events* evns = findEvents(anim->getName());

		return evns->mEndEvent.mEvent;
	}
}

#pragma once
#include "entity.h"

namespace BP
{
	class bpResource
	{
	public:
		bpResource();
		virtual ~bpResource();

		virtual HRESULT load(const std::wstring& path) = 0;

		const std::wstring& getKey()
		{
			return mKey;
		}
		const std::wstring& getPath()
		{
			return mPath;
		}
		void setKey(const std::wstring& key)
		{
			mKey = key;
		}
		void setPath(const std::wstring& path)
		{
			mPath = path;
		}

	private:
		std::wstring mKey;
		std::wstring mPath;
	};
}
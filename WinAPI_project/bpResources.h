#pragma once
#include "bpResource.h"

namespace BP
{
	class bpResources
	{
	public:
		template <typename T>
		static T* find(const std::wstring& key)
		{
			//리소스 맵에서 데이터 탐색. 데이터 발견 시, 데이터 반환, 없을 시에 end 반환
			std::map<std::wstring, bpResource*>::iterator iter = mBpResources.find(key);
			//데이터 발견시 형변환 후, 반환
			if (iter != mBpResources.end())
			{
				return dynamic_cast<T*>(iter->second);
			}
			return nullptr;
		}

		template <typename T>
		static T* load(const std::wstring& key, const std::wstring& path)
		{
			//key값으로 탐색
			T* resource = bpResources::find<T>(key);
			if (resource != nullptr)
			{
				return resource;
			}
			//리소스가 없으면 실행
			resource = new T();
			if (FAILED(resource->load(path)))
			{
				assert(false);
				return nullptr;
			}

			resource->setKey(key);
			resource->setPath(path);
			mBpResources.insert(std::make_pair(key, resource));

			return dynamic_cast<T*>(resource);
		}

		template <typename T>
		static void insert(const std::wstring& key, T* resource)
		{
			mBpResources.insert(std::make_pair(key, resource));
		}

		static void release()
		{
			for (auto pair: mBpResources)
			{
				delete pair.second;
				pair.second = nullptr;
			}
		}

	private:
		static std::map<std::wstring, bpResource*> mBpResources;
	};
}

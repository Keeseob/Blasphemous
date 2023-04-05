#pragma once
#include "engine.h"

namespace BP
{
	class entity
	{
	public:
		entity();
		virtual ~entity();

		void setName(const std::wstring& name) { mName = name; }
		std::wstring& getName() { return mName; }
		void setID(UINT64 id) { mID = id; }
		UINT64 getID() { return mID; }

	private:
		std::wstring mName;
		UINT64 mID;
	};
}
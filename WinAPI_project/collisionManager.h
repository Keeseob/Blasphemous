#pragma once
#include "includePack.h"
#include "enumPack.h"
#include "collider.h"

namespace BP
{
	union colliderID
	{
		struct
		{
			UINT32 left;
			UINT32 right;
		};
		UINT64 id;
	};

	class scene;
	class collisionManager
	{
	public:
		static void update();
		static void layerCollision(scene* scn, eLayerType left, eLayerType right);
		static void colliderCollision(collider* leftColl, collider* rightColl, eLayerType left, eLayerType right);
		static bool intersect(collider* left, collider* right);
		
		static void setLayer(eLayerType left, eLayerType right, bool value);
		static void clear();

	private:
		static WORD mMatrix[(UINT)eLayerType::end];
		static std::map<UINT64, bool> mCollisionMap;
	};
}
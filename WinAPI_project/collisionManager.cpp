#include "collisionManager.h"
#include "scene.h"
#include "sceneManager.h"

namespace BP
{
	WORD collisionManager::mMatrix[(UINT)eLayerType::end] = {};
	std::map<UINT64, bool> collisionManager::mCollisionMap;
	void collisionManager::update()
	{
		scene* scn = sceneManager::getActiveScene();
		for (UINT row = 0; row < (UINT)eLayerType::end; row++)
		{
			for (UINT coll = 0; coll < (UINT)eLayerType::end; coll++)
			{
				if (mMatrix[row] & (1 << coll))
				{
					layerCollision(scn, (eLayerType)row, (eLayerType)coll);
				}
			}
		}
	}

	void collisionManager::layerCollision(scene* scn, eLayerType left, eLayerType right)
	{
		std::vector<gameObject*>& lefts = scn->getGameObject(left);
		std::vector<gameObject*>& rights = scn->getGameObject(right);

		for (auto leftObject : lefts)
		{
			collider* leftCollider = leftObject->getComponent<collider>();
			if (leftCollider == nullptr)
			{
				continue;
			}

			for (auto rightObject : rights)
			{
				collider* rightCollider = rightObject->getComponent<collider>();
				if (rightObject == nullptr)
				{
					continue;
				}
				if (leftObject == rightObject)
				{
					continue;
				}

				colliderCollision(leftCollider, rightCollider, left, right);
			}
		}
	}

	void collisionManager::colliderCollision(collider* leftColl, collider* rightColl, eLayerType left, eLayerType right)
	{
		colliderID collID = {};
		collID.left = (UINT)leftColl->getID();
		collID.right = (UINT)rightColl->getID();

		std::map<UINT64, bool >::iterator iter = mCollisionMap.find(collID.id);

		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(collID.id, false));
			iter = mCollisionMap.find(collID.id);
		}

		if (intersect(leftColl, rightColl))
		{
			//최초 충돌시, onCollisionEnter
			if (iter->second == false)
			{
				leftColl->onCollisionEnter(rightColl);
				rightColl->onCollisionEnter(leftColl);
				iter->second = true;
			}
			else
			{
				leftColl->onCollisionStay(rightColl);
				rightColl->onCollisionStay(leftColl);
			}
		}
		else
		{
			//onCollisionExit
			//이전 프레임은 충돌 했으나, 현재 프레임은 충돌하지 않음.
			if (iter->second == true)
			{
				leftColl->onCollisionExit(rightColl);
				rightColl->onCollisionExit(leftColl);
				iter->second = false;
			}
		}
	}

	bool collisionManager::intersect(collider* left, collider* right)
	{
		vector2 leftPos = left->getPosition();
		vector2 rightPos = right->getPosition();

		// 두 충돌체 간의 거리와, 각 면적의 절반끼리의 합을 비교해서
		// 거리가 더 길다면 충돌 X, 거리가 더 짧다면 충돌 O
		vector2 leftSize = left->getSize();
		vector2 rightSize = right->getSize();

		leftPos.x = leftPos.x + leftSize.x / 2.0f;
		leftPos.y = leftPos.y + leftSize.y / 2.0f;

		rightPos.x = rightPos.x + rightSize.x / 2.0f;
		rightPos.y = rightPos.y + rightSize.y / 2.0f;

		if (fabs(leftPos.x - rightPos.x) < (leftSize.x / 2.0f) + (rightSize.x / 2.0f)
			&& fabs(leftPos.y - rightPos.y) < (leftSize.y / 2.0f) + rightSize.y / 2.0f)
		{
			return true;
		}
		return false;
	}

	void collisionManager::setLayer(eLayerType left, eLayerType right, bool value)
	{
		UINT row = 0;
		UINT coll = 0;

		UINT ileft = (UINT)left;
		UINT iright = (UINT)right;

		if (left <= right)
		{
			row = ileft;
			coll = iright;
		}
		else
		{
			row = iright;
			coll = ileft;
		}

		if (value == true)
		{
			//|= OR 비트 연산자, 비교 대상이 하나라도 1이면 반환 및 left에 대입
			mMatrix[row] |= (1 << coll);
		}
		else
		{
			//&= AND 비트 연산자, 비교 대상이 모두 같으면 1을 반환 및 left에 대입
			//~ NOT 비트 연산자, 비트 전부 반전
			mMatrix[row] &= ~(1 << coll);
		}
	}

	void collisionManager::clear()
	{
		memset(mMatrix, 0, sizeof(WORD) * (UINT)eLayerType::end);
		mCollisionMap.clear();
	}
}
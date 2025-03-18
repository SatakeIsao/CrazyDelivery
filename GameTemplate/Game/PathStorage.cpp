#include "stdafx.h"
#include "PathStorage.h"
#include "Path.h"
namespace
{
	//const float MIN_DISTANCE = 10000.0f; //
}

PathStorage* PathStorage::m_pathStorage = nullptr;

PathStorage::PathStorage()
{
	//本人の制御
	//インスタンスを一つだけにする
	if (m_pathStorage == nullptr)
	{
		//インスタンスの登録
		m_pathStorage = this;
	}
}

PathStorage::~PathStorage()
{
	m_pathStorage = nullptr;
}

void PathStorage::AddPath(int number, Path& path)
{
	auto it = m_paths.find(number);

	//すでに同じ番号のパスが存在していない場合
	if (it == m_paths.end())
	{
		//新しいパスを追加
		m_paths.emplace(number, &path);
	}
	/*if (number >= m_paths.size())
	{
		m_paths.emplace(number + 1);
	}*/

	//新しいパスを追加
	//m_paths[number] = new Path(path);
}


bool PathStorage::Exist(int number)
{
	auto it = m_paths.find(number);
	
	//すでに同じ番号のパスが存在していた場合
	if (it != m_paths.end())
	{
		return true;
	}
	//存在していない場合
	else
	{
		return false;
	}
}

PathStorage* PathStorage::CreateInstance()
{
	if (m_pathStorage != nullptr)
	{
		return m_pathStorage;
	}
	//メモリを確保
	m_pathStorage = new PathStorage;

	return m_pathStorage;
}

void PathStorage::DeleteInstance()
{
	//メモリを解放
	delete m_pathStorage;
}

Path* PathStorage::GetFirstPath()
{
	if (m_paths.empty())
	{
		return nullptr;
	}
	//先頭のパスを取得
	return m_paths.begin()->second;
}

Path* PathStorage::GetFirstPath2()
{
	int pathCount = GetPathCount();
	if (pathCount < 2) // 5つ未満なら2セット目は存在しない
	{
		return nullptr;
	}

	// 2セット目の最初のPathを探す
	Path* firstPath2 = nullptr;
	float minDistance = 10000;
	Vector3 referencePoint = GetFirstPath()->GetFirstPoint().position; // 1セット目の開始位置を基準

	for (int i = 0; i < pathCount; i++)
	{
		Path* path = GetPath(i);
		if (!path) continue;

		const Vector3& pathStart = path->GetFirstPoint().position;
		float distance = (pathStart - referencePoint).Length();

		// 1セット目のPathより遠く、最も近いPathを探す
		if (distance > 500.0f && distance < minDistance)  // 500.0f は適当なしきい値
		{
			minDistance = distance;
			firstPath2 = path;
		}
	}

	if (firstPath2)
	{
		return firstPath2;
	}
	else
	{
		return nullptr;
	}
}

Path* PathStorage::GetFirstPath3()
{
	int pathCount = GetPathCount();
	if (pathCount < 3) // 5つ未満なら2セット目は存在しない
	{
		return nullptr;
	}

	Path* firstPath1 = GetFirstPath();
	Path* firstPath2 = GetFirstPath2();

	if (!firstPath1 || !firstPath2)
	{
		return nullptr;
	}

	// 2セット目の最初のPathを探す
	Path* firstPath3 = nullptr;
	float minDistance = 10000;
	Vector3 referencePoint1 = firstPath1->GetFirstPoint().position; // 1セット目の開始位置を基準にする
	Vector3 referencePoint2 = firstPath2->GetFirstPoint().position;

	for (int i = 0; i < pathCount; i++)
	{
		Path* path = GetPath(i);
		if (!path) continue;

		const Vector3& pathStart = path->GetFirstPoint().position;
		float distance1 = (pathStart - referencePoint1).Length();
		float distance2 = (pathStart - referencePoint2).Length();

		// 1セット目のPathより遠く、最も近いPathを探す
		if (distance1 > 500.0f
			&& distance2 > 500.0f)
		{
			//距離が小さい方を選ぶ
			float closerDistance;
			if (distance1 < distance2)
			{
				closerDistance = distance1;
			}
			else
			{
				closerDistance = distance2;
			}

			if (closerDistance < minDistance)
			{
				minDistance = closerDistance;
				firstPath3 = path;
			}
		}
	}

	return firstPath3;
}

Path* PathStorage::GetFirstPath4()
{
	int pathCount = GetPathCount();
	//４つ未満なら４セット目は存在しない
	if (pathCount < 4)
	{
		return nullptr;
	}
	
	//1,2,3セット目のパスを取得
	Path* firstPath1 = GetFirstPath();
	Path* firstPath2 = GetFirstPath2();
	Path* firstPath3 = GetFirstPath3();

	//いずれかが存在しなければ4セット目は探せない
	if (!firstPath1
		|| !firstPath2
		|| !firstPath3)
	{
		return nullptr;
	}
	
	//1,2,3セット目の開始位置を基準点とする
	Vector3 referencePoint1 = firstPath1->GetFirstPoint().position;
	Vector3 referencePoint2 = firstPath2->GetFirstPoint().position;
	Vector3 referencePoint3 = firstPath3->GetFirstPoint().position;

	Path* firstPath4 = nullptr;
	float minDistance = 10000.0f;

	for (int i = 0; i < pathCount; i++)
	{
		Path* path = GetPath(i);
		if (!path) continue;

		const Vector3& pathStart = path->GetFirstPoint().position;
		//各規準点からの距離を計算
		float distance1 = (pathStart - referencePoint1).Length();
		float distance2 = (pathStart - referencePoint2).Length();
		float distance3 = (pathStart - referencePoint3).Length();

		//すべての基準値から500.0f以上離れているかチェック
		if (distance1 > 500.0f
			&& distance2 > 500.0f
			&& distance3 > 500.0f)
		{
			//3つの距離の中から最も近い距離を計算
			float closerDistance = distance1;

			if (distance2 < closerDistance)
			{
				closerDistance = distance2;
			}
			if (distance3 < closerDistance)
			{
				closerDistance = distance3;
			}
			//最も近いパスを更新
			if (closerDistance < minDistance)
			{
				minDistance = closerDistance;
				firstPath4 = path;
			}
		}
	}
	return firstPath4;
}

Path* PathStorage::GetLastPath()
{
	//コンテナ内が空っぽだったら
	if (m_paths.empty())
	{
		return nullptr;
	}
	//末尾のパスを取得
	return m_paths.rbegin()->second;
	
}

Path* PathStorage::GetLastPath2()
{
	Path* firstPath2 = GetFirstPath2();
	if (!firstPath2)
	{
		return nullptr;
	}

	int pathCount = GetPathCount();
	Path* lastPath2 = nullptr;
	float maxDistance = -1.0f;
	Vector3 referencePoint = firstPath2->GetFirstPoint().position;

	for (int i = 0; i < pathCount; i++)
	{
		Path* path = GetPath(i);
		if (!path) continue;

		const Vector3& pathStart = path->GetFirstPoint().position;
		float distance = (pathStart - referencePoint).Length();

		//１セット目から十分に離れており、最も早いパスを探す
		if (distance > 500.0f && distance > maxDistance)
		{
			maxDistance = distance;
			lastPath2 = path;
		}
	}
	return lastPath2;
}



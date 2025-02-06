#pragma once
#include <iostream>
#include "Path.h"
class Path;
/// <summary>
/// パスを保持するストーレジ
/// </summary>
/// <remark>
///		このクラスはシングルトンパターンで設計されている
///		このクラスはゲーム中のパスを保持するストレージです。
///		パスを番号とセットで記憶している
/// </remark>
class PathStorage
{
private:
	//本人以外の制御
	PathStorage();
	~PathStorage();

public:
	//シングルトン
	static PathStorage* GetPathStorage() {
		return m_pathStorage;
	}
	
	/// <summary>
	/// ストレージに追加するための関数
	/// </summary>
	/// <param name="number">検索可能なキー</param>
	/// <param name="path">キーに対応する値</param>
	void AddPath(int number, Path& path);
	
	/// <summary>
	/// PathStorageにpathNoの＊パスが保存されているか調べるための関数
	/// </summary>
	/// <param name="number"></param>
	/// <param name="path"></param>
	bool Exist(int number);

	/// <summary>
	/// インスタンスを作成する関数
	/// </summary>
	/// <returns></returns>
	static PathStorage* CreateInstance();

	/// <summary>
	/// インスタンスを削除する関数
	/// </summary>
	/// <returns></returns>
	static void DeleteInstance();

	/// <summary>
	/// パスを取得
	/// </summary>
	/// <param name="number">検索可能なキー</param>
	/// <returns></returns>
	Path* GetPath(int number)
	{
		auto it = m_paths.find(number);
		//すでに同じ番号のパスが存在していない場合
		if (it == m_paths.end()) 
		{
			//指定された番後のパスがない
			return nullptr;
		}
		//キーに対応する値を返す
		return it->second;
	}
	/// <summary>
	/// パスの数を取得
	/// </summary>
	/// <returns></returns>
	int GetPathCount() const
	{
		return m_paths.size();
	}

	Path* GetFirstPath()
	{
		if (m_paths.empty())
		{
			return nullptr;
		}
		//先頭のパスを取得
		return m_paths.begin()->second;
	}

	Path* GetFirstPath2()
	{
		int pathCount = GetPathCount();
		if (pathCount < 2) // 5つ未満なら2セット目は存在しない
		{
			std::cout << "Error: Not enough paths for second set. Path count = " << pathCount << std::endl;
			return nullptr;
		}

		// **2セット目の最初のPathを探す**
		Path* firstPath2 = nullptr;
		float minDistance = FLT_MAX;
		Vector3 referencePoint = GetFirstPath()->GetFirstPoint().position; // 1セット目の開始位置を基準にする

		for (int i = 0; i < pathCount; i++)
		{
			Path* path = GetPath(i);
			if (!path) continue;

			const Vector3& pathStart = path->GetFirstPoint().position;
			float distance = (pathStart - referencePoint).Length();

			// **1セット目のPathより遠く、最も近いPathを探す**
			if (distance > 500.0f && distance < minDistance)  // 500.0f は適当な閾値
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
private:
	static PathStorage* m_pathStorage;	//PathStorageクラスのインスタンス
	std::map<int, Path*>	m_paths;	//番号とパス
};


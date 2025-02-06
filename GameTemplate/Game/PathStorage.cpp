#include "stdafx.h"
#include "PathStorage.h"
#include "Path.h"
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



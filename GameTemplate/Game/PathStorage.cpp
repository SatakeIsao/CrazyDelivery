#include "stdafx.h"
#include "PathStorage.h"
#include "Path.h"
PathStorage* PathStorage::m_pathStorage = nullptr;

PathStorage::PathStorage()
{
	//�{�l�̐���
	//�C���X�^���X��������ɂ���
	if (m_pathStorage == nullptr)
	{
		//�C���X�^���X�̓o�^
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

	//���łɓ����ԍ��̃p�X�����݂��Ă��Ȃ��ꍇ
	if (it == m_paths.end())
	{
		//�V�����p�X��ǉ�
		m_paths.emplace(number, &path);
	}
	/*if (number >= m_paths.size())
	{
		m_paths.emplace(number + 1);
	}*/

	//�V�����p�X��ǉ�
	//m_paths[number] = new Path(path);
}


bool PathStorage::Exist(int number)
{
	auto it = m_paths.find(number);
	
	//���łɓ����ԍ��̃p�X�����݂��Ă����ꍇ
	if (it != m_paths.end())
	{
		return true;
	}
	//���݂��Ă��Ȃ��ꍇ
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
	//���������m��
	m_pathStorage = new PathStorage;

	return m_pathStorage;
}

void PathStorage::DeleteInstance()
{
	//�����������
	delete m_pathStorage;
}

Path* PathStorage::GetFirstPath()
{
	if (m_paths.empty())
	{
		return nullptr;
	}
	//�擪�̃p�X���擾
	return m_paths.begin()->second;
}

Path* PathStorage::GetFirstPath2()
{
	int pathCount = GetPathCount();
	if (pathCount < 2) // 5�����Ȃ�2�Z�b�g�ڂ͑��݂��Ȃ�
	{
		return nullptr;
	}

	// **2�Z�b�g�ڂ̍ŏ���Path��T��**
	Path* firstPath2 = nullptr;
	float minDistance = 10000;
	Vector3 referencePoint = GetFirstPath()->GetFirstPoint().position; // 1�Z�b�g�ڂ̊J�n�ʒu����ɂ���

	for (int i = 0; i < pathCount; i++)
	{
		Path* path = GetPath(i);
		if (!path) continue;

		const Vector3& pathStart = path->GetFirstPoint().position;
		float distance = (pathStart - referencePoint).Length();

		// **1�Z�b�g�ڂ�Path��艓���A�ł��߂�Path��T��**
		if (distance > 500.0f && distance < minDistance)  // 500.0f �͓K����臒l
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

Path* PathStorage::GetLastPath()
{
	//�R���e�i��������ۂ�������
	if (m_paths.empty())
	{
		return nullptr;
	}
	//�����̃p�X���擾
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

		//�P�Z�b�g�ڂ���\���ɗ���Ă���A�ł������p�X��T��
		if (distance > 500.0f && distance > maxDistance)
		{
			maxDistance = distance;
			lastPath2 = path;
		}
	}
	return lastPath2;
}



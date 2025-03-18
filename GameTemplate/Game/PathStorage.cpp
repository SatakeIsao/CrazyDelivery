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

	// 2�Z�b�g�ڂ̍ŏ���Path��T��
	Path* firstPath2 = nullptr;
	float minDistance = 10000;
	Vector3 referencePoint = GetFirstPath()->GetFirstPoint().position; // 1�Z�b�g�ڂ̊J�n�ʒu���

	for (int i = 0; i < pathCount; i++)
	{
		Path* path = GetPath(i);
		if (!path) continue;

		const Vector3& pathStart = path->GetFirstPoint().position;
		float distance = (pathStart - referencePoint).Length();

		// 1�Z�b�g�ڂ�Path��艓���A�ł��߂�Path��T��
		if (distance > 500.0f && distance < minDistance)  // 500.0f �͓K���Ȃ������l
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
	if (pathCount < 3) // 5�����Ȃ�2�Z�b�g�ڂ͑��݂��Ȃ�
	{
		return nullptr;
	}

	Path* firstPath1 = GetFirstPath();
	Path* firstPath2 = GetFirstPath2();

	if (!firstPath1 || !firstPath2)
	{
		return nullptr;
	}

	// 2�Z�b�g�ڂ̍ŏ���Path��T��
	Path* firstPath3 = nullptr;
	float minDistance = 10000;
	Vector3 referencePoint1 = firstPath1->GetFirstPoint().position; // 1�Z�b�g�ڂ̊J�n�ʒu����ɂ���
	Vector3 referencePoint2 = firstPath2->GetFirstPoint().position;

	for (int i = 0; i < pathCount; i++)
	{
		Path* path = GetPath(i);
		if (!path) continue;

		const Vector3& pathStart = path->GetFirstPoint().position;
		float distance1 = (pathStart - referencePoint1).Length();
		float distance2 = (pathStart - referencePoint2).Length();

		// 1�Z�b�g�ڂ�Path��艓���A�ł��߂�Path��T��
		if (distance1 > 500.0f
			&& distance2 > 500.0f)
		{
			//����������������I��
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
	//�S�����Ȃ�S�Z�b�g�ڂ͑��݂��Ȃ�
	if (pathCount < 4)
	{
		return nullptr;
	}
	
	//1,2,3�Z�b�g�ڂ̃p�X���擾
	Path* firstPath1 = GetFirstPath();
	Path* firstPath2 = GetFirstPath2();
	Path* firstPath3 = GetFirstPath3();

	//�����ꂩ�����݂��Ȃ����4�Z�b�g�ڂ͒T���Ȃ�
	if (!firstPath1
		|| !firstPath2
		|| !firstPath3)
	{
		return nullptr;
	}
	
	//1,2,3�Z�b�g�ڂ̊J�n�ʒu����_�Ƃ���
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
		//�e�K���_����̋������v�Z
		float distance1 = (pathStart - referencePoint1).Length();
		float distance2 = (pathStart - referencePoint2).Length();
		float distance3 = (pathStart - referencePoint3).Length();

		//���ׂĂ̊�l����500.0f�ȏ㗣��Ă��邩�`�F�b�N
		if (distance1 > 500.0f
			&& distance2 > 500.0f
			&& distance3 > 500.0f)
		{
			//3�̋����̒�����ł��߂��������v�Z
			float closerDistance = distance1;

			if (distance2 < closerDistance)
			{
				closerDistance = distance2;
			}
			if (distance3 < closerDistance)
			{
				closerDistance = distance3;
			}
			//�ł��߂��p�X���X�V
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



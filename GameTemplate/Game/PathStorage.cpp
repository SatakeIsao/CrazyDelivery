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



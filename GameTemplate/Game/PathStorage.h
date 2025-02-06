#pragma once
#include <iostream>
#include "Path.h"
class Path;
/// <summary>
/// �p�X��ێ�����X�g�[���W
/// </summary>
/// <remark>
///		���̃N���X�̓V���O���g���p�^�[���Ő݌v����Ă���
///		���̃N���X�̓Q�[�����̃p�X��ێ�����X�g���[�W�ł��B
///		�p�X��ԍ��ƃZ�b�g�ŋL�����Ă���
/// </remark>
class PathStorage
{
private:
	//�{�l�ȊO�̐���
	PathStorage();
	~PathStorage();

public:
	//�V���O���g��
	static PathStorage* GetPathStorage() {
		return m_pathStorage;
	}
	
	/// <summary>
	/// �X�g���[�W�ɒǉ����邽�߂̊֐�
	/// </summary>
	/// <param name="number">�����\�ȃL�[</param>
	/// <param name="path">�L�[�ɑΉ�����l</param>
	void AddPath(int number, Path& path);
	
	/// <summary>
	/// PathStorage��pathNo�́��p�X���ۑ�����Ă��邩���ׂ邽�߂̊֐�
	/// </summary>
	/// <param name="number"></param>
	/// <param name="path"></param>
	bool Exist(int number);

	/// <summary>
	/// �C���X�^���X���쐬����֐�
	/// </summary>
	/// <returns></returns>
	static PathStorage* CreateInstance();

	/// <summary>
	/// �C���X�^���X���폜����֐�
	/// </summary>
	/// <returns></returns>
	static void DeleteInstance();

	/// <summary>
	/// �p�X���擾
	/// </summary>
	/// <param name="number">�����\�ȃL�[</param>
	/// <returns></returns>
	Path* GetPath(int number)
	{
		auto it = m_paths.find(number);
		//���łɓ����ԍ��̃p�X�����݂��Ă��Ȃ��ꍇ
		if (it == m_paths.end()) 
		{
			//�w�肳�ꂽ�Ԍ�̃p�X���Ȃ�
			return nullptr;
		}
		//�L�[�ɑΉ�����l��Ԃ�
		return it->second;
	}
	/// <summary>
	/// �p�X�̐����擾
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
		//�擪�̃p�X���擾
		return m_paths.begin()->second;
	}

	Path* GetFirstPath2()
	{
		int pathCount = GetPathCount();
		if (pathCount < 2) // 5�����Ȃ�2�Z�b�g�ڂ͑��݂��Ȃ�
		{
			std::cout << "Error: Not enough paths for second set. Path count = " << pathCount << std::endl;
			return nullptr;
		}

		// **2�Z�b�g�ڂ̍ŏ���Path��T��**
		Path* firstPath2 = nullptr;
		float minDistance = FLT_MAX;
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
private:
	static PathStorage* m_pathStorage;	//PathStorage�N���X�̃C���X�^���X
	std::map<int, Path*>	m_paths;	//�ԍ��ƃp�X
};


#pragma once
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
	/// �P�Z�b�g�ڂ̃p�X�擪�擾
	/// </summary>
	/// <returns></returns>
	Path* GetFirstPath();
	Path* GetFirstPath2();
	Path* GetFirstPath3();
	Path* GetFirstPath4();
	Path* GetLastPath();
	Path* GetLastPath2();

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

	
	
private:
	static PathStorage* m_pathStorage;	//PathStorage�N���X�̃C���X�^���X
	std::map<int, Path*>	m_paths;	//�ԍ��ƃp�X
};


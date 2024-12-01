#pragma once
#include "IPlayerState.h"

namespace nsPlayer
{
	//�O���錾
	class Player;
	/// <summary>
	/// �v���C���[�̃X�^�[�g����:�X�e�[�g�N���X
	/// </summary>
	class PlayerStartState : public IPlayerState
	{
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="player">�v���C���[�̃C���X�^���X</param>
		PlayerStartState(Player* player) :IPlayerState(player){};

		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~PlayerStartState() override;

		/// <summary>
		/// �X�e�[�g�J�n���̏���
		/// </summary>
		void Enter() override;

		/// <summary>
		/// �X�e�[�g�̑J�ڏ���
		/// </summary>
		/// <returns>�J�ڂ���X�e�[�g</returns>
		IPlayerState* StateChange() override;

		/// <summary>
		/// �X�e�[�g�ɂ�����X�V����
		/// </summary>
		void Update() override;

	private:
		float acceleTime = 0.6f;
		//ModelRender			m_playerModel;								//�v���C���[���f��
		//ModelRender			m_boardModel;								//�{�[�h���f��
	};
}



#pragma once
#include "IPlayerState.h"

namespace nsPlayer
{
	//�O���錾
	class Player;
	/// <summary>
	/// �v���C���[�������Ă��鎞�̃X�e�[�g�N���X
	/// </summary>
	class PlayerRunState : public IPlayerState
	{
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="player">�v���C���[�̃C���X�^���X</param>
		PlayerRunState(Player* player) :IPlayerState(player) {};

		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~PlayerRunState() override;

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
		
		/*float GetAcceleTime()
		{
			return acceleTime;
		}*/
	private:
		float m_acceleTime = 0.6f;
		
	};
}




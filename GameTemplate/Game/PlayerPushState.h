#pragma once
#include "IPlayerState.h"

/// <summary>
/// �v���C���[�̖��O���
/// </summary>
namespace nsPlayer
{
	//�O���錾
	class Player;
	/// <summary>
	/// �v���C���[�̒n�ʏR��X�e�[�g�N���X
	/// </summary>
	class PlayerPushState : public IPlayerState
	{
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="player">�v���C���[�̃C���X�^���X</param>
		PlayerPushState(Player* player) :IPlayerState(player) {}

		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~PlayerPushState() override;

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
	};
}



#pragma once
#include "IPlayerState.h"

namespace nsPlayer
{
	class Player;
	/// <summary>
	/// �v���C���[���{���Ă��鎞�̃X�e�[�g�N���X
	/// </summary>
	class PlayerAngryState :public IPlayerState
	{
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="player"></param>
		PlayerAngryState(Player* player) :IPlayerState(player) {};
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~PlayerAngryState() override;
		/// <summary>
		/// �X�e�[�g�J�n���̏���
		/// </summary>
		void Enter() override;
		/// <summary>
		/// �X�e�[�g�̑J�ڏ���
		/// </summary>
		/// <returns></returns>
		IPlayerState* StateChange() override;
		/// <summary>
		/// �X�e�[�g�ɂ�����X�V����
		/// </summary>
		void Update() override;

	private:
	};
}



#pragma once
#include "Player.h"
#include "GameCamera.h"
#include "Scene/Game.h"
#include "GameSound.h"
#include "UI/ResultUI.h"

/// <summary>
/// �v���C���[�̖��O���
/// </summary>
namespace nsPlayer
{
	//�O���錾
	class Player;

	/// <summary>
	/// �v���C���[�X�e�[�g���N���X
	/// </summary>
	class IPlayerState
	{
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="player">�v���C���[</param>
		IPlayerState(Player *player):m_player(player){}

		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		virtual ~IPlayerState(){}
		
		/// <summary>
		/// �X�e�[�g�̊J�n���̏���
		/// </summary>
		virtual void Enter() = 0;

		/// <summary>
		/// �X�e�[�g�̑J�ڏ���
		/// </summary>
		/// <returns>�J�ڂ���X�e�[�g</returns>
		virtual IPlayerState* StateChange() = 0;

		/// <summary>
		/// �e�X�e�[�g�ɂ�����X�V����
		/// </summary>
		virtual void Update() = 0;

	protected:
		Player*			m_player = nullptr; //�v���C���[
		GameCamera*		m_gameCamera = nullptr; //�Q�[���J����
		Game*			m_game = nullptr;		//�Q�[��
		SoundSource*	m_skaterJumpSE = nullptr;//���ʉ�
		ResultUI*		m_resultUI = nullptr;		//���U���gUI
		//SoundSource* m_skaterRunSE = nullptr;
		//SoundSource* m_skaterAcceleSE = nullptr;
	};


}



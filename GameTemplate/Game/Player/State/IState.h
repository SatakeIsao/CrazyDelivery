/**
 * �v���C���[���g�p����X�e�[�g�p�^�[���̊��N���X
 */
#pragma once
#include "GameSound.h"
#include "Util/CRC32.h"
/** �v���C���[�̊e�X�e�[�g�p�^�[�������ʂ��邽�߂�ID���`����define */
#define playerState(name)\
public:\
	static constexpr uint32_t ID() { return Hash32(#name); }

static constexpr uint32_t INVALID_PLAYER_STATE_ID = 0xffffffff;

namespace nsPlayer
{
	class Player;

	class IState
	{
	protected:
		/// <summary>
		/// �w�肳�ꂽ���ʉ����Đ����܂��B
		/// </summary>
		/// <param name="name">�Đ�������ʉ��̖��O</param>
		/// <param name="vol">���ʉ��̉��ʁi0.0�`1.0�͈̔́j</param>
		/// <param name="isPlay">���[�v�Đ����邩�ǂ����itrue�Ń��[�v�Đ��Afalse��1��̂݁j</param>
		void PlaySoundSE(const SoundName& name, const float vol, const bool isPlay);
	public:
		IState(Player* owner) : m_owner(owner) {}
		virtual ~IState() {}

		/// <summary>
		/// �X�e�[�g���؂�ւ�����Ƃ��ɌĂ΂��֐�
		/// NOTE: ��������̏�����������Ƃ��Ɏg�p���܂�
		/// </summary>
		virtual void Enter() = 0;
		/// <summary>
		/// ���t���[���Ă΂��X�V�֐�
		/// </summary>
		virtual void Update() = 0;
		/// <summary>
		/// ��Ԃ��؂�ւ��Ƃ��ɌĂ΂��֐�
		/// NOTE: ��������̔j���Ȃǂ���Ƃ��Ɏg�p���܂�
		/// </summary>
		virtual void Exit() = 0;
		/// <summary>
		/// ��Ԃ̐؂�ւ������N�G�X�g���܂�
		/// NOTE: �؂�ւ�肪���������Ƃ��͈�����ID������Ȓl�ŕԂ�܂�
		/// </summary>
		virtual bool RequestState(uint32_t& id) = 0;

	protected:
		friend class Player;
		Player* m_owner = nullptr;	// ���̃X�e�[�g�p�^�[�����g�p���鎝����
	};
}
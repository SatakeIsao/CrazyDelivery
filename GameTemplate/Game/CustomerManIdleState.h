#pragma once
#include "ICustomerManState.h"

/// <summary>
/// ���q����i�j���j�̖��O���
/// </summary>
namespace nsCustomerMan
{
	//�O���錾
	class CustomerMan;
	/// <summary>
	/// ���q����i�j���j�̑ҋ@�X�e�[�g�N���X
	/// </summary>
	class CustomerManIdleState : public ICustomerManState
	{
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="customerman"></param>
		CustomerManIdleState(CustomerMan* customerman):ICustomerManState(customerman){}

		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~CustomerManIdleState() override;

		/// <summary>
		/// �X�e�[�g�J�n���̏���
		/// </summary>
		void Enter() override;

		/// <summary>
		/// �X�e�[�g�̑J�ڏ���
		/// </summary>
		/// <returns>�J�ڂ���X�e�[�g</returns>
		ICustomerManState* StateChange() override;

		/// <summary>
		/// �X�e�[�g�ɂ�����X�V����
		/// </summary>
		void Update() override;
	};
}



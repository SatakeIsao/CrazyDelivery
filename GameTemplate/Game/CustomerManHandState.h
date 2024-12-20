#pragma once
#include "ICustomerManState.h"

namespace nsCustomerMan
{
	//�O���錾
	class CustomerMan;
	/// <summary>
	/// ���q����i�j���j�̎��������X�e�[�g�N���X
	/// </summary>
	class CustomerManHandState : public ICustomerManState
	{
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="customerman"></param>
		CustomerManHandState(CustomerMan* customerman):ICustomerManState(customerman){}

		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~CustomerManHandState() override;

		/// <summary>
		/// �X�e�[�g�J�n���̏���
		/// </summary>
		void Enter() override;

		/// <summary>
		/// �X�e�[�g�̑J�ڏ���
		/// </summary>
		/// <returns></returns>
		ICustomerManState* StateChange() override;

		/// <summary>
		/// �X�e�[�g�ɂ�����X�V����
		/// </summary>
		void Update() override;
	};
}



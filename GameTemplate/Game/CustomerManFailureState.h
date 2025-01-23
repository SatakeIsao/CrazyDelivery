#pragma once
#include "ICustomerManState.h"

//�O���錾
class CustomerMan;
	/// <summary>
	/// ���q����i�j���j�̎��s����X�e�[�g�N���X
	/// </summary>
class CustomerManFailureState : public ICustomerManState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="customerman"></param>
	CustomerManFailureState(CustomerMan* customerman):ICustomerManState(customerman){}

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CustomerManFailureState() override;

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

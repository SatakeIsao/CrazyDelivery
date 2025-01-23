#pragma once
#include "ICustomerManState.h"

//�O���錾
class CustomerMan;
/// <summary>
/// ���q����i�j���j�̊������Ƃ��̃X�e�[�g�N���X
/// </summary>
class CustomerManHappyState : public ICustomerManState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="customerman"></param>
	CustomerManHappyState(CustomerMan* customerman):ICustomerManState(customerman){}

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CustomerManHappyState() override;

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




#include "stdafx.h"
#include "ShopHamburger.h"
#include "Player.h"

namespace
{
	const Vector3 CHECKPOINT_SIZE = { 380.0f,200.0f,400.0f };
	const float	  COOLDOWN_TIME = 7.0f;
	const float		TRANSITION_TIME = 1.3f;	//HAMBURGER_LEFT_ENDPOS �ɓ��B���鎞�Ԃ�ݒ�
}

ShopHamburger::ShopHamburger()
{
}

ShopHamburger::~ShopHamburger()
{
	DeleteGO(m_collision);
}

bool ShopHamburger::Start()
{
	Init();
	return true;
}

void ShopHamburger::Init()
{
	m_player = FindGO<nsPlayer::Player>("player");
	m_inventoryUI = FindGO<InventoryUI>("inventoryui");

	m_collision = NewGO<CollisionObject>(0);
	m_collision->CreateBox(
		m_position, 
		m_rotation, 
		CHECKPOINT_SIZE	
		);

	//�R���W�����I�u�W�F�N�g�������ō폜����Ȃ��悤�ɂ���
	m_collision->SetIsEnableAutoDelete(false);

	m_shopHamburgerUI.Init("Assets/Sprite/UI/ShopUI_Hamburger.dds", 224, 150);
	
	m_shopHamburgerX_UI.Init("Assets/Sprite/UI/ShopUI_Hamburger_SoldOut.dds", 224, 150);

	m_shopHamburgerGrayUI.Init("Assets/Sprite/UI6/ShopUI_Hamburger_Gray.dds", 224, 150);
}

void ShopHamburger::Update()
{
	//���X�̑O�����ɉ摜��\���������̂�Z�l�������グ��
	Vector3 pos = m_position;
	pos.x -= 180.0f;
	pos.y += 100.0f;
	//���[���h���W����X�N���[�����W���v�Z
	g_camera3D->CalcScreenPositionFromWorldPosition(m_shopHamburgerUIPos, pos);

	m_shopHamburgerUI.SetPosition(Vector3(m_shopHamburgerUIPos.x, m_shopHamburgerUIPos.y, 0.0f));
	m_shopHamburgerX_UI.SetPosition(Vector3(m_shopHamburgerUIPos.x, m_shopHamburgerUIPos.y, 0.0f));
	m_shopHamburgerGrayUI.SetPosition(Vector3(m_shopHamburgerUIPos.x, m_shopHamburgerUIPos.y, 0.0f));


	
	EffectCoolTime();

	//�Փ˔���
	CollisionPlayerPoint();
	//�n���o�[�K�[�ړ��̊Ǘ�
	HandleHamburgerTrasition();
	//UI�̍X�V
	m_shopHamburgerUI.Update();
	m_shopHamburgerX_UI.Update();
	m_shopHamburgerGrayUI.Update();
}

void ShopHamburger::CollisionPlayerPoint()
{
	//�N�[���^�C�����͉������Ȃ�
	if (m_coolDownTimer > 0.0f)
	{
		m_coolDownTimer -= g_gameTime->GetFrameDeltaTime();
		return;
	}
	if (m_collision == nullptr) {
		return;
	}

	//�R���W�����ƃL�����R�����Փ˂�����
	if (m_collision->IsHit(m_player->GetCharacterController()))
	{
		if (!m_isHaburgerUIMove)
		{
			//Hamburger�̃X���C�h���J�n
			m_isHaburgerUIMove = true;
			m_hamburgerUIMoveTimer = 0.0f;	//�^�C�}�[���Z�b�g
			m_coolDownTimer = COOLDOWN_TIME;	//�N�[���_�E���^�C�}�[���Z�b�g
		}
		else
		{
			//�Փˉ�������N�[���_�E�����͉������Ȃ�	
			if (m_coolDownTimer <= 0.0f)
			{
				m_isHaburgerUIMove = false;
			}
		}
	}
}

void ShopHamburger::EffectCoolTime()
{
	//�N�[���^�C���̌o�ߎ��Ԃ��X�V
	m_effectCoolTimer += g_gameTime->GetFrameDeltaTime();
	//3�b�o�߂�����G�t�F�N�g���Đ�
	if (m_effectCoolTimer >= 2.0f)
	{
		Vector3 effectPosition = m_position;
		effectPosition.x -= 100.0f;
		effectPosition.y += 50.0f;
		PlayEffect(enEffectName_Shop, effectPosition, m_rotation, m_effectScale);

		//�^�C�}�[�����Z�b�g
		m_effectCoolTimer = 0.0f;
	}
}

bool ShopHamburger::CalcAngle()
{
	//�J�������炨�X�̈ʒu�ւ̃x�N�g�������߂�
	Vector3 toShopHumburger = m_position - g_camera3D->GetPosition();
	toShopHumburger.Normalize();
	//�J�����̑O�����ɃJ�������炨�X�ւ̃x�N�g���̓��ς����߂�
	float angle = g_camera3D->GetForward().Dot(toShopHumburger);

	//���ς̌��ʂ���p�x�����߂�
	angle = acos(angle);
	//�J�������猩�Ă��X�����p�x�ȓ��Ȃ�
	if (fabsf(angle) <= Math::DegToRad(50.0f))
	{
		//�v���C���[�Ƃ��X�̋��������߂�
		Vector3 diff = m_position - m_player->GetPostion();
		//��苗���ȓ���������
		if (diff.Length() <= 2000.0f)
		{
			//�`�悷��
			return true;
		}
	}
	//�`�悵�Ȃ�
	return false;
}

void ShopHamburger::HandleHamburgerTrasition()
{
	if (!m_isHaburgerUIMove)
	{
		return;
	}

	//�o�ߎ��Ԃ����Z
	m_hamburgerUIMoveTimer += g_gameTime->GetFrameDeltaTime();

	if (m_hamburgerUIMoveTimer >= TRANSITION_TIME)
	{
		//�t���O�����Z�b�g���ď�Ԃ�i�߂�
		m_isHaburgerUIMove = false;
		m_inventoryUI->NextHamburgerState();	//���̏�Ԃ֐i��

		//�n���o�[�K�[�̏�����������ɒB���Ă��Ȃ��Ȃ�
		if (!GetIsHamburgerFull())
		{
			//���ʉ��̍Đ�
			m_inventoryChangeSE = NewGO<SoundSource>(0);
			m_inventoryChangeSE->Init(enSoundName_inventoryChange);
			m_inventoryChangeSE->SetVolume(1.0f);
			m_inventoryChangeSE->Play(false);
		}
		
	};
}

void ShopHamburger::PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale)
{
	//�G�t�F�N�g�̍Đ�
	EffectEmitter* m_effect = NewGO<EffectEmitter>(0);
	m_effect->Init(name);
	m_effect->SetPosition(pos);
	m_effect->SetRotation(rot);
	m_effect->SetScale(scale);
	m_effect->Play();

}

void ShopHamburger::Render(RenderContext& rc)
{
	if (CalcAngle()==false)
	{
		return;
	}
	if (m_coolDownTimer<=7.0f
		&&m_coolDownTimer>=0.1f
		&& m_isHamburgerFull == false)
	{
		m_shopHamburgerGrayUI.Draw(rc);
	}

	else if (m_inventoryUI->GetIsHasFullHamburger())
	{
		//�n���o�[�K�[���t���ŏ������Ă���ꍇ
		m_shopHamburgerX_UI.Draw(rc);
		m_isHamburgerFull = true;
	}
	else
	{
		//�ʏ�̕`��
		m_shopHamburgerUI.Draw(rc);
		m_isHamburgerFull = false;
	}
	
}

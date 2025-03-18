#include "stdafx.h"
#include "ShopSushi.h"
#include "Player.h"

namespace
{
	const Vector3 CHECKPOINT_SIZE = { 400.0f,200.0f,450.0f };
	const float	  COOLDOWN_TIME = 7.0f;
	const float		MOVE_STOP_SUSHI = 1.7f;	//SUSHI_LEFT_ENDPOS�ɓ��B���鎞��
}

ShopSushi::ShopSushi()
{
}

ShopSushi::~ShopSushi()
{
	DeleteGO(m_collision);
}

bool ShopSushi::Start()
{
	Init();
	return true;
}

void ShopSushi::Init()
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
	//�����i��UI
	m_shopSushiUI.Init("Assets/Sprite/UI/ShopUI_Sushi.dds", 224, 150);

	m_shopSushiX_UI.Init("Assets/Sprite/UI/ShopUI_Sushi_SoldOut.dds", 224, 150);
	m_shopSushiGrayUI.Init("Assets/Sprite/UI/ShopUI_Sushi_Gray.dds", 224, 150);
}

void ShopSushi::Update()
{
	//���X�̑O�����ɉ摜��\���������̂�
	Vector3 pos = m_position;
	pos.y += 100.0f;
	pos.x -= 100.0f;
	//���[���h���W����X�N���[�����W���v�Z
	g_camera3D->CalcScreenPositionFromWorldPosition(m_shopSushiUIPos, pos);
	m_shopSushiUI.SetPosition(Vector3{ m_shopSushiUIPos.x,m_shopSushiUIPos.y,0.0f });
	m_shopSushiX_UI.SetPosition(Vector3{ m_shopSushiUIPos.x,m_shopSushiUIPos.y,0.0f });
	m_shopSushiGrayUI.SetPosition(Vector3{ m_shopSushiUIPos.x,m_shopSushiUIPos.y,0.0f });
	//
	
	EffectCoolTime();
	/*if (m_coolDownTimer >= 0.0f)
	{
		m_coolDownTimer -= g_gameTime->GetFrameDeltaTime();
	}*/
	//else
	//{
		CollisionPlayerPoint();

		//���i�ړ��̊Ǘ�
		HandleSushiTrasition();

		//UI�̍X�V
		m_shopSushiUI.Update();
		m_shopSushiX_UI.Update();
		m_shopSushiGrayUI.Update();
	//}

}

void ShopSushi::CollisionPlayerPoint()
{
	//�N�[���^�C�����͉������Ȃ�
	if (m_coolDownTimer > 0.0f)
	{
		m_coolDownTimer -= g_gameTime->GetFrameDeltaTime();
		return;
	}
	//�R���W�����ƃL�����R�����Փ˂�����
	if (m_collision->IsHit(m_player->GetCharacterController()))
	{
		if (!m_isSushiUIMove)
		{
			m_isSushiUIMove = true;
			m_sushiUIMoveTimer = 0.0f;
			m_coolDownTimer = COOLDOWN_TIME;
		}
		else
		{
			//�Փˉ�������N�[���_�E�����͉������Ȃ�
			if (m_coolDownTimer <= 0.0f)

			{
				m_isSushiUIMove = false;
			}
		}
	//	//���߂ďՓ˂����ꍇ
	//	if (m_isHasCollided_Sushi==false)
	//	{
	//		m_inventoryUI->NextSushiState();	//���i�̏�Ԃ��X�V
	//		m_isHasCollided_Sushi = true;		//�Փ˃t���O�𗧂Ă�
	//		m_coolDownTimer = COOLDOWN_TIME;	//�N�[���^�C�}�[�����Z�b�g
	//	}
	//	
	//}
	//else {
	//	//�Փ˂��������ꂽ�ꍇ�ł��A�N�[���_�E�����̓t���O��ύX���Ȃ�
	//	if (m_coolDownTimer <= 0.0f)
	//	{
	//		m_isHasCollided_Sushi = false;	//�Փ˃t���O�����Z�b�g
	//	}
		
	}
}

void ShopSushi::EffectCoolTime()
{
	//�G�t�F�N�g�̃N�[���^�C���̌o�ߎ��Ԃ��X�V
	m_effectCoolTimer += g_gameTime->GetFrameDeltaTime();
	//2�b�o�߂�����G�t�F�N�g���Đ�
	if (m_effectCoolTimer >= 2.0f)
	{
		Vector3 effectPosition = m_position;
		effectPosition.x -= 100.0f;
		effectPosition.y += 50.0f;
		//�G�t�F�N�g�̍Đ�
		PlayEffect(enEffectName_Shop, effectPosition, m_rotation, m_effectScale);

		//�G�t�F�N�g�̃N�[���^�C�������Z�b�g
		m_effectCoolTimer = 0.0f;
	}
}

bool ShopSushi::CalcAngle()
{
	//�J�������炨�X�̈ʒu�ւ̃x�N�g�������߂�
	Vector3 toShopSushi = m_position - g_camera3D->GetPosition();
	toShopSushi.Normalize();
	//�J�����̑O�����ɃJ�������炨�X�ւ̃x�N�g���̓��ς����߂�
	float angle = g_camera3D->GetForward().Dot(toShopSushi);

	//���ς̌��ʂ���p�x�����߂�
	angle = acos(angle);
	//�J�������猩�Ă��X�����̊p�x�ȓ��Ȃ�
	if (fabs(angle) <= Math::DegToRad(50.0f))
	{
		//�v���C���[�Ƃ��X�̋��������߂�
		Vector3 diff = m_position - m_player->GetPostion();
		//���̋����ȓ���������
		if (diff.Length() <= 2000.0f)
		{
			//�`�悷��
			return true;
		}
	}
	//�`�悵�Ȃ�
	return false;
}

void ShopSushi::HandleSushiTrasition()
{
	if (!m_isSushiUIMove)
	{
		return;
	}

	//�o�ߎ��Ԃ����Z
	m_sushiUIMoveTimer += g_gameTime->GetFrameDeltaTime();
	//SUSHI_LEFT_ENDPOS�ɓ��B���鎞�Ԃ�ݒ�
	//const float transitionSushiTime = 1.7f;
	if (m_sushiUIMoveTimer >= MOVE_STOP_SUSHI)
	{
		//�t���O�����Z�b�g���ď�Ԃ�i�߂�
		m_isSushiUIMove = false;
		m_inventoryUI->NextSushiState();
		//
		if (!GetIsSushiFull())
		{
			//���ʉ��̍Đ�
			m_inventoryChangeSE = NewGO<SoundSource>(0);
			m_inventoryChangeSE->Init(enSoundName_inventoryChange);
			m_inventoryChangeSE->SetVolume(1.0f);
			m_inventoryChangeSE->Play(false);
		}
		
	}
		
}

void ShopSushi::PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale)
{
	//�G�t�F�N�g�̍Đ�
	EffectEmitter* m_effect = NewGO<EffectEmitter>(0);
	m_effect->Init(name);
	m_effect->SetPosition(pos);
	m_effect->SetRotation(rot);
	m_effect->SetScale(scale);
	m_effect->Play();

}

void ShopSushi::Render(RenderContext& rc)
{
	if (CalcAngle() == false)
	{
		return;
	}
	if (m_coolDownTimer <= 7.0f
		&& m_coolDownTimer >=0.1f
		&& m_isSushiFull == false)
	{
		m_shopSushiGrayUI.Draw(rc);
	}

	else if (m_inventoryUI->GetIsHasFullSushi())
	{
		//���i���t���ŏ������Ă���ꍇ
		m_shopSushiX_UI.Draw(rc);
		m_isSushiFull = true;
	}
	else
	{
		//�ʏ�̕`��
		m_shopSushiUI.Draw(rc);
		m_isSushiFull = false;
	}
	
}



#include "stdafx.h"
#include "ShopPizza.h"
#include "Player.h"

namespace
{
	const Vector3	CHECKPOINT_SIZE = { 478.0f,200.0f,428.0f };
	const float		COOLDOWN_TIME = 7.0f;
	const float		MOVE_STOP_PIZZA = 1.5f; //PIZZA_LEFT_ENDPOS�ɓ��B���鎞��
}

ShopPizza::ShopPizza()
{
}

ShopPizza::~ShopPizza()
{
	DeleteGO(m_collision[0]);
}

bool ShopPizza::Start()
{
	Init();
	return true;
}

void ShopPizza::Init()
{
	m_player = FindGO<nsPlayer::Player>("player");
	m_inventoryUI = FindGO<InventoryUI>("inventoryui");

	m_collision[0] = NewGO<CollisionObject>(0);
	m_collision[0]->CreateBox(
		m_position,
		m_rotation,
		CHECKPOINT_SIZE
	);

	//�R���W�����I�u�W�F�N�g�������ō폜����Ȃ��悤�ɂ���
	m_collision[0]->SetIsEnableAutoDelete(false);
	//���X��UI
	m_shopPizzaUI.Init("Assets/Sprite/UI/ShopUI_Pizza.dds", 224, 150);

	m_shopPizzaX_UI.Init("Assets/Sprite/UI/ShopUI_Pizza_SoldOut.dds", 224, 150);

	m_shopPizzaGrayUI.Init("Assets/Sprite/UI/ShopUI_Pizza_Gray.dds", 224, 150);
}


void ShopPizza::Update()
{
	//���X�̑O�����ɉ摜��\���������̂�X�l�AY�l�𒲐�
	Vector3 pos = m_position;
	pos.x += 180.0f;
	pos.y += 100.0f;
	//���[���h���W����X�N���[�����W���v�Z
	g_camera3D->CalcScreenPositionFromWorldPosition(m_shopPizzaUIPos, pos);
	m_shopPizzaUI.SetPosition(Vector3(m_shopPizzaUIPos.x, m_shopPizzaUIPos.y, 0.0f));
	m_shopPizzaX_UI.SetPosition(Vector3(m_shopPizzaUIPos.x, m_shopPizzaUIPos.y, 0.0f));
	m_shopPizzaGrayUI.SetPosition(Vector3(m_shopPizzaUIPos.x, m_shopPizzaUIPos.y, 0.0f));
	
	
	EffectCoolTime();
	/*if (m_coolDownTimer >= 0.0f)
	{
		m_coolDownTimer -= g_gameTime->GetFrameDeltaTime();
	}*/
	//else
	//{
		CollisionPlayerPoint();

		//�s�U�ړ��̊Ǘ�
		HandlePizzaTrasition();

		//UI�̍X�V
		m_shopPizzaUI.Update();
		m_shopPizzaX_UI.Update();
		m_shopPizzaGrayUI.Update();
	//}
	
}

void ShopPizza::CollisionPlayerPoint()
{
	//�N�[���_�E�����͉������Ȃ�
	if (m_coolDownTimer > 0.0f)
	{
		m_coolDownTimer -= g_gameTime->GetFrameDeltaTime();
		return;
	}
	//�R���W�����ƃL�����R�����Փ˂�����
	if (m_collision[0]->IsHit(m_player->GetCharacterController()))
	{
		if (!m_isPizzaUIMove)
		{
			m_isPizzaUIMove = true;
			m_pizzaUIMoveTimer = 0.0f;
			m_coolDownTimer = COOLDOWN_TIME;
		}
		else
		{
			//�Փˉ�������N�[���_�E�����͉������Ȃ�
			if (m_coolDownTimer <= 0.0f)
			{
				m_isPizzaUIMove = false;
			}
		}

	//	//���߂ďՓ˂����ꍇ
	//	if (m_isHasCollided_Pizza == false) 
	//	{
	//		m_inventoryUI->NextPizzaState();	//�s�U�̏�Ԃ��X�V
	//		m_isHasCollided_Pizza = true;		//�Փ˃t���O�𗧂Ă�
	//		m_coolDownTimer = COOLDOWN_TIME;	//�N�[���^�C�������Z�b�g
	//	}
	//}
	//else {
	//	//�Փ˂��������ꂽ�ꍇ�ł��A�N�[���_�E�����̓t���O��ύX���Ȃ�
	//	if (m_coolDownTimer <= 0.0f)
	//	{
	//		m_isHasCollided_Pizza = false;		//�Փ˃t���O�����Z�b�g
	//	}
	
	}
}

void ShopPizza::EffectCoolTime()
{
	//�N�[���^�C���̌o�ߎ��Ԃ��X�V
	m_effectCoolTimer += g_gameTime->GetFrameDeltaTime();
	//3�b�o�߂�����G�t�F�N�g���Đ�
	if (m_effectCoolTimer >= 2.0f)
	{
		Vector3 effectPosition = m_position;
		effectPosition.x += 100.0f;
		effectPosition.y += 50.0f;
		PlayEffect(enEffectName_Shop, effectPosition, m_rotation, m_effectScale);
		//�^�C�}�[�����Z�b�g
		m_effectCoolTimer = 0.0f;
	}
}

bool ShopPizza::CalcAngle()
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

void ShopPizza::HandlePizzaTrasition()
{
	if (!m_isPizzaUIMove)
	{
		return;
	}

	//�o�ߎ��Ԃ����Z
	m_pizzaUIMoveTimer += g_gameTime->GetFrameDeltaTime();
;

	if (m_pizzaUIMoveTimer >= MOVE_STOP_PIZZA)
	{
		//�t���O�����Z�b�g���ď�Ԃ�i�߂�
		m_isPizzaUIMove = false;
		m_inventoryUI->NextPizzaState();
		if (!GetIsPizzaFull())
		{
			//���ʉ��̍Đ�
			m_inventoryChangeSE = NewGO<SoundSource>(0);
			m_inventoryChangeSE->Init(enSoundName_inventoryChange);
			m_inventoryChangeSE->SetVolume(1.0f);
			m_inventoryChangeSE->Play(false);
		}
		

	}
}

void ShopPizza::PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale)
{
	//�G�t�F�N�g�̍Đ�
	EffectEmitter* m_effect = NewGO<EffectEmitter>(0);
	m_effect->Init(name);
	m_effect->SetPosition(pos);
	m_effect->SetRotation(rot);
	m_effect->SetScale(scale);
	m_effect->Play();
}

void ShopPizza::Render(RenderContext& rc)
{
	if (CalcAngle() == false)
	{
		return;
	}

	if (m_coolDownTimer<=7.0f
		&& m_coolDownTimer>=0.1f
		//m_isHasCollided_Pizza == true
		&& m_isPizzaFull == false)
	{
		m_shopPizzaGrayUI.Draw(rc);
	}
	else if (m_inventoryUI->GetIsHasFullPizza())
	{
		//�s�U���t���ŏ������Ă���ꍇ
		m_shopPizzaX_UI.Draw(rc);
		m_isPizzaFull = true;
	}
	else
	{
		//�ʏ�̕`��
		m_shopPizzaUI.Draw(rc);
		m_isPizzaFull = false;
	}
	
}

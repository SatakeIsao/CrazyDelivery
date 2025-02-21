#include "stdafx.h"
#include "CustomerMan_Hamburger.h"
#include "Game.h"
#include "ResultUI.h"
#include "InventoryUI.h"
#include "GameSound.h"
namespace
{

	const float RESET_TIME_THRESHOLD = 3.0f;				//���Z�b�g�^�C���̂������l
	const int	REWARD_HAMBURGER = 150.0f;					//�n���o�[�K�[��͂������̕�V
	const float MAX_RENDER_DISTANCE = 2000.0f;				//�v���C���[�Ƃ��q����̍ő勗��
	const float CAMERA_VIEW_ANGLE = Math::DegToRad(50.0f);	//�J�����̎���p
	const float EFFECT_COOL_TIME = 2.0f;					//�G�t�F�N�g�Đ��Ԋu
	const float UI_HEIGHT_OFFSET = 100.0f;					//UI��Y���I�t�Z�b�g
	const float EFFECT_Y_OFFSET = 10.0f;					//�G�t�F�N�g��Y���I�t�Z�b�g
}

CustomerMan_Hamburger::CustomerMan_Hamburger()
{
}

CustomerMan_Hamburger::~CustomerMan_Hamburger()
{
	DeleteGO(m_collision);
}


void CustomerMan_Hamburger::Init()
{
	//������]��ݒ�
	m_rotation.SetRotationDegZ(0.0f);

	//���f���̏�����
	m_customerMan_Hamburger.Init("Assets/Customer/Man2/human.tkm", m_manAnimClips, enAnimClip_Num,enModelUpAxisY,true,false);
	m_customerMan_Hamburger.SetPosition(m_position);
	m_customerMan_Hamburger.SetRotation(m_rotation);
	m_customerMan_Hamburger.SetScale(m_scale);
	m_customerMan_Hamburger.Update();

	//���q����̓���ɕ\������UI
	m_customerUI.Init("Assets/Customer/UI/CustomerHamburger.DDS",224,150);
	m_customerUI_Thank.Init("Assets/skaterData/PlayerUI_Thank2.dds", 1920, 1080);
	m_customerMan = &m_customerMan_Hamburger;
}
void CustomerMan_Hamburger::CollisionPlayerPoint()
{
	//�R���W�����ƃL�����R�����Փ˂�����
	if (m_collision->IsHit(m_player->GetCharacterController()))
	{
		//�Փˉ\���A�n���o�[�K�������Ă���ꍇ
		if (m_inventoryUI->GetIsHasHamburger() 
			&&  m_isHasCollided_Man == false)
		{
			m_inventoryUI->PreviousHamburgerState();
			m_isHasCollided_Man = true;	//�Փ˃t���O�𗧂Ă�
			m_isScoreAdded = true;
			m_scoreResetTimer = RESET_TIME_THRESHOLD; //���Z�b�g�^�C�}�[��ݒ�
			//�X�R�A�̒ǉ�
			m_resultUI->ScoreAdded(REWARD_HAMBURGER);
			
			//�v���C���[�̑��x���[���Ƀ��Z�b�g�i�u���[�L�j
			m_player->SetBrake();
		}
	}
	else {
		//�Փ˂��������ꂽ�ꍇ
		m_isHasCollided_Man = false;
		m_isScoreAdded = false;
		m_isSoundPlayed = false;
	}
}

bool CustomerMan_Hamburger::CalcAngle()
{
	//�J�������炨�q����̈ʒu�ւ̃x�N�g�������߂�
	Vector3 toCustomerHamburger = m_position - g_camera3D->GetPosition();
	toCustomerHamburger.Normalize();

	//�J�����̑O�����ƃJ�������炨�q����ւ̃x�N�g���̓��ς����߂�
	float angle = g_camera3D->GetForward().Dot(toCustomerHamburger);

	//���ς̌��ʂ���p�x�����߂�
	angle = acos(angle);
	//�J�������猩�Ă��q���񂪈��p�x�ȓ��̎�
	if (fabsf(angle) <= CAMERA_VIEW_ANGLE)
	{
		//�v���C���[�Ƃ��q����̋��������߂�
		Vector3 diff = m_position - m_player->GetPostion();
		//��苗���ȓ���������
		if (diff.Length() <= MAX_RENDER_DISTANCE)
		{
			//�`�悷��
			return true;
		}
	}
	//�`�悵�Ȃ�
	return false;
}

void CustomerMan_Hamburger::CoolTime()
{
	// OnUpdate�Ń��Z�b�g����
	if (m_scoreResetTimer > 0.0f)
	{
		m_scoreResetTimer -= g_gameTime->GetFrameDeltaTime();
		if (m_scoreResetTimer < 0.0f)
		{
			m_scoreResetTimer = 0.0f;	//�^�C�}�[�����Z�b�g
		}
	}
}

void CustomerMan_Hamburger::EffectCoolTime()
{
	//�N�[���^�C���̌o�ߎ��Ԃ��X�V
	m_effectCoolTimer += g_gameTime->GetFrameDeltaTime();
	//�Փ˂��Ă��Ȃ��ꍇ
	if (m_isHasCollided_Man == false)
	{
		//2�b�o�߂�����G�t�F�N�g���Đ�
		if (m_effectCoolTimer >= EFFECT_COOL_TIME)
		{
			Vector3 effectPosition = m_position;
			effectPosition.y += EFFECT_Y_OFFSET;
			//�G�t�F�N�g���Đ�
			PlayEffect(enEffectName_CustomerPizza, effectPosition, m_rotation, m_effectScale);
			//�^�C�}�[�����Z�b�g
			m_effectCoolTimer = 0.0f;
		}
	}		
}

void CustomerMan_Hamburger::OnUpdate()
{
		
	//�G�t�F�N�g�̃N�[������
	EffectCoolTime();
	//�N�[������
	CoolTime();
	//�v���C���[�Ƃ̏Փ˔���
	CollisionPlayerPoint();
	//�v���C���[�̑O�����ɂ��q�����������
	if (CalcAngle())
	{
		//�v���C���[�̑O�������擾
		Vector3 playerForward = m_player->GetForward();
		playerForward.y = 0.0f; //Y�������̉e�������O
		playerForward.Normalize();

		//�v���C���[��Y����]�p�x���擾
		float playerAngleY = atan2(playerForward.x, playerForward.z);
		float customerAngleY = playerAngleY + Math::PI; //180�x���]

		//�v���C���[�̉�]�����̂܂ܓK�p
		m_rotation.SetRotationY(customerAngleY);
	}

	//���q����i�j���j���f���̍X�V
	m_customerMan_Hamburger.SetPosition(m_position);
	m_customerMan_Hamburger.SetRotation(m_rotation);
	m_customerMan_Hamburger.SetScale(m_scale);
	m_customerMan_Hamburger.Update();

	//�I�u�W�F�N�g�̏�̕��ɉ摜��\���������̂�Y���������グ��
	Vector3 position = m_position;
	position.y += UI_HEIGHT_OFFSET;
	//���[���h���W����X�N���[�����W���v�Z
	g_camera3D->CalcScreenPositionFromWorldPosition(m_customerUIPos, position);
	m_customerUI.SetPosition(Vector3(m_customerUIPos.x, m_customerUIPos.y, 0.0f));
	m_customerUI.Update();
	m_customerUI_Thank.SetPosition(Vector3(m_customerUIPos.x, m_customerUIPos.y, 0.0f));
	m_customerUI_Thank.Update();
}

void CustomerMan_Hamburger::Render(RenderContext& rc)
{
	//���q����i�j���j���f���̍X�V
	m_customerMan_Hamburger.Draw(rc);

	//�`��͈͊O�̏ꍇ�͕`�悵�Ȃ�
	if (CalcAngle() == false)
	{
		return;
	}

	//Player�ƏՓ˂�����
	if (m_isHasCollided_Man == true)
	{
		m_customerUI_Thank.Draw(rc);
			
		if (m_isSoundPlayed==false)
		{
			m_rewardGot = NewGO<SoundSource>(0);
			m_rewardGot->Init(enSoundName_RewardGot);
			m_rewardGot->SetVolume(1.0f);

			m_rewardGot->Play(false);
			m_isSoundPlayed = true;
		}
	}
	else 
	{
		//�ʏ�UI�̕`��
		m_customerUI.Draw(rc);
	}		
}
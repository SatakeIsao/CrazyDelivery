#include "stdafx.h"
#include "CustomerMan_Sushi.h"
#include "Game.h"
#include "ResultUI.h"
#include "InventoryUI.h"
#include "GameSound.h"
namespace
{
	const float RESET_TIME_THRESHOLD = 3.0f;				//���Z�b�g�^�C���̂������l
	const int	REWARD_SUSHI = 500.0f;						//�n���o�[�K�[��͂������̕�V
	const float MAX_RENDER_DISTANCE = 2000.0f;				//�v���C���[�Ƃ��q����̍ő勗��
	const float CAMERA_VIEW_ANGLE = Math::DegToRad(50.0f);	//�J�����̎���p
	const float EFFECT_COOL_TIME = 2.0f;					//�G�t�F�N�g�Đ��Ԋu
	const float UI_HEIGHT_OFFSET = 100.0f;					//UI��Y���I�t�Z�b�g
	const float EFFECT_Y_OFFSET = 10.0f;					//�G�t�F�N�g��Y���I�t�Z�b�g
}

CustomerMan_Sushi::CustomerMan_Sushi()
{
}

CustomerMan_Sushi::~CustomerMan_Sushi()
{
	DeleteGO(m_collision);
}

void CustomerMan_Sushi::Init()
{
	//������]��ݒ�
	m_rotation.SetRotationDegZ(0.0f);

	//���f���̏�����
	m_customerMan_Sushi.Init("Assets/Customer/Man2/human3.tkm", m_manAnimClips, enAnimClip_Num, enModelUpAxisY, true, false);
	m_customerMan_Sushi.SetPosition(m_position);
	m_customerMan_Sushi.SetRotation(m_rotation);
	m_customerMan_Sushi.SetScale(m_scale);
	m_customerMan_Sushi.Update();

	//���q����̓���ɕ\������UI
	m_customerUI.Init("Assets/Customer/UI/CustomerSushi.DDS", 224, 150);
	m_customerUI_Thank.Init("Assets/skaterData/PlayerUI_Thank2.dds", 1920, 1080);
	m_customerMan = &m_customerMan_Sushi;
}

void CustomerMan_Sushi::CollisionPlayerPoint()
{
	//�R���W�����ƃL�����R�����Փ˂�����
	if (m_collision->IsHit(m_player->GetCharacterController()))
	{
		//�Փˉ\���A���i�������Ă��邩
		if (m_inventoryUI->GetIsHasSushi() 
			&& m_isHasCollided_Man == false)
		{
			m_inventoryUI->PreviousSushiState();
			m_isHasCollided_Man = true;	//�Փ˔���t���O�𗧂Ă�
			m_isScoreAdded = true;
			m_scoreResetTimer = RESET_TIME_THRESHOLD; //���Z�b�g�^�C�}�[��ݒ�
			//�X�R�A�̒ǉ�
			m_resultUI->ScoreAdded(REWARD_SUSHI);
			//�v���C���[�̑��x���[���Ƀ��Z�b�g�i�u���[�L�j
			m_player->SetBrake();
		}
	}
	else {
		//�Փ˂��������ꂽ�ꍇ
		m_isHasCollided_Man = false;
		m_isScoreAdded = false;
		m_isSEPlayed = false;
	}
}

bool CustomerMan_Sushi::CalcAngle()
{
	//�J�������炨�q����̈ʒu�ւ̃x�N�g�������߂�
	Vector3 toCustomerSushi = m_position - g_camera3D->GetPosition();
	toCustomerSushi.Normalize();

	//�J�����̑O�����ƃJ�������炨�q����ւ̃x�N�g���̓��ς����߂�
	float angle = g_camera3D->GetForward().Dot(toCustomerSushi);

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

void CustomerMan_Sushi::CoolTime()
{
	// OnUpdate�Ń��Z�b�g����
	if (m_scoreResetTimer > 0.0f)
	{
		m_scoreResetTimer -= g_gameTime->GetFrameDeltaTime();
		if (m_scoreResetTimer < 0.0f)
		{
			m_scoreResetTimer = 0.0f; //�^�C�}�[�����Z�b�g
		}
	}

}

void CustomerMan_Sushi::EffectCoolTime()
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

void CustomerMan_Sushi::OnUpdate()
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
		playerForward.y = 0.0f;
		playerForward.Normalize();

		//�v���C���[��Y����]�p�x���擾
		float playerAngleY = atan2(playerForward.x, playerForward.z);
		float customerAngleY = playerAngleY + Math::PI;

		//�v���C���[�̉�]�����̂܂ܓK�p
		m_rotation.SetRotationY(customerAngleY);
	}
	//���q����i�j���j���f���̍X�V
	m_customerMan_Sushi.SetPosition(m_position);
	m_customerMan_Sushi.SetRotation(m_rotation);
	m_customerMan_Sushi.SetScale(m_scale);
	m_customerMan_Sushi.Update();

	//�I�u�W�F�N�g�̏�̕��ɉ摜��\���������̂�Y���������グ��
	Vector3 position = m_position;
	position.y += UI_HEIGHT_OFFSET;
	//���[���h���W����X�N���[�����W���v�Z
	g_camera3D->CalcScreenPositionFromWorldPosition(m_customerUIPos, position);
	m_customerUI.SetPosition(Vector3(m_customerUIPos.x, m_customerUIPos.y, 0.0f));
	m_customerUI_Thank.SetPosition(Vector3(m_customerUIPos.x, m_customerUIPos.y, 0.0f));
	m_customerUI.Update();
	m_customerUI_Thank.Update();
}

void CustomerMan_Sushi::Render(RenderContext& rc)
{
	//���q����i�j���j���f���̕`��
	m_customerMan_Sushi.Draw(rc);

	//�`��͈͊O�̏ꍇ�͕`�悵�Ȃ�
	if (CalcAngle() == false)
	{
		return;
	}

	//Player�ƏՓ˂�����
	if (m_isHasCollided_Man == true)
	{
		m_customerUI_Thank.Draw(rc);

		if (m_isSEPlayed == false)
		{
			m_rewardGot = NewGO<SoundSource>(0);
			m_rewardGot->Init(enSoundName_RewardGot);
			m_rewardGot->SetVolume(1.0f);
			m_rewardGot->Play(false);
			m_isSEPlayed = true;
		}
	}
	else
	{
		//�ʏ�UI�̕`��
		m_customerUI.Draw(rc);
	}
}


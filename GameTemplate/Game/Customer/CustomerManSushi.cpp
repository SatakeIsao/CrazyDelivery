#include "stdafx.h"
#include "Customer/CustomerManSushi.h"
#include "Scene/Game.h"
#include "UI/ResultUI.h"
#include "UI/InventoryUI.h"

namespace
{
	const int	REWARD_SUSHI = 500.0f;						//���i��͂������̕�V
	const float RESET_TIME_THRESHOLD = 3.0f;				//���Z�b�g�^�C���̂������l
	const float MAX_RENDER_DISTANCE = 2000.0f;				//�v���C���[�Ƃ��q����̍ő勗��
	const float CAMERA_VIEW_ANGLE = Math::DegToRad(50.0f);	//�J�����̎���p
	const float EFFECT_COOL_TIME = 2.0f;					//�G�t�F�N�g�Đ��Ԋu
	const float UI_HEIGHT_OFFSET = 100.0f;					//UI��Y���I�t�Z�b�g
	const float EFFECT_Y_OFFSET = 10.0f;					//�G�t�F�N�g��Y���I�t�Z�b�g
}

CustomerManSushi::CustomerManSushi()
{
}

CustomerManSushi::~CustomerManSushi()
{
	DeleteGO(m_collision);
}

void CustomerManSushi::Render(RenderContext& rc)
{
	CustomerMan::Render(rc);
	
	//�`��͈͊O�̏ꍇ�͕`�悵�Ȃ�
	if (!IsEnableAngle(CAMERA_VIEW_ANGLE, MAX_RENDER_DISTANCE))
	{
		return;
	}

	//Player�ƏՓ˂�����
	if (m_isHasCollidedMan)
	{
		//���ӂ�\��UI�̕`��
		m_iconThank.Draw(rc);
	}
	else
	{
		//�ʏ�UI�̕`��
		m_iconOrder.Draw(rc);
	}
}

void CustomerManSushi::Init()
{

	//������]��ݒ�
	m_rotation.SetRotationDegZ(0.0f);

	//���f���̏�����
	m_modelRender.Init("Assets/ModelData/Customer/Man/Man_Sushi.tkm", m_manAnimClips, enAnimClip_Num, enModelUpAxisY, true, false);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();

	//���q����̓���ɕ\������UI
	m_iconOrder.Init("Assets/Sprite/UI/CustomerOrderIcon_Sushi.DDS", 224, 150);
	m_iconThank.Init("Assets/Sprite/UI/CustomerOrderIcon_Thank.dds", 1920, 1080);
}

void CustomerManSushi::OnUpdate()
{
	//�G�t�F�N�g�̃N�[������
	UpdateMarkEffect();
	//�N�[������
	UpdateCoolTime();
	//�v���C���[�Ƃ̏Փ˔���
	UpdateHitPlayerCollision();
	//�v���C���[�̑O�����ɂ��q�����������
	if (IsEnableAngle(CAMERA_VIEW_ANGLE, MAX_RENDER_DISTANCE))
	{
		//�v���C���[�̑O�������擾
		Vector3 playerForward = m_player->GetForward();
		playerForward.y = 0.0f;
		playerForward.Normalize();

		//�v���C���[��Y����]�p�x���擾
		const float playerAngleY = atan2(playerForward.x, playerForward.z);
		const float customerAngleY = playerAngleY + Math::PI;

		//�v���C���[�̉�]�����̂܂ܓK�p
		m_rotation.SetRotationY(customerAngleY);
	}
	//���q����i�j���j���f���̍X�V
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();

	//�I�u�W�F�N�g�̏�̕��ɉ摜��\���������̂�Y���������グ��
	Vector3 position = m_position;
	position.y += UI_HEIGHT_OFFSET;
	//���[���h���W����X�N���[�����W���v�Z
	g_camera3D->CalcScreenPositionFromWorldPosition(m_iconPos, position);
	m_iconOrder.SetPosition(Vector3(m_iconPos.x, m_iconPos.y, 0.0f));
	m_iconOrder.Update();
	m_iconThank.SetPosition(Vector3(m_iconPos.x, m_iconPos.y, 0.0f));
	m_iconThank.Update();
}

void CustomerManSushi::UpdateHitPlayerCollision()
{
	//�R���W�����ƃL�����R�����Փ˂�����
	if (m_collision->IsHit(m_player->GetCharacterController()))
	{
		//�Փˉ\���A���i�������Ă��邩
		if (m_inventoryUI->GetIsHasSushi()
			&& !m_isHasCollidedMan)
		{
			m_inventoryUI->PreviousSushiState();
			m_isHasCollidedMan = true;	//�Փ˔���t���O�𗧂Ă�
			m_isScoreAdded = true;		//�X�R�A���Z�t���O�𗧂Ă�
			m_scoreResetTimer = RESET_TIME_THRESHOLD; //���Z�b�g�^�C�}�[��ݒ�
			//�X�R�A�̒ǉ�
			m_resultUI->ScoreAdded(REWARD_SUSHI);
			//�v���C���[�̑��x���[���Ƀ��Z�b�g�i�u���[�L�j
			m_player->SetBrake();

			// �T�E���h�Đ�
			if (m_isSEPlayed == false)
			{
				PlaySoundSE(enSoundName_RewardGot, 1.0f, false);
				m_isSEPlayed = true;
			}
		}
	}
	else
	{
		//�Փ˂��������ꂽ�ꍇ
		m_isHasCollidedMan = false;
		m_isScoreAdded = false;
		m_isSEPlayed = false;
	}
}

void CustomerManSushi::UpdateMarkEffect()
{
	//�N�[���^�C���̌o�ߎ��Ԃ��X�V
	m_effectCoolTimer += g_gameTime->GetFrameDeltaTime();
	//�Փ˂��Ă��Ȃ��ꍇ
	if (!m_isHasCollidedMan)
	{
		//2�b�o�߂�����G�t�F�N�g���Đ�
		if (m_effectCoolTimer >= EFFECT_COOL_TIME)
		{
			Vector3 effectPosition = m_position;
			effectPosition.y += EFFECT_Y_OFFSET;
			//�G�t�F�N�g���Đ�
			PlayEffect(enEffectName_Customer, effectPosition, m_rotation, m_effectScale);
			//�^�C�}�[�����Z�b�g
			m_effectCoolTimer = 0.0f;
		}
	}
}

void CustomerManSushi::UpdateCoolTime()
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
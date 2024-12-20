#include "stdafx.h"
#include "CustomerMan_Hamburger.h"
#include "Game.h"

namespace
{
	//���Z�b�g�^�C���̂������l
	const float RESET_TIME_THRESHOLD = 3.0f;
	//�n���o�[�K�[��͂������̕�V
	const int	REWARD_HAMBURGER = 150.0f;
}

namespace nsCustomerMan
{
	void CustomerMan_Hamburger::Init()
	{
		m_rotation.SetRotationDegZ(0.0f);
		m_customerMan_Hamburger.Init("Assets/Customer/Man2/human.tkm", m_manAnimClips, enAnimClip_Num);
		//m_customerMan.Init("Assets/Customer/Man2/man.tkm");
		m_customerMan_Hamburger.SetPosition(m_position);
		m_customerMan_Hamburger.SetRotation(m_rotation);
		m_customerMan_Hamburger.SetScale(m_scale);
		m_customerMan_Hamburger.Update();
		//���q����̓���ɕ\������UI
		m_customerUI.Init("Assets/Customer/UI/CustomerHamburger.DDS",224,126);

		m_customerMan = &m_customerMan_Hamburger;
	}
	void CustomerMan_Hamburger::CollisionPlayerPoint()
	{
		//�R���W�����ƃL�����R�����Փ˂�����
		if (m_collision->IsHit(m_player->GetCharacterController()))
		{
			if (m_inventoryUI->GetIsHasHamburger() &&  m_isHasCollided_Man == false)
			{
				m_inventoryUI->PreviousHamburgerState();
				m_isHasCollided_Man = true;
				m_isScoreAdded = true;
				m_game->ScoreAdded(REWARD_HAMBURGER);
				//m_isScoreAdded = true;
				//m_hamburgerScore += REWARD_HAMBURGER;
				m_scoreResetTimer = 0.0f;
			}
		}
		else {
			m_isHasCollided_Man = false;
			m_isScoreAdded = false;
			//m_hamburgerScore = 0.0f;
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
		if (fabsf(angle) <= Math::DegToRad(50.0f))
		{
			//�v���C���[�Ƃ��q����̋��������߂�
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

	void CustomerMan_Hamburger::CoolTime()
	{
		// OnUpdate�Ń��Z�b�g����
		if (m_isHamburgerScoreAdded)
		{
			m_scoreResetTimer += g_gameTime->GetFrameDeltaTime();
			if (m_scoreResetTimer > RESET_TIME_THRESHOLD) // 3�b��Ƀ��Z�b�g
			{
				m_isHamburgerScoreAdded = false;
				m_scoreResetTimer = 0.0f; // �^�C�}�[�����Z�b�g
			}
		}
	}

	void CustomerMan_Hamburger::EffectCoolTime()
	{
		//�N�[���^�C���̌o�ߎ��Ԃ��X�V
		m_effectCoolTimer += g_gameTime->GetFrameDeltaTime();
		//3�b�o�߂�����G�t�F�N�g���Đ�
		if (m_effectCoolTimer >= 2.0f)
		{
			Vector3 effectPosition = m_position;
			effectPosition.y += 10.0f;
			PlayEffect(enEffectName_CustomerHamburger, effectPosition, m_rotation, m_effectScale);
			//�^�C�}�[�����Z�b�g
			m_effectCoolTimer = 0.0f;
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

		m_customerMan_Hamburger.SetPosition(m_position);
		m_customerMan_Hamburger.SetRotation(m_rotation);
		m_customerMan_Hamburger.SetScale(m_scale);
		m_customerMan_Hamburger.Update();

		//�I�u�W�F�N�g�̏�̕��ɉ摜��\���������̂�Y���������グ��
		Vector3 position = m_position;
		position.y += 100.0f;
		//���[���h���W����X�N���[�����W���v�Z
		g_camera3D->CalcScreenPositionFromWorldPosition(m_customerUIPos, position);
		m_customerUI.SetPosition(Vector3(m_customerUIPos.x, m_customerUIPos.y, 0.0f));
		m_customerUI.Update();
		//m_customerMan_Hamburger.

	}

	void CustomerMan_Hamburger::Render(RenderContext& rc)
	{
		m_customerMan_Hamburger.Draw(rc);

		if (CalcAngle() == false)
		{
			return;
		}
		m_customerUI.Draw(rc);
	}
	
}

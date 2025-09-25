#pragma once
class StartButtonUI : public IGameObject
{
public:

	//UI�̏�Ԃ�\���X�e�[�g
	enum EnStartUIState
	{
		enStartUIState_FadeIn,		//���邭�Ȃ���
		enStartUIState_FadeOut,		//�����Ă������
		enStartUIState_AlphaZero,	//�A���t�@�l��0�̏��
	};

	StartButtonUI();
	~StartButtonUI();

	bool Start();
	void Update();
	void FadeProcess();
	void FadeOut();
	void AlphaZero();
	void CalcAlpha(float& alpha);
	void Render(RenderContext& rc);



	/// <summary>
	/// ��Ԃ�ݒ�
	/// </summary>
	/// <param name="enStartUIState"></param>
	void SetState(EnStartUIState enStartUIState)
	{
		m_startUIState = enStartUIState;
	};

	EnStartUIState GetStete() const
	{
		return m_startUIState;
	}

	void ResetButtonState()
	{
		m_isButtonPush = false;
	}

	bool GetButtonPush()
	{
		return m_isButtonPush;
	}

private:
	EnStartUIState m_startUIState = enStartUIState_FadeIn;	//������ԁFFadeIn
	SpriteRender m_startSprite;								//�X�^�[�g�̃X�v���C�g�\���p
	SoundSource* m_buttonSE;								//�{�^������SE
	float m_fadeAlpha = 1.0f;								//�A���t�@�l
	float m_fadeTime = 0.5f;								//�t�F�[�h���Ǘ����鎞��
	bool m_isButtonPush = false;							//�X�^�[�g�{�^���͉����ꂽ���ǂ���
	//bool m_drawButtonUI = false;							//�{�^��BUI�͕`�悳��Ă��邩
};


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

private:
	EnStartUIState m_startUIState = enStartUIState_FadeIn;	//������ԁFFadeIn
	//SpriteInitData m_initStartData;
	SpriteRender m_startSprite;						 //�X�^�[�g�̃X�v���C�g�\���p
	float m_alpha = 1.0f;							 //�A���t�@�l
	float m_time = 0.5f;							 
};


#pragma once
class FocusLine : public IGameObject
{
public:
	FocusLine();
	~FocusLine();

	bool Start();
	/// <summary>
	/// �X�v���C�g��������
	/// </summary>
	void InitSprite();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// �O����g�嗦���w��
	/// NOTE:�����ɕω�����̂ł͂Ȃ����X�ɕω������邽�߁A���`��ԂɕK�v�ȏ������̂Ƃ��ɕۑ�
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(const float scale)
	{
		m_targetScale = scale;
		m_saveScale = m_currentScale;
	}
private:
	SpriteRender m_focusLineSprite;	//�W�����̃X�v���C�g
	Vector3 m_position;				//���W
	float m_targetScale;			//�ڕW�g�嗦
	float m_saveScale = 0.0f;		//�O��̊g�嗦
	float m_currentScale = 0.0f;	//���݂̊g�嗦
	float m_elapsedTimer = 0.0f;	//�o�ߎ���
	bool m_isEffectVisible = false;
};


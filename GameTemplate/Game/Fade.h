#pragma once
class Fade : public IGameObject
{
public:
	~Fade();
	bool Start();
	void Update();
	void CalcRotation();
	void CalcFadeAlpha();
	void MakeGame();
	void Render(RenderContext& rc);

	/// <summary>
	/// �t�F�[�h�������̒ʒm��ݒ�
	/// </summary>
	/// <param name="callback"></param>
	void SetOnFadeOutComplete(std::function<void()> callback);
	
	/// <summary>
	/// �t�F�[�h�C���J�n
	/// </summary>
	void StartFadeIn() 
	{
		m_isFadeStart = true;		//�t�F�[�h�������J�n
		m_isFadeOut = true;			//�t�F�[�h�C���i���邭����j
		m_fadeSpriteAlpha = 1.0f;	//���S�ɈÂ�������Ԃ���J�n
	}

	void StartFadeOut()
	{
		m_isFadeStart = true;		//�t�F�[�h�������J�n
		m_isFadeOut = false;		//�t�F�[�h�A�E�g�i�Â�����j
		m_fadeSpriteAlpha = 0.0f;	//���S�ɖ��邢��Ԃ���J�n
	}
private:
	SpriteRender m_fadeSprite;					//�t�F�[�h�p�X�v���C�g
	SpriteRender m_loadSprite;					//���[�h�p�X�v���C�g
	float m_fadeSpriteAlpha = 0.0f;				//�t�F�[�h�p�̃A���t�@�l
	float m_rotLoad = 0.0f;
	Quaternion m_loadRot;
	bool m_isFadeStart = true;					//�t�F�[�h���J�n���ꂽ��	
	bool m_isFadeComplete = false;				//�^���ÂɂȂ�����
	bool m_isFadeOut = false;					//���邭�Ȃ�t�F�[�Y��
	std::function<void()> m_onFadeOutComplete;	//�t�F�[�h�����ʒm�R�[���o�b�N
};


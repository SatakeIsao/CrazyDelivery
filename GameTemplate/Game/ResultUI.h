#pragma once

class GameTimer;
class Game;
class InventoryUI;
class ResultUI :public IGameObject
{
public:
	//���U���gUI�̃X�e�[�g
	enum enResultUIState
	{
		enResultUIState_Fade,		//�t�F�[�h���
		enResultUIState_Score,		//�X�R�A�\�����
		enResultUIState_Evaluation,	//�]�����
		enResultUIState_FadeOut,	//�t�F�[�h�A�E�g���
	};

	//���U���gUI�̍��W�X�e�[�g
	enum ResultSetPos
	{
		Pos_OutSide,	//��ʊO
		Pos_InSide,		//��ʓ�
		Pos_Slide,		//�X���C�h��
	};

	ResultUI();
	~ResultUI();
	bool Start();
	void Update();
	void ScoreAdded(int addScore);
	void NextResultPosState();
	void Render(RenderContext& rc);

	/// <summary>
	/// ���U���g�\�����I�����Ă��邩�̎擾
	/// </summary>
	/// <returns></returns>
	bool& GetIsResultEnd()
	{
		return m_isResultEnd;
	}

	

private:
	Game* m_game = nullptr;									//�Q�[��
	GameTimer* m_gameTimer = nullptr;						//�Q�[���^�C�}�[
	ResultUI* m_resultUI = nullptr;							//���U���gUI
	SoundSource* m_finishSE = nullptr;						//�t�B�j�b�V�����̌��ʉ�
	enResultUIState m_resultUIState = enResultUIState_Fade;	//���U���gUI�̃X�e�[�g
	ResultSetPos m_resultSetPosState = Pos_OutSide;			//���U���gUI�̍��W�X�e�[�g
	
	SpriteRender m_finishSprite;		//�t�B�j�b�V�����̃X�v���C�g
	SpriteRender m_resultUI_Sprite;		//���U���gUI�̃X�v���C�g
	SpriteRender m_clearSprite;			//�Q�[���N���A�̃X�v���C�g
	SpriteRender m_failedSprite;		//�Q�[�����s�̃X�v���C�g
	SpriteRender m_rankC_Sprite;		//�����NC�̃X�v���C�g
	SpriteRender m_rankB_Sprite;		//�����NB�̃X�v���C�g
	SpriteRender m_rankA_Sprite;		//�����NA�̃X�v���C�g
	SpriteRender m_rankS_Sprite;		//�����NS�̃X�v���C�g

	FontRender	m_nowScoreRender;		//���݂̃X�R�A�\���p�t�H���g
	
	float	   m_elapsedTime = 0.0f;	//�o�ߎ���

	Vector3		m_position = Vector3::Zero;	//���W
	Vector3		m_scale = Vector3::One;		//�g�嗦
	Vector3		m_nowScorePos = Vector3(400.0f, 730.0f, 0.0f);//���݂̃X�R�A�\���̍��W
	bool		m_isResultEnd = false;		//���U���g�\�����I�����Ă��邩
	bool		m_isFinishSEPlayed = false;	//�t�B�j�b�V�����̌��ʉ����Đ����Ă邩
	int			m_nowScore = 0.0f;			//���݂̃X�R�A

};


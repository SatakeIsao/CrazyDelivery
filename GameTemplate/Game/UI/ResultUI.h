#pragma once

class GameTimer;
class Game;
class InventoryUI;
class StartButtonUI;
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
	enum ResultSetPosState
	{
		Pos_OutSide,	//��ʊO
		Pos_InSide,		//��ʓ�
		Pos_Slide,		//�X���C�h��
	};

	//�t�B�j�b�V���X�v���C�g�̊g�嗦�X�e�[�g
	enum FinishScaleState
	{
		Scale_Double,	//�{�̊g�嗦
		Scale_Small,	//�k����
		Scale_Medium,	//���{�̊g�嗦
		Scale_None,		//�ύX�Ȃ�
	};

	ResultUI();
	~ResultUI();
	bool Start();
	void Update();

	void ScoreAdded(const int& addScore);
	int EarnedScoreDisplay();
	void NextResultPosState();
	void NextFinishScaleState();
	void ScaleDouble();
	void ScaleMedium();
	void ScaleSmall();
	void Render(RenderContext& rc);

	/// <summary>
	/// ���U���g�\�����I�����Ă��邩�̎擾
	/// </summary>
	bool GetIsResultEnd()
	{
		return m_isResultEnd;
	}
	/// <summary>
	/// �t�B�j�b�V���\���ς݂�
	/// </summary>
	bool GetFinishDisplayed()
	{
		return m_isFinishDisplayed;
	}
	/// <summary>
	/// �����NC�̎擾
	/// </summary>
	bool GetRankC();
	
private:
	//Game*			m_game = nullptr;						//�Q�[��
	GameTimer*		m_gameTimer = nullptr;					//�Q�[���^�C�}�[
	ResultUI*		m_resultUI = nullptr;					//���U���gUI
	SoundSource*	m_finishSE = nullptr;					//�t�B�j�b�V�����̌��ʉ�
	StartButtonUI*  m_startButtonUI = nullptr;				//�X�^�[�g�{�^��UI
	enResultUIState m_resultUIState = enResultUIState_Fade;	//���U���gUI�̃X�e�[�g
	ResultSetPosState	m_resultSetPosState = Pos_OutSide;	//���U���gUI�̍��W�X�e�[�g
	FinishScaleState m_finishScaleState = Scale_Double;		//�t�B�j�b�V���X�v���C�g�̊g�嗦�X�e�[�g

	SpriteRender	m_finishSprite;							//�t�B�j�b�V�����̃X�v���C�g
	SpriteRender	m_resultUI_Sprite;						//���U���gUI�̃X�v���C�g
	SpriteRender	m_clearSprite;							//�Q�[���N���A�̃X�v���C�g
	SpriteRender	m_failedSprite;							//�Q�[�����s�̃X�v���C�g
	SpriteRender	m_rankC_Sprite;							//�����NC�̃X�v���C�g
	SpriteRender	m_rankB_Sprite;							//�����NB�̃X�v���C�g
	SpriteRender	m_rankA_Sprite;							//�����NA�̃X�v���C�g
	SpriteRender	m_rankS_Sprite;							//�����NS�̃X�v���C�g
	FontRender		m_nowScoreRender;						//���݂̃X�R�A�\���p�t�H���g
	
	Vector3			m_position = Vector3::Zero;				//���W
	Vector3			m_nowScorePos = Vector3(500.0f, 730.0f, 0.0f);//���݂̃X�R�A�\���̍��W

	float			m_scale = 1.0f;							//�g�嗦
	float			m_finishScale = 10.0f;					//�t�B�j�b�V���̊g�嗦
	float			m_elapsedTime = 0.0f;					//�o�ߎ���
	float			m_displayScore = 0.0f;					//��ԗp�̕\���X�R�A
	float			m_displayTotalScore = 0.0f;				//��ԗp�̍��v�X�R�A
	int				m_nowScore = 1.0f;						//���ۂ̌��݂̃X�R�A
	int				m_saveNowScore = 0.0f;					//�O��̃X�R�A
	bool			m_isResultEnd = false;					//���U���g�\�����I�����Ă��邩
	bool			m_isFinishSEPlayed = false;				//�t�B�j�b�V�����̌��ʉ����Đ����Ă邩
	bool			m_isFinishDisplayed = false;			//�t�B�j�b�V���\���ς݂�
};


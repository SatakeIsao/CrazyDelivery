#pragma once

#include "SkyCube.h"
#include "Player.h"
#include "LevelRender.h"
#include "MakeEffect.h"
#include "GameSound.h"
#include "ResultUI.h"


class CustoemrMan;
class BackGround;
class GameCamera;
class GameTimer;
class InventoryUI;
class MapUI;
class StartButtonUI;
class ShopHamburger;
class ShopPizza;
class ShopSushi;
class CustomerMan_Hamburger;
class CustomerMan_Pizza;
class CustomerMan_Sushi;
class GameInformation;

class Game : public IGameObject
{
public:
	enum ScorePanelSetPos
	{
		POS_SCORE_OUTSIDE,
		POS_SCORE_INSIDE,
		POS_SCORE_SLIDE,
	};

	//�e�X�g�p�A�j���[�V�����N���b�v
	enum EnAnimationClip
	{
		enAnimClip_Idle,
		enAnimClip_Start,
		enAnimClip_Push,
		enAnimClip_Run,
		enAnimClip_Jump,
		enAnimClip_Drift,
		//enAnimClip_Angry,
		enAnimClip_Num
	};

	enum ScoreRank
	{
		enScoreS,
		enScoreA,
		enScoreB,
		enScoreC,
	};
	

	Game();
	~Game();
	bool Start();
	void PlayerMove();
	void Update();
	void UpdateScore();
	void Render(RenderContext& rc);
	void SetSkyCube();
	void FinishTimer();
	//void CalcAlpha();
	//void IncreaseTimer();
	//void FontSet();
	void DisplayTime();
	void NextScorePosState();
	//void ScoreAdded(int addScore);

	bool& GetIsFinish()
	{
		return m_isFinish;
	}
	int& GetNowScore()
	{
		return m_nowScore;
	}

	ScoreRank GetScoreRankState()
	{
		return m_scoreRankState;
	}

private:
	LevelRender m_levelRender;
	SkyCube* m_skyCube = nullptr;
	nsPlayer::Player* m_player = nullptr;
	CustomerMan* m_customerMan = nullptr;
	BackGround* m_backGround = nullptr;
	GameCamera* m_gameCamera = nullptr;
	GameTimer* m_gameTimer = nullptr;
	InventoryUI* m_inventoryUI = nullptr;
	MapUI* m_mapUI = nullptr;
	StartButtonUI* m_startButtonUI = nullptr;
	//ShopPizza*	   m_shopPizza = nullptr;
	//ShopSushi*	   m_shopSushi = nullptr;
	MakeEffect*	   m_makeEfe = nullptr;
	ResultUI* m_resultUI = nullptr;
	//CustomerMan_Hamburger* m_customerMan_Hamburger= nullptr;
	//CustomerMan_Pizza* m_customerMan_Pizza = nullptr;
	//CustomerMan_Sushi* m_customerMan_Sushi = nullptr;
	GameSound* m_gameSound = nullptr;
	GameInformation* m_gameInfo = nullptr;
	//SoundSource* m_gameBGM = nullptr;

	ModelRender m_shadowTest;						 //�e�X�g�p���f��
	AnimationClip m_playerAnimClips[enAnimClip_Num]; //�e�X�g�p�v���C���[�̃A�j���[�V�����N���b�v
	//FontRender m_testFontRen;						 //�e�X�g�\���p���b�Z�[�W
	SpriteRender m_testSprite;						 //�e�X�g�\���p�X�v���C�g
	//SpriteRender m_finishSprite;

	Vector3 m_testSpritePos = Vector3(1050.0f, 550.0f, 0.0f);

	ScorePanelSetPos m_setScorePosState = POS_SCORE_OUTSIDE;
	ScoreRank m_scoreRankState = enScoreC;

	float m_second = 0.0f;							 //�b��
	int m_minute = 3.0f;							 //����
	Vector3 m_pointPosition = Vector3::Zero;
	ModelRender m_testModel;
	Vector3 m_testModelPos;
	FontRender	m_nowScoreRender;
	FontRender  m_scoreRender;
	int		m_nowScore = 0.0f;
	Texture m_coolTimeTexture;
	
	bool	m_isFinish = false;
	bool	m_isFinishStarted = false;

	float m_finishStartTime = 0.0f;


	struct CoolTimeSpriteData
	{
	private:
		/// <summary>
		/// ���C�v����
		/// </summary>
		float m_wipeRatio = 6.3f; //6.3f=�S�̂̃A���t�@�l
		/// <summary>
		/// �A���t�@�l
		/// </summary>
		float m_alpha = 0.7f;
		/// <summary>
		/// ���C�v�T�C�Y
		/// </summary>
		float m_wipeSize = 0;
	public:
		/// <summary>
		/// �����̏�����
		/// </summary>
		/// <param name="value"></param>
		void SetDegree(const float value)
		{
			m_wipeSize = value;
		}
		/// <summary>
		/// �����̉��Z
		/// </summary>
		/// <param name="addValue"></param>
		void AddDegree(const float addValue)
		{
			m_wipeSize += addValue;
		}
		/// <summary>
		/// �����̎擾
		/// </summary>
		/// <returns></returns>
		const float& GetDegree() const
		{
			return m_wipeSize;
		}
		/// <summary>
		/// ��������
		/// </summary>
		/// <param name="value"></param>
		void SetDirection(const float& value)
		{
			m_wipeRatio = value;
		}
		/// <summary>
		/// �A���t�@�l�̉��Z
		/// </summary>
		/// <param name="addValue"></param>
		void AddDirection(const float addValue)
		{
			m_wipeRatio += addValue;
		}
		/// <summary>
		/// �����擾
		/// </summary>
		/// <returns></returns>
		const float& GetDirection() const
		{
			return m_wipeRatio;
		}
		/// <summary>
		/// �A���t�@�l�̏�����
		/// </summary>
		/// <param name="value"></param>
		void SetAlpha(const float value)
		{
			m_alpha = value;
		}
		/// <summary>
		/// �A���t�@�l�̉��Z
		/// </summary>
		/// <param name="addValue"></param>
		void AddAlpha(const float addValue)
		{
			m_alpha += addValue;
		}
		/// <summary>
		/// �A���t�@�l�̎擾
		/// </summary>
		/// <returns></returns>
		const float& GetAlpha() const
		{
			return m_alpha;
		}

	};
	CoolTimeSpriteData m_coolTimeSpriteData;
	SpriteRender m_coolSprite;
};


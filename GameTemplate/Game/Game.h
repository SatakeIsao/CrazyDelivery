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

	//テスト用アニメーションクリップ
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

	ModelRender m_shadowTest;						 //テスト用モデル
	AnimationClip m_playerAnimClips[enAnimClip_Num]; //テスト用プレイヤーのアニメーションクリップ
	//FontRender m_testFontRen;						 //テスト表示用メッセージ
	SpriteRender m_testSprite;						 //テスト表示用スプライト
	//SpriteRender m_finishSprite;

	Vector3 m_testSpritePos = Vector3(1050.0f, 550.0f, 0.0f);

	ScorePanelSetPos m_setScorePosState = POS_SCORE_OUTSIDE;
	ScoreRank m_scoreRankState = enScoreC;

	float m_second = 0.0f;							 //秒数
	int m_minute = 3.0f;							 //分数
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
		/// ワイプ方向
		/// </summary>
		float m_wipeRatio = 6.3f; //6.3f=全体のアルファ値
		/// <summary>
		/// アルファ値
		/// </summary>
		float m_alpha = 0.7f;
		/// <summary>
		/// ワイプサイズ
		/// </summary>
		float m_wipeSize = 0;
	public:
		/// <summary>
		/// 割合の初期化
		/// </summary>
		/// <param name="value"></param>
		void SetDegree(const float value)
		{
			m_wipeSize = value;
		}
		/// <summary>
		/// 割合の加算
		/// </summary>
		/// <param name="addValue"></param>
		void AddDegree(const float addValue)
		{
			m_wipeSize += addValue;
		}
		/// <summary>
		/// 割合の取得
		/// </summary>
		/// <returns></returns>
		const float& GetDegree() const
		{
			return m_wipeSize;
		}
		/// <summary>
		/// 方向決定
		/// </summary>
		/// <param name="value"></param>
		void SetDirection(const float& value)
		{
			m_wipeRatio = value;
		}
		/// <summary>
		/// アルファ値の加算
		/// </summary>
		/// <param name="addValue"></param>
		void AddDirection(const float addValue)
		{
			m_wipeRatio += addValue;
		}
		/// <summary>
		/// 方向取得
		/// </summary>
		/// <returns></returns>
		const float& GetDirection() const
		{
			return m_wipeRatio;
		}
		/// <summary>
		/// アルファ値の初期化
		/// </summary>
		/// <param name="value"></param>
		void SetAlpha(const float value)
		{
			m_alpha = value;
		}
		/// <summary>
		/// アルファ値の加算
		/// </summary>
		/// <param name="addValue"></param>
		void AddAlpha(const float addValue)
		{
			m_alpha += addValue;
		}
		/// <summary>
		/// アルファ値の取得
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


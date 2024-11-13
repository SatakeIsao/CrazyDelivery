#pragma once

#include "SkyCube.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
//class Player;
//class BackGround;
//class GameCamera;
class Game : public IGameObject
{
public:
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

	Game();
	~Game();
	bool Start();
	void PlayerMove();
	void Update();
	void Render(RenderContext& rc);
	void SetSkyCube();
	//テスト用座標
	Vector3 m_modelTestPos = Vector3::Zero;

	Vector3 m_pointLightTestPos = { 0.0f,20.0f,0.0f };

	Vector3 m_spotLightTestPos = { 0.0f,20.0f,0.0f };
	
	Vector3 m_spotLightTestDirection = { 1.0,-1.0f,1.0f };
	//テストカメラ
	//GameCamera* m_testCamera = nullptr;

	//PointLight m_testPointLight;
private:
	SkyCube* m_skyCube = nullptr;
	//ModelRender m_modelPlayer;
	nsPlayer::Player* m_player = nullptr;
	BackGround* m_backGround = nullptr;
	GameCamera* m_gameCamera = nullptr;

	ModelRender m_shadowTest;		//テスト用モデル
	AnimationClip m_playerAnimClips[enAnimClip_Num]; //テスト用プレイヤーのアニメーションクリップ
	FontRender m_testFont;			//テスト表示用メッセージ
	SpriteRender m_testSprite;			//テスト表示用スプライト
};


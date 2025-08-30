#pragma once
#include "SpringCamera.h"

namespace nsPlayer { class Player; }
class Player;
class ResultUI;
class Fade;
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	/// <summary>
	/// カメラの移動が完了したか
	/// </summary>
	bool GetIsCameraMoveFinished() { return m_isCameraMoveFinished; }

	void ResetForCameraMove();
private:
	nsPlayer::Player*		m_player = nullptr;						//プレイヤー
	ResultUI*				m_resultUI = nullptr;					//リザルトUI
	Fade*					m_fade = nullptr;						//フェード
	SpringCamera			m_springCamera;							//ばねカメラ

	Vector3					m_toCameraPos;							//注視点から視点に向かうベクトル
	Vector3					m_offsetPos = { 0.0f, 70.0f, -130.0f }; //注視点から視点に向かうベクトルの初期値
	Vector3					m_fixedCameraPos;						//パス移動中のカメラの固定位置
	Vector3					m_fixedCameraTarget;					//パス移動中のカメラの固定注視点
	Vector3					m_fixedCameraOffset;					// パス移動時のカメラの相対位置
	Vector3					m_fixedCameraFinish = { 0.0f,70.0f,130.0f };

	float					m_accelOffsetZ = -250.0f;				//加速時のカメラオフセット
	float					m_defaultOffsetZ = -130.0f;				//通常時のカメラオフセット
	float					m_finishOffsetX = 50.0f;				//リザルト表示時のカメラオフセット
	float					m_finishOffsetZ = 100.0f;				//リザルト表示時のカメラオフセット
	float					m_timer = 0.0f;

	bool					m_isCameraFixed = false;				//パス移動中にカメラを固定するフラグ
	bool 					m_isCameraMoveFinished = false;			//カメラの移動が完了したか
};


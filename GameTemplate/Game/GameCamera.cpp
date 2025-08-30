#include "stdafx.h"
#include "GameCamera.h"
#include "Player/Player.h"
#include "UI/ResultUI.h"
#include "Fade.h"
#include "GameEvents.h"

GameCamera::GameCamera()
{
}

GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	//注視点から視点までのベクトルを設定
	m_toCameraPos.Set(0.0f, 70.0f, -200.0f);
	//プレイヤーのインスタンスを探す
	m_player = FindGO<nsPlayer::Player>("player");
	//リザルトUIのインスタンスを探す
	m_resultUI = FindGO<ResultUI>("resultui");

	//フェードのインスタンスを探す
	//m_fade = FindGO<Fade>("fade");
	//カメラのニアクリップとファークリップを設定
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(80000.0f);

	//ばねカメラの初期化
	m_springCamera.Init(
		*g_camera3D,	//ばねカメラの処理を行うカメラを指定する
		5000.0f,		//カメラの移動速度の最大値
		true,			//カメラと地形とのあたり判定を取るかどうかのフラグ。trueだとあたり判定を行う
		5.0f			//カメラに設定される球体コリジョンの半径。第3引数がtrueの時に有効になる
	);

	return true;
}

void GameCamera::Update()
{
	// プレイヤーの位置と回転を取得
	Vector3 target = m_player->GetPostion();
	Quaternion playerRotation = m_player->GetRotation();
	if (m_resultUI->GetFinishDisplayed())
	{
		m_timer += g_gameTime->GetFrameDeltaTime();
	}else
	{
		m_timer = 0.0f;
	}

	
	if (m_player->IsPathMoving())
	{
		// パス移動中はカメラの位置をプレイヤーの相対位置に固定するが、追従する
		if (!m_isCameraFixed)
		{
			// カメラの相対位置を記録
			m_fixedCameraOffset = g_camera3D->GetPosition() - target;
			m_isCameraFixed = true;
		}

		// プレイヤーの位置が動いたらカメラもその分動かす
		Vector3 cameraPosition = target + m_fixedCameraOffset;
		Vector3 cameraTarget = target + Vector3(0.0f, 70.0f, 0.0f); // 注視点はプレイヤーの少し上

		m_springCamera.SetPosition(cameraPosition);
		m_springCamera.SetTarget(cameraTarget);
	}
	//TODO：ここ変更
	//フェードが始まってからに変更
	else if (m_timer >= 3.0f)
	{
		m_offsetPos.x = Math::Lerp(0.5f, m_offsetPos.x, m_finishOffsetX);
		m_offsetPos.z = Math::Lerp(0.5f, m_offsetPos.z, m_finishOffsetZ);

		// プレイヤーの位置が動いたらカメラもその分動かす
		Vector3 cameraPosition = target + m_offsetPos;
		Vector3 cameraTarget = target + Vector3(-120.0f, 70.0f, 0.0f); // 注視点はプレイヤーの少し上

		m_springCamera.SetPosition(cameraPosition);
		m_springCamera.SetTarget(cameraTarget);

		m_isCameraMoveFinished = true; // カメラの移動が完了
	}
	else
	{
		//EventManager::GetInstance().Subscribe(GameEvents::GameFinished, [&]() {
		//this->ResetForCameraMove();
		//});
		
		// 通常時はプレイヤーの背後を追従
		m_isCameraFixed = false; // 固定解除

		//プレイヤーのスピード状態を取得
		float maxSpeedPer = 1.0f;
		//プレイヤーの速度を取得
		float velocity = m_player->GetVelocity().Length();
		//プレイヤーの最大速度を取得
		float maxSpeed = m_player->GetStatus().GetSpeedMax() * maxSpeedPer;
		//速度を最大速度で割る
		velocity = min((velocity / maxSpeed), 1.0f);

		//加速時はカメラオフセットを加速用オフセットに近づける
		m_offsetPos.z = Math::Lerp(velocity, m_defaultOffsetZ, m_accelOffsetZ);

		Vector3 currentOffset = m_offsetPos;;// 通常時のカメラの位置
		playerRotation.Apply(currentOffset); // プレイヤーの回転を適用

		Vector3 cameraPosition = target + currentOffset;
		Vector3 cameraTarget = target;
		cameraTarget.y += 70.0f;

		m_springCamera.SetPosition(cameraPosition);
		m_springCamera.SetTarget(cameraTarget);
	}

	m_springCamera.Update();
}

void GameCamera::ResetForCameraMove()
{
	// プレイヤーの位置と回転を取得
	Vector3 target = m_player->GetPostion();
	Quaternion playerRotation = m_player->GetRotation();

	Vector3 currentOffset = m_offsetPos;;// 通常時のカメラの位置
	playerRotation.Apply(currentOffset); // プレイヤーの回転を適用

	Vector3 cameraPosition = target + currentOffset;
	Vector3 cameraTarget = target;
	cameraTarget.y += 70.0f;

	m_springCamera.SetPosition(cameraPosition);
	m_springCamera.SetTarget(cameraTarget);

	m_springCamera.Update();
}

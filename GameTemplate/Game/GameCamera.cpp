#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

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
	//m_toCameraPos *= 0.5f;
	//プレイヤーのインスタンスを探す
	m_player = FindGO<nsPlayer::Player>("player");
	//カメラのニアクリップとファークリップを設定
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(80000.0f);

	return true;
}

void GameCamera::Update()
{
	// プレイヤーの位置を取得
	Vector3 target = m_player->GetPostion(); // プレイヤーの現在位置

	// 右スティックの入力でカメラを左右に回転させる
	m_stickPowerX = g_pad[0]->GetRStickXF(); // X軸のスティック入力

	// プレイヤーの周りをY軸回転でカメラを移動
	Quaternion yRotation;
	yRotation.SetRotationDeg(Vector3::AxisY, 2.4f * m_stickPowerX); // Y軸周りに回転
	yRotation.Apply(m_toCameraPos); // カメラのオフセットに回転を適用

	// カメラ位置をプレイヤーの後ろに設定（プレイヤー位置 + カメラオフセット）
	Vector3 cameraPosition = target + m_toCameraPos;

	// プレイヤーの頭上を注視点に設定
	Vector3 cameraTarget = target;
	cameraTarget.y += 70.0f;  // プレイヤーの少し上を注視点に

	// カメラの位置と注視点をメインカメラに設定
	g_camera3D->SetPosition(cameraPosition);
	g_camera3D->SetTarget(cameraTarget);

	//プレイヤーの向きをカメラが向いている方向にする
	//カメラの正面ベクトルを取得する
	Vector3 forward = g_camera3D->GetForward();
	//プレイヤーが斜めを向かないようにyをゼロにする
	forward.y = 0.0f;
	//正規化
	forward.Normalize();
	//用意した情報でプレイヤーのローテーションを用意する
	Quaternion playerRotation;
	//正面ベクトル(0,0,1)からカメラの正面ベクトルに向かう回転を作る
	playerRotation.SetRotation(Vector3::AxisZ, forward);
	//プレイヤーのローテーションに適用する
	m_player->SetRotation(playerRotation);

	// カメラを更新
	g_camera3D->Update();
}

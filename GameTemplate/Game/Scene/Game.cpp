#include "stdafx.h"
#include "Game.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "UI/GameTimer.h"
#include "UI/InventoryUI.h"
#include "UI/StartButtonUI.h"
#include "UI/MapUI.h"
#include "UI/UIAnimationManager.h"
#include "UI/HasFoodManager.h"
#include "Shop/ShopHamburger.h"
#include "Shop/ShopPizza.h"
#include "Shop/ShopSushi.h"
#include "Customer/CustomerMan.h"
#include "Customer/CustomerManHamburger.h"
#include "Customer/CustomerManPizza.h"
#include "Customer/CustomerManSushi.h"
#include "GameInformation.h"
#include "Fade.h"
#include "Path.h"
#include "PathStorage.h"
#include "GameTitle.h"
#include "Player/Player.h"
#include "ParameterManager.h"
#include "FocusLine.h"
#include "SkyCube.h"

namespace
{
	const float		BLINK_INTERVAL = 0.1f;	//点滅間隔
}

Game::Game()
{
}

Game::~Game()
{
	//ハンバーガーショップの削除
	std::vector<ShopHamburger*>  shopHamburger = FindGOs<ShopHamburger>("shophamburger");
	for (auto shHamGo : shopHamburger) {
		DeleteGO(shHamGo);
	}
	//ピザショップの削除
	std::vector<ShopPizza*> shopPizza = FindGOs<ShopPizza>("shoppizza");
	for (auto shPizGo : shopPizza) {
		DeleteGO(shPizGo);
	}
	//寿司店の削除
	std::vector<ShopSushi*> shopSushi = FindGOs<ShopSushi>("shopsushi");
	for (auto shSusGo : shopSushi){
		DeleteGO(shSusGo);
	}
	//お客さん（ハンバーガー）の削除
	std::vector<CustomerManHamburger*> customerManHam = FindGOs<CustomerManHamburger>("customerman_hamburger");
	for (auto csHamGo : customerManHam) {
		DeleteGO(csHamGo);
	}
	//お客さん（ピザ）の削除
	std::vector<CustomerManPizza*> customerManPiz = FindGOs<CustomerManPizza>("customerman_pizza");
	for (auto csPizGo : customerManPiz) {
		DeleteGO(csPizGo);
	}
	//お客さん（寿司）の削除
	std::vector<CustomerManSushi*> customerManSus = FindGOs<CustomerManSushi>("customerman_sushi");
	for (auto csSusGo : customerManSus) {
		DeleteGO(csSusGo);
	}

	//プレイヤーの削除
	DeleteGO(m_player);
	//エフェクトの削除
	DeleteGO(m_makeEfe);
	//背景の削除
	DeleteGO(m_backGround);
	//ゲームカメラの削除
	DeleteGO(m_gameCamera);
	//ゲームタイマーの削除
	DeleteGO(m_gameTimer);
	//インベントリーUIの削除
	DeleteGO(m_inventoryUI);
	//マップUIの削除
	DeleteGO(m_mapUI);
	//スタートボタンUIの削除
	DeleteGO(m_startButtonUI);
	//リザルトUIの削除
	DeleteGO(m_resultUI);
	//食べ物を所持しているかの管理クラスの削除
	DeleteGO(m_hasFoodManager);
	//ゲームインフォメーションの削除
	DeleteGO(m_gameInfo);
	//パスストレージクラスのインスタンスを削除
	m_pathSt->DeleteInstance();
	//集中線のオブジェクトを削除
	DeleteGO(m_focusLine);
	//スカイキューブの削除
	DeleteGO(m_skyCube);
	//フェードの削除
	//DeleteGO(m_fade);
}

bool Game::Start()
{
	//パスストレージのインスタンスを作成
	if (m_pathSt == nullptr){
		m_pathSt = PathStorage::CreateInstance();
	}

	//エフェクトの初期化
	m_makeEfe = NewGO<MakeEffect>(0, "makeeffect");
	//レベルの初期化
	m_levelRender.Init("Assets/ModelData/StageData/bg.tkl",
		[&](LevelObjectData_Render& objData){
		if (objData.ForwardMatchName(L"Path_") == true){
			// パスデータが見つかった。
			// パス番号を取得する
			const int PathNoStartPos = 6;	// パス番号が始まる文字列中の位置
			const int Digits = 2;			// 桁数			
			char pathNoString[Digits + 1];	// null文字を追加するために＋１

			pathNoString[0] = objData.name[PathNoStartPos];
			pathNoString[1] = objData.name[PathNoStartPos + 1];
			pathNoString[2] = '\0';
			int pathNo = atoi(pathNoString);

			//ポイント番号を取得
			const int PointNoStartPos = 9;			// ポイント番号が始まる文字列中の位置
			const int PointDigits = 5;				// 桁数
			char pointNoString[PointDigits + 1];	// null文字を追加するために＋１

			pointNoString[0] = objData.name[PointNoStartPos];
			pointNoString[1] = objData.name[PointNoStartPos + 1];
			pointNoString[2] = objData.name[PointNoStartPos + 1];
			pointNoString[3] = objData.name[PointNoStartPos + 1];
			pointNoString[4] = objData.name[PointNoStartPos + 1];
			pointNoString[5] = '\0';
			int pointNo = atoi(pointNoString);

			//Pathクラスのインスタンス
			Path* editPath = nullptr;	
			//PathStorageにpathNoの*パスが保存されているか調べる
			//保存されていたら
			if (m_pathSt->Exist(pathNo) == true){
				//パスストレージから編集するPathクラスのインスタンスを取得
				editPath = m_pathSt->GetPath(pathNo);
			}
			//保存されていなければ
			else {
				//新しいPathクラスのインスタンスを作成
				editPath = new Path;
				//ストレージに追加
				m_pathSt->AddPath(pathNo, *editPath);
			}
			//パスにポイントの座標を追加
			Vector3 pointPos = objData.position;
			
			editPath->AddPointPos(pointNo, pointPos);
		}
		//ハンバーガーショップの生成
		if (objData.ForwardMatchName(L"DummyHamburger") == true){
			ShopHamburger* shopHamburger = NewGO<ShopHamburger>(0, "shophamburger");
			shopHamburger->SetPosition(objData.position);
			shopHamburger->SetRotation(objData.rotation);
			shopHamburger->SetScale(objData.scale);
			return true;
		}
		//ピザショップの生成
		else if (objData.ForwardMatchName(L"DummyPizza") == true){
			ShopPizza* shopPizza = NewGO<ShopPizza>(0, "shoppizza");
			shopPizza->SetPosition(objData.position);
			shopPizza->SetRotation(objData.rotation);
			shopPizza->SetScale(objData.scale);
			return true;
		}
		//寿司店の生成
		else if (objData.ForwardMatchName(L"DummySushi") == true){
			ShopSushi* shopSushi = NewGO<ShopSushi>(0, "shopsushi");
			shopSushi->SetPosition(objData.position);
			shopSushi->SetRotation(objData.rotation);
			shopSushi->SetScale(objData.scale);
			return true;
		}
		//ハンバーガー待ちのお客さん
		else if (objData.ForwardMatchName(L"DummyManHamburger") == true){
			CustomerManHamburger* customerHamburger = NewGO<CustomerManHamburger>(0, "customerman_hamburger");
			customerHamburger->SetPosition(objData.position);
			customerHamburger->SetRotation(objData.rotation);
			customerHamburger->SetGamePointer(this);
			return true;
		}
		//ピザ待ちのお客さん
		else if (objData.ForwardMatchName(L"DummyManPizza") == true){
			CustomerManPizza* customerPizza = NewGO<CustomerManPizza>(0, "customerman_pizza");
			customerPizza->SetPosition(objData.position);
			customerPizza->SetRotation(objData.rotation);
			customerPizza->SetGamePointer(this);
			return true;
		}
		//寿司待ちのお客さん
		else if (objData.ForwardMatchName(L"DummyManSushi") == true){
			CustomerManSushi* customerSushi = NewGO<CustomerManSushi>(0, "customerman_sushi");
			customerSushi->SetPosition(objData.position);
			customerSushi->SetRotation(objData.rotation);
			customerSushi->SetGamePointer(this);
			return true;
		}
		return true;
	});

	// パスのポイントの収集が終わったのでパスを構築する
	int pathCount = PathStorage::GetPathStorage()->GetPathCount();
	for (int i = 0; i < pathCount; i++) {
		//シングルトンクラスからパスを取得
		auto path = PathStorage::GetPathStorage()->GetPath(i);
		//収集されたポイントの情報からパスを構築する
		path->Build();
	}

	//プレイヤーのオブジェクトを作成
	m_player = NewGO<nsPlayer::Player>(0, "player");
	//集中線のオブジェクトを作成
	m_focusLine = NewGO<FocusLine>(0, "focusline");
	//背景のオブジェクトを作成
	m_backGround = NewGO<BackGround>(0, "background");
	//ゲームカメラのオブジェクトを作成
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
	//ゲームタイマーのオブジェクトを作成
	m_gameTimer = NewGO<GameTimer>(0, "gametimer");
	//インベントリーUIのオブジェクトを作成
	m_inventoryUI = NewGO<InventoryUI>(0, "inventoryui");
	//ミニマップUIのオブジェクトを作成
	m_mapUI = NewGO<MapUI>(0, "mapui");
	//スタート時のUIのオブジェクトを作成
	m_startButtonUI = NewGO<StartButtonUI>(0, "startbuttonui");
	//リザルトUIのオブジェクトを作成
	m_resultUI = NewGO<ResultUI>(0, "resultui");
	//食べ物を所持しているかの管理クラスのオブジェクトを作成
	m_hasFoodManager = NewGO<HasFoodManager>(0, "hasfoodmanager");
	//フェードのオブジェクトを作成
	//m_fade = NewGO<Fade>(0, "fade");
	//スカイキューブの作成
	SetSkyCube();
	
	//スコアパネルスプライトの初期化
	m_scorePanelSprite.Init("Assets/Sprite/InGame/ScorePanel.DDS", 500.0f, 500.0f);
	m_scorePanelSprite.SetPosition(m_scorePanelSpritePos);
	m_scorePanelSprite.Update();

	//操作バネルスプライトの初期化
	m_optionPanelSprite.Init("Assets/Sprite/InGame/OperationManual.DDS", 1600.0f, 900.0f);
	m_optionPanelSprite.SetPosition({ 0.0f,0.0f,0.0f });
	m_optionPanelSprite.Update();

	//ゲームインフォメーションクラスの作成
	m_gameInfo = NewGO<GameInformation>(0, "gameinformation");

	//PathStorage からパスを取得して Playerに設定
	Path* path = PathStorage::GetPathStorage()->GetPath(0);
	if (path){
		m_player->SetPath(path);
	}

	//パラメーターマネージャーの初期化
	ParameterManager::CreateInstance();

	// TODO: アニメーションマネージャーが作動するかテスト
	auto* animationManager = NewGO<UIAnimationManager>(0, "uianimationmanager");

	return true;
}

void Game::Update()
{
	m_blinkTimer += g_gameTime->GetFrameDeltaTime();
	//タイマー終了処理
	FinishTimer();
	//集中線の更新
	UpdateFocusLine();
	
	//リザルトが最大まで表示されたら、フェードイン
	

	////カメラの移動が終われば、フェードアウト
	//if (m_gameCamera->GetIsCameraMoveFinished())
	//{
	//	Fade* fade = NewGO<Fade>(0, "fade");
	//	//フェードインを開始
	//	fade->StartFadeOut();

	//	fade->SetOnFadeOutComplete([this]()
	//		{
	//			Fade* fade = FindGO<Fade>("fade");
	//			fade->StartFadeIn();
	//		}
	//	);
	//}

	//制限時間が0で、リザルトUIが終了したらタイトルに戻る処理
	if (m_gameTimer->GetIsTimerEnd()
		&& m_resultUI->GetIsResultEnd()
		&& g_pad[0]->IsTrigger(enButtonB)){
		Fade* fade = NewGO<Fade>(0, "fade");
		//フェードインを開始
		fade->StartFadeOut();
		//フェードアウト完了時の処理を設定
		fade->SetOnFadeOutComplete([this](){
			//フェードアウト完了後にタイトルを表示(既に存在していないかチェック)
			if (FindGO<GameTitle>("gameTitle") == nullptr){
				NewGO<GameTitle>(0, "gameTitle");
				//ゲームクラスを削除
				DeleteGO(this);
			}
		});
	}

	//スコアパネルのスライド処理
	if (g_pad[0]->IsTrigger(enButtonB)
		&& !m_gameTimer->GetIsTimerEnd()) {
		//スコアボードの位置を変更
		NextScorePosState();
		if (m_resultUI){
			//リザルトUIのスライド処理を開始
			m_resultUI->NextResultPosState();
		}
	}

	//スライドパネルのスライド処理
	if (m_setScorePosState == POS_SCORE_SLIDE) {
		if (m_scorePanelSpritePos.x > 550.0f) {
			m_scorePanelSpritePos.x -= 130.0f;
		}else {
			m_setScorePosState = POS_SCORE_INSIDE;
		}
	}

	//スコアパネルスプライトを更新
	m_scorePanelSprite.SetPosition(m_scorePanelSpritePos);
	m_scorePanelSprite.Update();
	
}

void Game::SetSkyCube()
{
	m_skyCube = NewGO<SkyCube>(0, "skycube");
	//明るさを設定
	m_skyCube->SetLuminance(1.0f);
	m_skyCube->SetScale(2000.0f);
	m_skyCube->SetPosition({ 1000.0f,500.0f,15500.0f });
	//スカイキューブの種類を設定
	m_skyCube->SetType((EnSkyCubeType)enSkyCubeType_Day);
}

void Game::FinishTimer()
{
	//タイマーが終了している場合
	if (m_gameTimer->GetIsTimerEnd()) {
		//終了処理開始していない場合
		if (m_isFinishStarted = false){
			//ゲームを終了処理開始
			m_isFinishStarted = true;
			//フィニッシュ開始時間を記録
			m_finishStartTime = g_gameTime->GetFrameDeltaTime();
		}
		//終了処理が開始されてから３秒経過した場合
		if (m_isFinishStarted
			&& g_gameTime->GetFrameDeltaTime() - m_finishStartTime >= 3.0f){
			//ゲームを終了状態に設定
			m_isFinish = true;
		}
	}
}

void Game::NextScorePosState()
{
	switch (m_setScorePosState) {
	case POS_SCORE_OUTSIDE:
		m_setScorePosState = POS_SCORE_SLIDE;
		break;
	case POS_SCORE_SLIDE:
		m_setScorePosState = POS_SCORE_INSIDE;
		break;
	default:
		break;
	}
}

void Game::UpdateFocusLine()
{
	if (m_player->DrawBoostEffect()){
		//加速中なら集中線を表示
		m_focusLine->SetScale(1.0);
	}else{
		// 最大速度の遊びとなるパーセント(一定値以上を集中線最大にしたいから)
		constexpr float maxSpeedPer = 0.8f;
		//集中線の最大拡大率
		constexpr float maxFocusLineScale = 20.0f;
		//集中線の最小拡大率
		constexpr float minFocusLineScale = 1.0f;

		//プレイヤーの速度を取得
		float velocity = m_player->GetVelocity().Length();
		//プレイヤーの最大速度を取得
		float maxSpeed = m_player->GetStatus().GetSpeedMax() * maxSpeedPer;
		//速度を最大速度で割る
		velocity = min((velocity / maxSpeed), 1.0f);
		//線形補間で拡大率を計算
		//float currentScale = Math::Lerp(velocity, maxFocusLineScale, minFocusLineScale);
		float currentScale = Math::Lerp(velocity, maxFocusLineScale, minFocusLineScale);
		//集中線の拡大率を設定
		m_focusLine->SetScale(currentScale);
	}
}

void Game::Render(RenderContext& rc)
{
	if (m_gameTimer->GetIsTimerEnd()){
		//タイマーが終了している場合、スコアパネルと操作パネルを描画しない
		return;
	}
	m_scorePanelSprite.Draw(rc);
	m_optionPanelSprite.Draw(rc);
}
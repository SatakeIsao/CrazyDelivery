#include "stdafx.h"
#include "ResultUI.h"
#include "GameTimer.h"
#include "InventoryUI.h"
#include "Scene/Game.h"
#include "GameSound.h"
#include "Fade.h"
#include "Scene/GameTitle.h"
#include "StartButtonUI.h"
#include "GameEvents.h"

namespace
{
	const Vector3 SCORE_POS(130.0f, 100.0f, 0.0f);	//スコアテキストの座標

	const float RESULT_SCORE_S = 4000.0f;			//スコア条件値：Sランク
	const float RESULT_SCORE_A = 3000.0f;			//スコア条件値：Aランク
	const float RESULT_SCORE_B = 2000.0f;			//スコア条件値：Bランク

	const float SLIDE_SPEED = 5.0f;					//スライドする速度
	const float SLIDE_TARGET_Y = 530.0f;			//スライド時の目標Y値

	const float FINISH_DISPLAY_TIME = 3.0f;			//フィニッシュの表示する時間

	const float SCORE_SCALE = 2.0f;					//スコアテキストの拡大率
	
}

ResultUI::ResultUI()
{
}

ResultUI::~ResultUI()
{
	DeleteGO(m_startButtonUI);
	OnDestroy();
}

bool ResultUI::Start()
{
	m_gameTimer = FindGO<GameTimer>("gametimer");
	m_resultUI = FindGO<ResultUI>("resultui");
	m_startButtonUI = NewGO<StartButtonUI>(0, "startbuttonui");

	//フィニッシュスプライトの初期化
	m_finishSprite.Init("Assets/Sprite/Result/ResultUI_Finish.dds", 1980.0f, 1020.0f);
	m_finishSprite.SetPosition(Vector3::Zero);
	m_finishSprite.SetScale(m_finishScale);
	m_finishSprite.Update();

	//リザルトUIの画像
	m_resultUI_Sprite.Init("Assets/Sprite/Result/ResultUI_Base.DDS",1440.0f,810.0f);
	m_resultUI_Sprite.SetPosition(m_position);
	m_resultUI_Sprite.SetScale(m_scale);
	m_resultUI_Sprite.Update();
	
	//CLEARの画像
	m_clearSprite.Init("Assets/Sprite/Result/ResultUI_Clear.DDS", 1440.0f, 810.0f);
	m_clearSprite.SetPosition(m_resultIconPos);
	m_clearSprite.SetScale(m_resultIconScale);
	m_clearSprite.Update();

	//FAILEDの画像
	m_failedSprite.Init("Assets/Sprite/Result/ResultUI_Failed.DDS", 1440.0f, 810.0f);
	m_failedSprite.SetPosition(m_failedIconPos);
	m_failedSprite.SetScale(0.4f);
	m_failedSprite.Update();

	//ランクSの画像
	m_rankS_Sprite.Init("Assets/Sprite/Result/ResultUI_RankS.DDS", 1440.0f, 810.0f);
	m_rankS_Sprite.SetPosition(m_rankIconPos);
	m_rankS_Sprite.SetScale(m_rankIconScale);
	m_rankS_Sprite.Update();

	//ランクAの画像
	m_rankA_Sprite.Init("Assets/Sprite/Result/ResultUI_RankA.DDS", 1440.0f, 810.0f);
	m_rankA_Sprite.SetPosition(m_rankIconPos);
	m_rankA_Sprite.SetScale(m_rankIconScale);
	m_rankA_Sprite.Update();

	//ランクBの画像
	m_rankB_Sprite.Init("Assets/Sprite/Result/ResultUI_RankB.DDS", 1440.0f, 810.0f);
	m_rankB_Sprite.SetPosition(m_rankIconPos);
	m_rankB_Sprite.SetScale(m_rankIconScale);
	m_rankB_Sprite.Update();

	//ランクCの画像
	m_rankC_Sprite.Init("Assets/Sprite/Result/ResultUI_RankC.DDS", 1440.0f, 810.0f);
	m_rankC_Sprite.SetPosition(m_rankIconPos);
	m_rankC_Sprite.SetScale(m_rankIconScale);
	m_rankC_Sprite.Update();
	
	//現在のスコア表示の初期化
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"$ %05d", m_nowScore);
	m_nowScoreRender.SetText(wcsbuf);
	m_nowScoreRender.SetPosition(m_nowScorePos);
	m_nowScoreRender.SetScale(SCORE_SCALE);
	m_nowScoreRender.SetColor({ 1.0f,1.0f,1.0f,1.0f });
	
	//初期スケール値と初期
	m_rankIconScale = 0.5f;
	m_rankIconScaleState = RankScale_Small;
	m_resultIconScale = 0.5f;
	m_rewardIconScaleState = RewardScale_Small;
	m_failedIconPos.x = 0.0f;
	m_failedIconPosState = Failed_Icon_Left;

	return true;
}

void ResultUI::Update()
{
	if (m_gameTimer->GetIsTimerEnd() == true) {
		UpdateGameLogic();
		if (m_elapsedTime >= FINISH_DISPLAY_TIME) {
			EventManager::GetInstance().Trigger(GameEvents::ResultUIReady);
		}
	}else {
		//ゲーム中のスコア表示更新
		UpdateScoreUpdate();
	}
	//どの状態でも実行される共通の更新処理
	//UpdateStartButtonUI();
	UpdatePositionSlide();
	UpdateFinishSpriteScale();
	//スプライトの更新
	m_finishSprite.SetScale(m_finishScale);
	m_finishSprite.Update();
}

void ResultUI::ScoreAdded(const int& addScore)
{
	//スコアの加算
	m_nowScore += addScore;
}

int ResultUI::EarnedScoreDisplay()
{
	m_saveNowScore = m_nowScore;
	return m_nowScore = Math::Lerp(0.01f, 0.0f, (float)m_nowScore);
}

void ResultUI::NextResultPosState()
{
	//現在の座標状態を次の状態に切り替え
	switch (m_resultSetPosState){
	case Pos_OutSide:
		m_resultSetPosState = Pos_Slide;
		break;
	case Pos_Slide:
		m_resultSetPosState = Pos_InSide;
		break;
	default:
		break;
	}
}

void ResultUI::NextFinishScaleState()
{
	//現在の拡大率の状態を次の状態に切り替え
	switch (m_finishScaleState){
	case Scale_Double:
		ScaleDouble();
		m_finishScaleState = Scale_Medium;
		break;
	case Scale_Small:
		ScaleSmall();
		if (m_finishScale <= 1.0f){
			m_finishScale = 1.0f;
			//縮小完了
			m_finishScaleState = Scale_None;
		}
		break;
	case Scale_Medium:
		ScaleMedium();
		m_finishScaleState = Scale_None;
		break;
	case Scale_None:
	default:
		break;
	}
}

void ResultUI::NextRankIconScaleState()
{
	switch (m_rankIconScaleState) {
	case RankScale_Small:
		m_rankIconScaleState = RankScale_Large;
		break;
	case RankScale_Large:
		m_rankIconScaleState = RankScale_Default;
		break;
	case RankScale_Default:
		m_rankIconScaleState = RankScale_Final;
		break;
	case RankScale_Final:
		break;
	}
}

void ResultUI::NextRewardIconScaleState()
{
	switch (m_rewardIconScaleState) {
	case RewardScale_Small:
		m_rewardIconScaleState = RewardScale_Large;
		break;
	case RewardScale_Large:
		m_rewardIconScaleState = RewardScale_Final;
		break;
	case RewardScale_Final:
		break;
	}
}

void ResultUI::NextFailedIconPosState()
{
	switch (m_failedIconPosState) {
	case Failed_Icon_Left:
		m_failedIconPosState = Failed_Icon_Right;
		break;
	case Failed_Icon_Right:
		m_failedIconPosState = Failed_Icon_Stop;
		break;
	case Failed_Icon_Stop:
		break;
	}
}

void ResultUI::ScaleDouble()
{
	//拡大率を10倍に設定
	m_finishSprite.SetScale(10.0f);
}

void ResultUI::ScaleMedium()
{
	//拡大率は等倍に設定
	m_finishSprite.SetScale(1.0f);
}

void ResultUI::ScaleSmall()
{
	//拡大率を徐々に減少させる
	m_finishScale -= 0.2f;
	if (m_finishScale < 1.0f){
		//最小値に固定
		m_finishScale = 1.0f;
	}

	m_finishSprite.SetScale(m_finishScale);
}

void ResultUI::Render(RenderContext& rc)
{
	if (m_gameTimer->GetIsTimerEnd() == true){
		//タイマーの累計時間を更新
		m_elapsedTime += g_gameTime->GetFrameDeltaTime();
		
		if (m_elapsedTime < FINISH_DISPLAY_TIME){
			if (!m_isFinishSEPlayed){
				//フィニッシュの音声再生
				m_finishSE = NewGO<SoundSource>(0);
				m_finishSE->Init(enSoundName_Finish);
				m_finishSE->SetVolume(1.0f);
				m_finishSE->Play(false);
				//フィニッシュの音声再生済みに設定
				m_isFinishSEPlayed = true;
			}
			m_finishSprite.Draw(rc);
		}else{
			if (g_pad[0]->IsTrigger(enButtonB))
			{
				m_elapsedTime += 5.0f;
			}
			//リザルトUIの描画
			m_resultUI_Sprite.Draw(rc);
			if (m_elapsedTime > 8.0f) {
				//ランクアイコンの描画
				UpdateRankIconScale();

				if (m_nowScore >= RESULT_SCORE_S) {
					m_rankS_Sprite.Draw(rc);
					//m_clearSprite.Draw(rc);
				}
				else if (m_nowScore >= RESULT_SCORE_A) {
					m_rankA_Sprite.Draw(rc);
					//m_clearSprite.Draw(rc);
				}
				else if (m_nowScore >= RESULT_SCORE_B) {
					m_rankB_Sprite.Draw(rc);
					//m_clearSprite.Draw(rc);
				}
				else {
					m_rankC_Sprite.Draw(rc);
					//m_failedSprite.Draw(rc);
				}
			}
			if (m_elapsedTime > 6.0f) {
				//リザルトアイコンの描画
				UpdateRewardIconScale();
				UpdateFailedIconPos();

				if (m_nowScore >= RESULT_SCORE_S) {
					//m_rankS_Sprite.Draw(rc);
					m_clearSprite.Draw(rc);
				}
				else if (m_nowScore >= RESULT_SCORE_A) {
					//m_rankA_Sprite.Draw(rc);
					m_clearSprite.Draw(rc);
				}
				else if (m_nowScore >= RESULT_SCORE_B) {
					//m_rankB_Sprite.Draw(rc);
					m_clearSprite.Draw(rc);
				}
				else {
					//m_rankC_Sprite.Draw(rc);
					m_failedSprite.Draw(rc);
				}
			}

			if (m_startButtonUI != nullptr){
				m_startButtonUI->Render(rc);
			}
			//スコアの描画
			m_nowScoreRender.SetScale(SCORE_SCALE);
			m_nowScoreRender.SetPosition(SCORE_POS);
			m_nowScoreRender.Draw(rc);
			m_isResultEnd = true;
		}
	}else{
		m_nowScoreRender.Draw(rc);
	}
}

bool ResultUI::GetRankC()
{
	return (m_nowScore < RESULT_SCORE_B);
}

void ResultUI::UpdateGameLogic()
{
	//ゲーム終了イベントを送る
	EventManager::GetInstance().Trigger(GameEvents::GameFinished);
	//リザルトUIが表示された後、Bボタン押されたらタイトルに戻る
	if (g_pad[0]->IsTrigger(enButtonB)
		&& m_gameTimer->GetIsTimerEnd()
		&& m_elapsedTime >= FINISH_DISPLAY_TIME
		&& m_isReturnToTitleStarted) {
		//Bボタンが押されたらSEを鳴らす
		SoundSource* buttonSE = NewGO<SoundSource>(0);
		buttonSE->Init(enSoundName_Button);
		buttonSE->SetVolume(0.5f);
		buttonSE->Play(false);
	
		//次の座標状態に変更
		NextResultPosState();
	
		Fade* fade = NewGO<Fade>(0, "fade");
		// フェードアウト開始
		fade->StartFadeOut();
		// フェードアウト完了時に `Game` クラスを生成
		fade->SetOnFadeOutComplete([this](){
			if (FindGO<GameTitle>("gameTitle") == nullptr){
				NewGO<GameTitle>(0, "gameTitle");
			}
			// タイトル画面の削除
			DeleteGO(this);
		});
	}
	//ゲームタイマーが終了していて
	//フィニッシュ表示がまだされていないなら
	if (m_gameTimer->GetIsTimerEnd()
		&& m_isFinishDisplayed == false) {
		m_finishScale = 10.0f;
		m_finishScaleState = Scale_Small;
		m_isFinishDisplayed = true;
	}
	//スコア表示の更新
	m_resultDelayTime += g_gameTime->GetFrameDeltaTime();
	if (m_resultDelayTime >= 3.0f
		&&g_pad[0]->IsTrigger(enButtonB))
	{
		// Bボタンが押されたら、即座に目標値に到達させる
		m_displayTotalScore = (float)m_nowScore - 1.0f;
	}
	
	else if (m_resultDelayTime >= 3.0f) {
		//表示スコアを実際のスコアに向かって補間
		m_displayTotalScore = Math::Lerp(0.025, m_displayTotalScore, (float)m_nowScore);
	}
	
	else {
		m_displayTotalScore = 0.0f;
	}
	//終了時のスコア表示
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"$%04d", (int)m_displayTotalScore);
	m_nowScoreRender.SetText(wcsbuf);
	m_nowScoreRender.SetPosition(m_nowScorePos);
}

void ResultUI::UpdateScoreUpdate()
{
	//表示スコアを実際のスコアに向かって補間
	const float interpolationRate = 0.1f;
	m_displayScore = Math::Lerp(interpolationRate, m_displayScore, (float)m_nowScore);
	//現在のスコア表示
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"$ %04d", (int)m_displayScore);
	m_nowScoreRender.SetText(wcsbuf);
	m_nowScoreRender.SetPosition(m_nowScorePos);
}
void ResultUI::UpdateStartButtonUI()
{
	if (m_startButtonUI != nullptr) {
		m_startButtonUI->Update();

		//ゲームタイマーが終了してリザルトUIが表示されたら、StartButtonUIをフェードインさせる
		if (m_elapsedTime >= FINISH_DISPLAY_TIME
			&& m_startButtonUI->GetStete() == StartButtonUI::enStartUIState_AlphaZero) {
			m_startButtonUI->SetState(StartButtonUI::enStartUIState_FadeIn);
		}
	}
}
void ResultUI::UpdatePositionSlide()
{
	if (m_resultSetPosState == Pos_Slide) {
		//Y軸を減少させて下にスライド
		if (m_nowScorePos.y > SLIDE_TARGET_Y) {
			//スライド速度
			m_nowScorePos.y -= SLIDE_SPEED;
		}else {
			//スライド完了
			m_resultSetPosState = Pos_InSide;
		}
	}	
}

void ResultUI::UpdateFinishSpriteScale()
{
	//拡大率を徐々に減少させる
	m_finishScale -= 0.2f;
	if (m_finishScale < 1.0f) {
		//最小値に固定
		m_finishScale = 1.0f;
	}
	m_finishSprite.SetScale(m_finishScale);
}

void ResultUI::UpdateRankIconScale()
{
	switch (m_rankIconScaleState) {
	case RankScale_Small:
		m_rankIconScale -= 0.02f;
		if (m_rankIconScale <= 0.1f) {
			m_rankIconScale = 0.1f;
			NextRankIconScaleState(); // 次のステートへ
		}
		break;
	case RankScale_Large:
		m_rankIconScale += 0.06f;
		if (m_rankIconScale >= 0.27f) {
			m_rankIconScale = 0.27f;
			NextRankIconScaleState(); // 次のステートへ
		}
		break;
	case RankScale_Final:
		// 最終状態では何もしない
		break;
	}
	// すべてのランクアイコンのスケールを更新
	m_rankA_Sprite.SetScale(m_rankIconScale);
	m_rankB_Sprite.SetScale(m_rankIconScale);
	m_rankC_Sprite.SetScale(m_rankIconScale);
	m_rankS_Sprite.SetScale(m_rankIconScale);
	m_rankA_Sprite.Update();
	m_rankB_Sprite.Update();
	m_rankC_Sprite.Update();
	m_rankS_Sprite.Update();
}

void ResultUI::UpdateRewardIconScale()
{
	switch (m_rewardIconScaleState) {
	case RankScale_Small:
		m_resultIconScale -= 0.02f;
		if (m_resultIconScale <= 0.1f) {
			m_resultIconScale = 0.1f;
			NextRewardIconScaleState(); // 次のステートへ
		}
		break;
	case RankScale_Large:
		m_resultIconScale += 0.06f;
		if (m_resultIconScale >= 0.4f) {
			m_resultIconScale = 0.4f;
			m_isReturnToTitleStarted = true;
			NextRewardIconScaleState(); // 次のステートへ
		}
		break;
	case RankScale_Final:
		// 最終状態では何もしない
		break;
	}
	m_clearSprite.SetScale(m_resultIconScale);
	m_clearSprite.Update();
	//m_failedSprite.SetScale(m_resultIconScale);
	//m_failedSprite.Update();
}

void ResultUI::UpdateFailedIconPos()
{
	switch (m_failedIconPosState) {
	case Failed_Icon_Left:
		//m_failedIconPos.x += 0.02f;
		//if (m_failedIconPos.x <= 0.1f) {
		//	m_failedIconPos.x = 0.1f;
			NextFailedIconPosState(); // 次のステートへ
		//}
		break;
	case Failed_Icon_Right:
		m_failedIconPos.x += 10.0f;
		if (m_failedIconPos.x >= 200.0f) {
			m_failedIconPos.x = 200.0f;
			NextFailedIconPosState(); // 次のステートへ
		}
		break;
	case Failed_Icon_Stop:
		// 最終状態では何もしない
		break;
	}

	m_failedSprite.SetPosition(m_failedIconPos);
	m_failedSprite.Update();
}

void ResultUI::RankIconScaleLarge()
{
	m_rankIconScale += 0.01f;
	if (m_rankIconScale > 0.27f) {
		m_rankIconScale = 0.27f;
	}
	m_rankA_Sprite.SetScale(m_rankIconScale);
	m_rankB_Sprite.SetScale(m_rankIconScale);
	m_rankC_Sprite.SetScale(m_rankIconScale);
	m_rankS_Sprite.SetScale(m_rankIconScale);
}

void ResultUI::RankIconScaleSmall()
{
	m_rankIconScale -= 0.01f;
	if (m_rankIconScale < 0.1f) {
		m_rankIconScale = 0.1f;
	}
	m_rankA_Sprite.SetScale(m_rankIconScale);
	m_rankB_Sprite.SetScale(m_rankIconScale);
	m_rankC_Sprite.SetScale(m_rankIconScale);
	m_rankS_Sprite.SetScale(m_rankIconScale);
}

void ResultUI::RankIconScaleMedium()
{
	m_rankA_Sprite.SetScale(0.27f);
	m_rankB_Sprite.SetScale(0.27f);
	m_rankC_Sprite.SetScale(0.27f);
	m_rankS_Sprite.SetScale(0.27f);
}
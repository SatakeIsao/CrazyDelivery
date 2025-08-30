/**
 * プレイヤーが使用するステートパターンの基底クラス
 */
#pragma once
#include "GameSound.h"
#include "Util/CRC32.h"
/** プレイヤーの各ステートパターンを識別するためのIDを定義するdefine */
#define playerState(name)\
public:\
	static constexpr uint32_t ID() { return Hash32(#name); }

static constexpr uint32_t INVALID_PLAYER_STATE_ID = 0xffffffff;

namespace nsPlayer
{
	class Player;

	class IState
	{
	protected:
		/// <summary>
		/// 指定された効果音を再生します。
		/// </summary>
		/// <param name="name">再生する効果音の名前</param>
		/// <param name="vol">効果音の音量（0.0～1.0の範囲）</param>
		/// <param name="isPlay">ループ再生するかどうか（trueでループ再生、falseで1回のみ）</param>
		void PlaySoundSE(const SoundName& name, const float vol, const bool isPlay);
	public:
		IState(Player* owner) : m_owner(owner) {}
		virtual ~IState() {}

		/// <summary>
		/// ステートが切り替わったときに呼ばれる関数
		/// NOTE: 何かしらの初期化をするときに使用します
		/// </summary>
		virtual void Enter() = 0;
		/// <summary>
		/// 毎フレーム呼ばれる更新関数
		/// </summary>
		virtual void Update() = 0;
		/// <summary>
		/// 状態が切り替わるときに呼ばれる関数
		/// NOTE: 何かしらの破棄などするときに使用します
		/// </summary>
		virtual void Exit() = 0;
		/// <summary>
		/// 状態の切り替わりをリクエストします
		/// NOTE: 切り替わりが発生したときは引数のIDが正常な値で返ります
		/// </summary>
		virtual bool RequestState(uint32_t& id) = 0;

	protected:
		friend class Player;
		Player* m_owner = nullptr;	// このステートパターンを使用する持ち主
	};
}
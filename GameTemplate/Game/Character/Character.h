/**
 * キャラクターとなるゲームオブジェクトの基底クラス
 * モデル・座標・拡縮・回転情報がある
 */
#pragma once
#include "GameSound.h"
#include "MakeEffect.h"

class Character : public IGameObject
{
public:
	Character() {}
	virtual ~Character() {}

	bool Start() override { return true; }
	void Update() override {}
	void Render(RenderContext& rc) override {}
	
public:
	/// <summary>
	/// 座標取得
	/// </summary>
	inline const Vector3& GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// 座標設定
	/// </summary>
	inline void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	/// <summary>
	/// 拡縮取得
	/// </summary>
	inline const Vector3& GetScale() const
	{
		return m_scale;
	}
	/// <summary>
	/// 拡縮設定
	/// </summary>
	inline void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// 回転取得
	/// </summary>
	inline const Quaternion& GetRotation() const
	{
		return m_rotation;
	}
	/// <summary>
	/// 拡縮設定
	/// </summary>
	inline void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	/// <summary>
	/// 指定された効果音を再生
	/// </summary>
	/// <param name="name"></param>
	/// <param name="vol"></param>
	/// <param name="isPlay"></param>
	void PlaySoundSE(const SoundName name, const float vol, const bool isPlay);
	/// <summary>
	/// 指定されたエフェクトを再生
	/// </summary>
	/// <param name="name"></param>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	/// <param name="scale"></param>
	void PlayEffect(const EffectName name, const Vector3& pos, const Quaternion& rot, const Vector3& scale);

protected:
	Vector3 m_position = Vector3::Zero;				// 座標
	Vector3 m_scale = Vector3::One;					// 拡縮
	Quaternion m_rotation = Quaternion::Identity;	// 回転

	ModelRender m_modelRender;						// モデル描画機能
};


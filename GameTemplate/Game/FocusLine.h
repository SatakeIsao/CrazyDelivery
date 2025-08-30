#pragma once
class FocusLine : public IGameObject
{
public:
	FocusLine();
	~FocusLine();

	bool Start();
	/// <summary>
	/// スプライトを初期化
	/// </summary>
	void InitSprite();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// 外から拡大率を指定
	/// NOTE:即座に変化するのではなく徐々に変化させるため、線形補間に必要な情報もこのときに保存
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(const float scale)
	{
		m_targetScale = scale;
		m_saveScale = m_currentScale;
	}
private:
	SpriteRender m_focusLineSprite;	//集中線のスプライト
	Vector3 m_position;				//座標
	float m_targetScale;			//目標拡大率
	float m_saveScale = 0.0f;		//前回の拡大率
	float m_currentScale = 0.0f;	//現在の拡大率
	float m_elapsedTimer = 0.0f;	//経過時間
	bool m_isEffectVisible = false;
};


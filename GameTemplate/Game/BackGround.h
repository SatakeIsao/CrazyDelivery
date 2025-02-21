#pragma once

class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start();
	void Init();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// 座標を設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	/// <summary>
	/// 回転を設定
	/// </summary>
	/// <param name="rotation">回転</param>
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	/// <summary>
	/// 拡大率を設定
	/// </summary>
	/// <param name="scale">拡大率</param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}
	
	
private:
	ModelRender			m_bgModel;					//背景モデル
	ModelRender			m_loadModel;				//地面モデル
	PhysicsStaticObject m_roadPhyStaticObject;		//静的物理オブジェクト
	Vector3				m_position = Vector3::Zero;	//座標
	Quaternion			m_rotation;					//回転
	Vector3				m_scale = Vector3::One;		//拡大率
	PhysicsStaticObject m_bgPhysicsStaticObject;	//静的オブジェクトを保持させる
};


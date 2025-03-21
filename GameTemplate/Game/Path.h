#pragma once
#include "MakeEffect.h"

struct Point {
	int no;	// ポイント番号
	Vector3 position;	// 座標
};
/// <summary>
/// 移動パスを表すクラス
/// </summary>
class Path 
{
public:
	Path();
	~Path();

	/// <summary>
	/// パスに新しい座標を追加
	/// </summary>
	/// <param name="point"></param>
	void AddPointPos(int no, Vector3& position)
	{
		Point point = { no, position };
		m_pointList.push_back(point);
	}
	/// <summary>
	/// 収集されたポイントの情報からパスを構築する
	/// </summary>
	void Build();

	/// <summary>
	/// エフェクトの再生
	/// </summary>
	/// <param name="name">名前</param>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	/// <param name="scale">拡大率</param>
	void PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale);

	///// <summary>
	///// 座標を設定
	///// </summary>
	///// <param name="pos"></param>
	//void SetPosition(const Vector3& pos)
	//{
	//	m_position = pos;
	//}

	///// <summary>
	///// 座標の取得
	///// </summary>
	///// <returns></returns>
	//const Vector3& GetPosition() const	{
	//	return m_position;
	//}

	/// <summary>
	/// パスのポイントリストを取得
	/// </summary>
	/// <returns></returns>
	const std::vector<Point>& GetPointList() const
	{
		return m_pointList;
	}

	/// <summary>
	/// パスの先頭ポイントリストを取得
	/// </summary>
	/// <returns></returns>
	const Point& GetFirstPoint() const 
	{ 
		return m_pointList.front();
	}

	/// <summary>
	/// パスの末尾ポイントリストを取得
	/// </summary>
	/// <returns></returns>
	const Point& GetLastPoint() const
	{
		return m_pointList.back();
	}

private:
	std::vector<Point>	m_pointList;	//ポイントのリスト
};


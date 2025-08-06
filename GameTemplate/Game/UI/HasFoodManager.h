#pragma once

class HasFoodManager : public IGameObject
{
public:
	HasFoodManager() {};
	~HasFoodManager() {};
	// todo for 必要に応じて追加
	//bool Start();
	//void Init();
	//void Update();

public:
	/// <summary>
	/// ハンバーガーを持っているか
	/// </summary>
	inline bool HasAnyHamburger()
	{
		return m_hasAnyHamburger;
	}
	/// <summary>
	/// ピザを持っているか
	/// </summary>
	inline bool HasAnyPizza() const
	{
		return m_hasAnyPizza;
	}
	/// <summary>
	/// 寿司を持っているか
	/// </summary>
	inline bool HasAnySushi() const
	{
		return m_hasAnySushi;
	}
public:
	/// <summary>
	/// ハンバーガーを上限まで持っているか
	/// </summary>
	inline bool HasFullHamburger()
	{
		return m_hasFullHamburger;
	}
	/// <summary>
	/// ピザを上限まで持っているか
	/// </summary>
	inline bool HasFullPizza() const
	{
		return m_hasFullPizza;
	}
	/// <summary>
	/// 寿司を上限まで持っているか
	/// </summary>
	inline bool HasFullSushi() const
	{
		return m_hasFullSushi;
	}

public:
	/// <summary>
	/// ハンバーガーを持っているかを設定
	/// </summary>
	inline bool SetHasAnyHamburger(bool anyHas)
	{
		return m_hasAnyHamburger = anyHas;
	}
	/// <summary>
	/// ピザを持っているかを設定
	/// </summary>
	inline bool SetHasAnyPizza(bool anyHas)
	{
		return m_hasAnyPizza = anyHas;
	}
	/// <summary>
	/// 寿司を持っているかを設定
	/// </summary>
	inline bool SetHasAnySushi(bool anyHas)
	{
		return m_hasAnySushi = anyHas;
	}
public:
	/// <summary>
	/// ハンバーガーを上限まで持っているかを設定
	/// </summary>
	inline bool SetHasFullHamburger(bool fullHas)
	{
		return m_hasFullHamburger = fullHas;
	}
	/// <summary>
	/// ピザを上限まで持っているかを設定
	/// </summary>
	inline bool SetHasFullPizza(bool fullHas)
	{
		return m_hasFullPizza = fullHas;
	}
	/// <summary>
	/// 寿司を上限まで持っているかを設定
	/// </summary>
	inline bool SetHasFullSushi(bool fullHas)
	{
		return m_hasFullSushi = fullHas;
	}

private:
	bool m_hasAnyHamburger = false;		// ハンバーガーを持っているか
	bool m_hasAnyPizza = false;			// ピザを持っているか
	bool m_hasAnySushi = false;			// 寿司を持っているか

	bool m_hasFullHamburger = false;	// ハンバーガーを上限まで持っているか
	bool m_hasFullPizza = false;		// ピザを上限まで持っているか
	bool m_hasFullSushi = false;		// 寿司を上限まで持っているか
};


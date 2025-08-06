#pragma once

class HasFoodManager : public IGameObject
{
public:
	HasFoodManager() {};
	~HasFoodManager() {};
	// todo for �K�v�ɉ����Ēǉ�
	//bool Start();
	//void Init();
	//void Update();

public:
	/// <summary>
	/// �n���o�[�K�[�������Ă��邩
	/// </summary>
	inline bool HasAnyHamburger()
	{
		return m_hasAnyHamburger;
	}
	/// <summary>
	/// �s�U�������Ă��邩
	/// </summary>
	inline bool HasAnyPizza() const
	{
		return m_hasAnyPizza;
	}
	/// <summary>
	/// ���i�������Ă��邩
	/// </summary>
	inline bool HasAnySushi() const
	{
		return m_hasAnySushi;
	}
public:
	/// <summary>
	/// �n���o�[�K�[������܂Ŏ����Ă��邩
	/// </summary>
	inline bool HasFullHamburger()
	{
		return m_hasFullHamburger;
	}
	/// <summary>
	/// �s�U������܂Ŏ����Ă��邩
	/// </summary>
	inline bool HasFullPizza() const
	{
		return m_hasFullPizza;
	}
	/// <summary>
	/// ���i������܂Ŏ����Ă��邩
	/// </summary>
	inline bool HasFullSushi() const
	{
		return m_hasFullSushi;
	}

public:
	/// <summary>
	/// �n���o�[�K�[�������Ă��邩��ݒ�
	/// </summary>
	inline bool SetHasAnyHamburger(bool anyHas)
	{
		return m_hasAnyHamburger = anyHas;
	}
	/// <summary>
	/// �s�U�������Ă��邩��ݒ�
	/// </summary>
	inline bool SetHasAnyPizza(bool anyHas)
	{
		return m_hasAnyPizza = anyHas;
	}
	/// <summary>
	/// ���i�������Ă��邩��ݒ�
	/// </summary>
	inline bool SetHasAnySushi(bool anyHas)
	{
		return m_hasAnySushi = anyHas;
	}
public:
	/// <summary>
	/// �n���o�[�K�[������܂Ŏ����Ă��邩��ݒ�
	/// </summary>
	inline bool SetHasFullHamburger(bool fullHas)
	{
		return m_hasFullHamburger = fullHas;
	}
	/// <summary>
	/// �s�U������܂Ŏ����Ă��邩��ݒ�
	/// </summary>
	inline bool SetHasFullPizza(bool fullHas)
	{
		return m_hasFullPizza = fullHas;
	}
	/// <summary>
	/// ���i������܂Ŏ����Ă��邩��ݒ�
	/// </summary>
	inline bool SetHasFullSushi(bool fullHas)
	{
		return m_hasFullSushi = fullHas;
	}

private:
	bool m_hasAnyHamburger = false;		// �n���o�[�K�[�������Ă��邩
	bool m_hasAnyPizza = false;			// �s�U�������Ă��邩
	bool m_hasAnySushi = false;			// ���i�������Ă��邩

	bool m_hasFullHamburger = false;	// �n���o�[�K�[������܂Ŏ����Ă��邩
	bool m_hasFullPizza = false;		// �s�U������܂Ŏ����Ă��邩
	bool m_hasFullSushi = false;		// ���i������܂Ŏ����Ă��邩
};


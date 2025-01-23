#pragma once

#include "Player.h"


class ShopHamburger;
class ShopPizza;
class ShopSushi;

class CustomerMan;
class CustomerMan_Hamburger;
class CustomerMan_Pizza;
class CustomerMan_Sushi;
class InventoryUI;
class ResultUI;
class GameTimer;
//#include "CustomerMan_Hamburger.h"


class MapUI : public IGameObject
{
public:
	enum MapFadeState {
		Map_Fade_Zero,		//表示しない
		Map_Fade_In,		//フェードイン
		Map_Fade_Default,	//フェードアウト
		Map_Fade_Out,		//表示する
	};

	struct CoolTimeSpriteData
	{
	private:
		/// <summary>
		/// ワイプ方向
		/// </summary>
		float m_wipeRatio = 6.3f; //6.3f=全体のアルファ値
		/// <summary>
		/// アルファ値
		/// </summary>
		float m_alpha = 0.7f;
		/// <summary>
		/// ワイプサイズ
		/// </summary>
		float m_wipeSize = 0;
	public:
		/// <summary>
		/// 割合の初期化
		/// </summary>
		/// <param name="value"></param>
		void SetDegree(const float value)
		{
			m_wipeSize = value;
		}
		/// <summary>
		/// 割合の加算
		/// </summary>
		/// <param name="addValue"></param>
		void AddDegree(const float addValue)
		{
			m_wipeSize += addValue;
		}
		/// <summary>
		/// 割合の取得
		/// </summary>
		/// <returns></returns>
		const float& GetDegree() const
		{
			return m_wipeSize;
		}
		/// <summary>
		/// 方向決定
		/// </summary>
		/// <param name="value"></param>
		void SetDirection(const float& value)
		{
			m_wipeRatio = value;
		}
		/// <summary>
		/// アルファ値の加算
		/// </summary>
		/// <param name="addValue"></param>
		void AddDirection(const float addValue)
		{
			m_wipeRatio += addValue;
		}
		/// <summary>
		/// 方向取得
		/// </summary>
		/// <returns></returns>
		const float& GetDirection() const
		{
			return m_wipeRatio;
		}
		/// <summary>
		/// アルファ値の初期化
		/// </summary>
		/// <param name="value"></param>
		void SetAlpha(const float value)
		{
			m_alpha = value;
		}
		/// <summary>
		/// アルファ値の加算
		/// </summary>
		/// <param name="addValue"></param>
		void AddAlpha(const float addValue)
		{
			m_alpha += addValue;
		}
		/// <summary>
		/// アルファ値の取得
		/// </summary>
		/// <returns></returns>
		const float& GetAlpha() const
		{
			return m_alpha;
		}
	};

	MapUI();
	~MapUI();
	bool Start() override;
	void Update() override;
	void MapSpriteFade();
	float CalcAlpha();
	bool IsInsideCircle(const Vector3& pos, const Vector3& center, float radius) {
		Vector3 diff = pos - center;
		return diff.LengthSq() <= (radius * radius);
	}
	void CalcWipeRatio();
	//void CalcAlpha(float& alpha);
	void AlphaZero();
	void PlayerSpritePulse();
	void Render(RenderContext& rc);
private:
	const bool WorldPosConvertToMapPos(
	Vector3 worldCenterPosition, 
	Vector3 worldPosition, 
	Vector3& mapPosition);
	SpriteRender m_spriteRender;		//全体のマップ
	SpriteRender m_playerSprite;		//プレイヤー
	SpriteRender m_bargerShopSprite;	//ハンバーガー1店舗目
	SpriteRender m_bargerShopSprite2;	//ハンバーガー2店舗目
	SpriteRender m_bargerShopGray;
	SpriteRender m_bargerShopGray2;
	SpriteRender m_bargerShopX;
	SpriteRender m_bargerShopX2;

	SpriteRender m_pizzaShopSprite;		//ピザ1店舗目
	SpriteRender m_pizzaShopSprite2;	//ピザ2店舗目
	SpriteRender m_pizzaShopGray;
	SpriteRender m_pizzaShopGray2;
	SpriteRender m_pizzaShopX;
	SpriteRender m_pizzaShopX2;

	SpriteRender m_sushiShopSprite;		//寿司1店舗目
	SpriteRender m_sushiShopSprite2;	//寿司2店舗目
	SpriteRender m_sushiShopGray;
	SpriteRender m_sushiShopGray2;
	SpriteRender m_sushiShopX;
	SpriteRender m_sushiShopX2;

	SpriteRender m_customerHamburgerSprite;	//お客さんハンバーガー
	SpriteRender m_customerHamburgerSprite2;	//お客さんハンバーガー
	SpriteRender m_customerPizzaSprite;
	SpriteRender m_customerPizzaSprite2;
	SpriteRender m_customerSushiSprite;
	SpriteRender m_customerSushiSprite2;
	
	MapFadeState m_fadeState = Map_Fade_Zero;
	nsPlayer::Player* m_player = nullptr;
	InventoryUI* m_inventoryUI = nullptr;
	std::vector<ShopHamburger*> m_shopHamburger;
	std::vector<ShopPizza*> m_shopPizza;
	std::vector<ShopSushi*> m_shopSushi;
	CustomerMan* m_customerMan = nullptr;
	std::vector<CustomerMan_Hamburger*> m_customerMan_Hamburger;
	std::vector<CustomerMan_Pizza*> m_customerMan_Pizza;
	std::vector<CustomerMan_Sushi*> m_customerMan_Sushi;
	//std::vector<CustomerMan
	ResultUI* m_resultUI = nullptr;
	GameTimer* m_gameTimer = nullptr;

	CoolTimeSpriteData m_coolTimeSpriteData;
	float m_alpha = 0.0f;				//ミニマップのアルファ値
	float m_pulseAlpha = 0.0f;			//点滅させるためのアルファ値
	int m_pulseDirection = 1;			//アルファ値の増減方向
	int m_pulseCount = 0;				//点滅させる回数
	bool m_isImage = false;				//マップに表示するかどうか
};


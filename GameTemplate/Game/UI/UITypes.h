#pragma once

//アイテムの状態を表す列挙型
enum EnItemState : uint8_t
{
	enItemStateAll,					//すべてのアイテムを収集済み
	enItemStateGrayHalf,			//アイテムの半分がグレー
	enItemStateGrayAll,				//アイテムのすべてグレー
	enItemStateMax,
};

//食べ物の種類
enum EnFoodType : uint8_t
{
	enFoodTypeHamburger,
	enFoodTypePizza,
	enFoodTypeSushi,
	enFoodTypeMax,
};
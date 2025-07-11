#pragma once

//アイテムの状態を表す列挙型
enum EnItemState
{
	enItemStateAll,					//すべてのアイテムを収集済み
	enItemStateGrayHalf,			//アイテムの半分がグレー
	enItemStateGrayAll,				//アイテムのすべてグレー
	enItemStateMax,
};

//食べ物の種類
enum EnFoodType
{
	enFoodTypeHamburger,
	enFoodTypePizza,
	enFoodTypeSushi,
	enFoodTypeMax,
};
#pragma once

//�A�C�e���̏�Ԃ�\���񋓌^
enum EnItemState : uint8_t
{
	enItemStateAll,					//���ׂẴA�C�e�������W�ς�
	enItemStateGrayHalf,			//�A�C�e���̔������O���[
	enItemStateGrayAll,				//�A�C�e���̂��ׂăO���[
	enItemStateMax,
};

//�H�ו��̎��
enum EnFoodType : uint8_t
{
	enFoodTypeHamburger,
	enFoodTypePizza,
	enFoodTypeSushi,
	enFoodTypeMax,
};
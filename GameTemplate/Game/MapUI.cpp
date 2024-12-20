#include "stdafx.h"
#include "MapUI.h"

#include "ShopHamburger.h"
namespace
{
	Vector3 MAP_CENTER_POSITION = Vector3(0.0f, 0.0f, 0.0f);

	//�}�b�v�̕`��͈́i�~�`�̔��a�j
	float MAP_RADIUS = 240.0f;
	//�}�b�v�ɕ\������A�v���C���[��X�̐�������
	float LIMITED_RANGE_IMAGE_X = 7125.0f*2.5f;
	float LIMITED_RANGE_IMAGE_Z = 9530.0f*2.5f;
	/*float LIMITED_RANGE_IMAGE_X = 7125.0f;
	float LIMITED_RANGE_IMAGE_Z = 9530.0f;*/
}

MapUI::MapUI()
{
}

MapUI::~MapUI()
{
}

bool MapUI::Start()
{
	//�}�b�v�̍����摜
	m_spriteRender.Init("Assets/MapData/map.DDS", 400, 400);
	m_spriteRender.SetPosition(Vector3(-600.0f,-250.0f,0.0f));
	m_spriteRender.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	//m_spriteRender.SetScale(m_scale);
	m_spriteRender.Update();

	//�}�b�v���S�̐Ԃ��摜
	m_playerSprite.Init("Assets/MapData/player.dds", 30, 30);
	m_playerSprite.SetPosition(Vector3(-600.0f, -250.0f, 0.0f));
	m_playerSprite.SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
	m_playerSprite.Update();

	//�n���o�[�K�[�X�̉摜
	m_bargerShopSprite.Init("Assets/MapData/hamburger.dds", 30, 30);
	m_bargerShopSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	//m_bargerShopSprite.Init("Assets/MapData/mapSushi.dds", 960, 540);
	//m_bargerShopSprite.SetPosition(Vector3(2144.19f, 0.0f, 1365.55f));
	m_bargerShopSprite2.Init("Assets/MapData/hamburger.dds", 30, 30);
	m_bargerShopSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });

	//�s�U�X�̉摜
	m_pizzaShopSprite.Init("Assets/MapData/mapPizza.dds", 960, 540);
	m_pizzaShopSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	m_pizzaShopSprite2.Init("Assets/MapData/mapPizza.dds", 960, 540);
	m_pizzaShopSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });

	//���i�X�̉摜
	m_sushiShopSprite.Init("Assets/MapData/mapSushi.dds", 960, 540);
	m_sushiShopSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	m_sushiShopSprite2.Init("Assets/MapData/mapSushi.dds", 960, 540);
	m_sushiShopSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });

	m_player = FindGO<nsPlayer::Player>("player");
	m_shopHamburger = FindGOs<ShopHamburger>("shophamburger");
	auto* shopHamburgerB = FindGO<ShopHamburger>("shophamburgerB");

	m_shopPizza = FindGOs<ShopPizza>("shoppizza");
	auto* shopPizzaB = FindGO<ShopPizza>("shoppizzaB");

	m_shopSushi = FindGOs<ShopSushi>("shopsushi");
	auto* shopSushiB = FindGO<ShopSushi>("shopsushiB");

	return true;
}

void MapUI::Update()
{
	
	Vector3 playerPosition = m_player->GetPostion();
	Vector3 bargerShopPositionA = m_shopHamburger[0]->GetPosition();
	Vector3 bargerShopPositionB = m_shopHamburger[1]->GetPosition();
	Vector3 pizzaShopPositionA = m_shopPizza[0]->GetPosition();
	Vector3 pizzaShopPositionB = m_shopPizza[1]->GetPosition();
	Vector3 sushiShopPositionA = m_shopSushi[0]->GetPosition();
	Vector3 sushiShopPositionB = m_shopSushi[1]->GetPosition();

	Vector3 mapPosition;

	if (g_pad[0]->IsTrigger(enButtonB) && m_fadeState == Map_Fade_Zero)
	{
		m_fadeState = Map_Fade_In;
	}

	MapSpriteFade();

	//�_�ŏ������X�V
	if (m_fadeState == Map_Fade_Default)
	{
		PlayerSpritePulse();
	}

	//�}�b�v�ɕ\������͈͂ɂ��X����������
	if (WorldPosConvertToMapPos(playerPosition, bargerShopPositionA, mapPosition))
	{
		//�}�b�v�ɕ\������悤�ɐݒ�
		m_isImage = true;
		//SpriteRender�ɍ��W��ݒ�
		m_bargerShopSprite.SetPosition(mapPosition);
	}
	//�}�b�v�ɕ\������͈͂ɂ��X����������
	if (WorldPosConvertToMapPos(playerPosition, bargerShopPositionB, mapPosition))
	{
		//�}�b�v�ɕ\������悤�ɐݒ�
		m_isImage = true;
		//SpriteRender�ɍ��W��ݒ�
		m_bargerShopSprite2.SetPosition(mapPosition);
	}
	//�}�b�v�ɕ\������͈͂ɂ��X����������
	if (WorldPosConvertToMapPos(playerPosition, pizzaShopPositionA, mapPosition))
	{
		//�}�b�v�ɕ\������悤�ɐݒ�
		m_isImage = true;
		//SpriteRender�ɍ��W��ݒ�
		m_pizzaShopSprite.SetPosition(mapPosition);
	}
	//�}�b�v�ɕ\������͈͂ɂ��X����������
	if (WorldPosConvertToMapPos(playerPosition, pizzaShopPositionB, mapPosition))
	{
		//�}�b�v�ɕ\������悤�ɐݒ�
		m_isImage = true;
		//SpriteRender�ɍ��W��ݒ�
		m_pizzaShopSprite2.SetPosition(mapPosition);
	}
	//�}�b�v�ɕ\������͈͂ɂ��X����������
	if (WorldPosConvertToMapPos(playerPosition, sushiShopPositionA, mapPosition))
	{
		//�}�b�v�ɕ\������悤�ɐݒ�
		m_isImage = true;
		//SpriteRender�ɍ��W��ݒ�
		m_sushiShopSprite.SetPosition(mapPosition);
	}
	//�}�b�v�ɕ\������͈͂ɂ��X����������
	if (WorldPosConvertToMapPos(playerPosition, sushiShopPositionB, mapPosition))
	{
		//�}�b�v�ɕ\������悤�ɐݒ�
		m_isImage = true;
		//SpriteRender�ɍ��W��ݒ�
		m_sushiShopSprite2.SetPosition(mapPosition);
	}

	else
	{
		//�}�b�v�ɕ\�����Ȃ�
		m_isImage = false;
	}
	m_spriteRender.Update();
	m_playerSprite.Update();
	m_bargerShopSprite.Update();
	m_bargerShopSprite2.Update();
	m_pizzaShopSprite.Update();
	m_pizzaShopSprite2.Update();
	m_sushiShopSprite.Update();
	m_sushiShopSprite2.Update();
}

void MapUI::MapSpriteFade()
{
	switch (m_fadeState) {
	case Map_Fade_Zero:
		
		break;
	case Map_Fade_In:
		CalcAlpha(m_alpha);
		m_spriteRender.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_bargerShopSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_bargerShopSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_pizzaShopSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_pizzaShopSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_sushiShopSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_sushiShopSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		break;
	case Map_Fade_Out:
		break;
	case Map_Fade_Default:
		m_alpha = 1.0f;
		m_spriteRender.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_bargerShopSprite.SetMulColor({ 1.0f,1.0f,1.0f,0.8 });	//0.5/0.5/0.5/0.8
		m_bargerShopSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_pizzaShopSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_pizzaShopSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_sushiShopSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_sushiShopSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		break;
	}
}

void MapUI::CalcAlpha(float& alpha)
{
	alpha += 0.025f;
	if (alpha > 1.0f)
	{
		alpha = 1.0f;
		m_fadeState = Map_Fade_Default;
	}
}

void MapUI::AlphaZero()
{
}

void MapUI::PlayerSpritePulse()
{
	if (m_pulseCount <= 5)
	{
		m_pulseAlpha += 0.02f * m_pulseDirection;
		if (m_pulseAlpha > 1.0f)
		{
			m_pulseAlpha = 1.0f;
			m_pulseDirection = -1;
			m_pulseCount++;
		}
		else if (m_pulseAlpha < 0.0f)
		{
			m_pulseAlpha = 0.0f;
			m_pulseDirection = 1;
			m_pulseCount++;
		}
		m_playerSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_pulseAlpha });
	}
	else {
		m_playerSprite.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	}
	
}

const bool MapUI::WorldPosConvertToMapPos(Vector3 worldCenterPosition, Vector3 worldPosition, Vector3& mapPosition)
{
	//Y�����W�̓}�b�v�Ɗ֌W�Ȃ��̂�0�ɂ���
	worldCenterPosition.y = 0.0f;
	worldPosition.y = 0.0f;
	Vector3 d = worldPosition - worldCenterPosition;
	
	if (d.LengthSq() >= LIMITED_RANGE_IMAGE_X * LIMITED_RANGE_IMAGE_Z)
	{
		return false;
	}

	//�x�N�g���̒������擾
	float leng = d.Length();

	//�J�����̑O�x�N�g������N�H�[�^�j�I���𐶐�

	Vector3 f = g_camera3D->GetForward();
	Quaternion cameraRot;
	cameraRot.SetRotationY(atan2(-f.x, f.z));
	////�x�N�g���ɃJ�����̉�]��K�p
	cameraRot.Apply(d);
	//d.Normalize();


	/*d.x = (d.x / LIMITED_RANGE_IMAGE_X) * leng;
	d.z = (d.z / LIMITED_RANGE_IMAGE_Z) * leng;*/
	d.x = (d.x / LIMITED_RANGE_IMAGE_X) * 400.0f;
	d.z = (d.z / LIMITED_RANGE_IMAGE_Z) * 400.0f;

	//�}�b�v�̒��S���W�Ə�L�x�N�g�������Z����
	mapPosition = Vector3(-600.0f, -250.0f, 0.0f);
	mapPosition.x += d.x;
	mapPosition.y += d.z;
	//g_camera2D->CalcScreenPositionFromWorldPosition()
	return true;

	/*
	//Y���W�̓}�b�v�̍��W�Ƃ͊֌W�Ȃ��̂ŁA�O�ɂ���
	worldCenterPosition.y = 0.0f;
	worldPosition.y = 0.0f;
	Vector3 diff = worldPosition - worldCenterPosition;
	//�}�b�v�̒��S�Ƃ���I�u�W�F�N�g�Ƃ̋��������ȏ㗣��Ă�����B
	if (diff.LengthSq() >= LIMITED_RANGE_IMAGE_X * LIMITED_RANGE_IMAGE_Z)
	{
		//�\�����Ȃ��悤�ɂ���B
		return false;
	}

	//�x�N�g���̒������擾
	float length = diff.Length();

	//�J�����̑O�����x�N�g������N�H�[�^�j�I���𐶐�
	Vector3 forward = g_camera3D->GetForward();
	Quaternion rot;
	rot.SetRotationY(atan2(-forward.x, forward.z));

	//�x�N�g���ɃJ�����̉�]��ʗp
	rot.Apply(diff);

	//�x�N�g���𐳋K��
	rot.Normalize();

	//�}�b�v�̑傫��/���������Ńx�N�g�����}�b�v���W�n�ɕϊ�
	diff *= length * MAP_RADIUS / LIMITED_RANGE_IMAGE_Z;
	//diff *= length * 240.0f / 600.0f;

	//�}�b�v�̒������W�Ə�L�x�N�g�������Z����
	mapPosition = Vector3(MAP_CENTER_POSITION.x + diff.x,MAP_CENTER_POSITION.y + diff.z, 0.0f);
	//mapPosition = Vector3(1000.0f + diff.x, 15500.0f + diff.z, 0.0f);
	return true; */
}

void MapUI::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_playerSprite.Draw(rc);
	if (m_isImage == false)
	{
		return;
	}
	m_bargerShopSprite.Draw(rc);
	m_bargerShopSprite2.Draw(rc);
	m_pizzaShopSprite.Draw(rc);
	m_pizzaShopSprite2.Draw(rc);
	m_sushiShopSprite.Draw(rc);
	m_sushiShopSprite2.Draw(rc);
}

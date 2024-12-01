#include "stdafx.h"
#include "MapUI.h"

namespace
{
	Vector3 MAP_CENTER_POSITION = Vector3(0.0f, 0.0f, 0.0f);

	//�}�b�v�̕`��͈́i�~�`�̔��a�j
	float MAP_RADIUS = 240.0f;
	//�}�b�v�ɕ\������A�v���C���[��X�̐�������
	float LIMITED_RANGE_IMAGE = 600.0f;
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

	//�}�b�v���S�̐Ԃ��摜
	m_playerSprite.Init("Assets/MapData/player.dds", 30, 30);
	m_playerSprite.SetPosition(Vector3(-600.0f, -250.0f, 0.0f));

	m_bargerShopSprite.Init("Assets/MapData/hamburger.dds", 30, 30);
	//m_bargerShopSprite.SetPosition(Vector3(2144.19f, 0.0f, 1365.55f));

	m_player = FindGO<nsPlayer::Player>("player");
	return true;
}

void MapUI::Update()
{
	Vector3 playerPosition = m_player->GetPostion();
	Vector3 bargerShopPositon = Vector3(2144.19f, 0.0f, 1365.55f);

	Vector3 mapPosition;

	//�}�b�v�ɕ\������͈͂ɂ��X����������
	if (WorldPosConvertToMapPos(playerPosition, bargerShopPositon, mapPosition))
	{
		//�}�b�v�ɕ\������悤�ɐݒ�
		m_isImage = true;
		//SpriteRender�ɍ��W��ݒ�
		m_bargerShopSprite.SetPosition(mapPosition);
	}
	else
	{
		//�}�b�v�ɕ\�����Ȃ�
		m_isImage = false;
	}
	m_spriteRender.Update();
	m_playerSprite.Update();
	m_bargerShopSprite.Update();
}

const bool MapUI::WorldPosConvertToMapPos(Vector3 worldCenterPosition, Vector3 worldPosition, Vector3& mapPosition)
{
	//Y���W�̓}�b�v�̍��W�Ƃ͊֌W�Ȃ��̂ŁA�O�ɂ���
	worldCenterPosition.y = 0.0f;
	worldPosition.y = 0.0f;
	Vector3 diff = worldPosition - worldCenterPosition;

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
	diff *= length * 240.0f / 600.0f;

	//�}�b�v�̒������W�Ə�L�x�N�g�������Z����
	mapPosition = Vector3(1000.0f + diff.x, 15500.0f + diff.z, 0.0f);
	return true;
}

void MapUI::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_playerSprite.Draw(rc);
	if (m_isImage == true)
	{
		return;
	}
	m_bargerShopSprite.Draw(rc);
}

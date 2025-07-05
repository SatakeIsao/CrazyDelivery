#pragma once

#include "SkyCube.h"
#include "Player/Player.h"
#include "LevelRender.h"
#include "MakeEffect.h"
#include "GameSound.h"
#include "UI/ResultUI.h"

class BackGround;
class GameCamera;
class GameTimer;
class InventoryUI;
class MapUI;
class StartButtonUI;
class ShopHamburger;
class ShopPizza;
class ShopSushi;
class CustomerMan;
class GameInformation;
class Fade;
class PathStorage;
class Player;

class Game : public IGameObject
{
public:

	//�X�R�A�p�l���̍��W���Ǘ�����񋓌^
	enum ScorePanelSetPos
	{
		POS_SCORE_OUTSIDE,	//�X�R�A���O���ɂ�����
		POS_SCORE_INSIDE,	//�X�R�A�������ɂ�����
		POS_SCORE_SLIDE,	//�X�R�A���X���C�h������
	};

	Game();
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	//void SetSkyCube();
	void FinishTimer();
	void NextScorePosState();

	/// <summary>
	/// �G�t�F�N�g�̍Đ�
	/// </summary>
	/// <param name="name">���O</param>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	/// <param name="scale">�g�嗦</param>
	void PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale)
	{
		//�G�t�F�N�g�̍Đ�
		EffectEmitter* effect = NewGO<EffectEmitter>(0);
		effect->Init(name);
		effect->SetPosition(pos);
		effect->SetRotation(rot);
		effect->SetScale(scale);
		effect->Play();
	}


private:
	LevelRender			m_levelRender;											//���x���̃����_�����O
	SkyCube*			m_skyCube = nullptr;									//�X�J�C�L���[�u�̃I�u�W�F�N�g
	nsPlayer::Player*	m_player = nullptr;										//�v���C���[�̃I�u�W�F�N�g
	BackGround*			m_backGround = nullptr;									//�w�i�̃I�u�W�F�N�g
	GameCamera*			m_gameCamera = nullptr;									//�Q�[���J�����̃I�u�W�F�N�g
	GameTimer*			m_gameTimer = nullptr;									//�Q�[���^�C�}�[�̃I�u�W�F�N�g
	InventoryUI*		m_inventoryUI = nullptr;								//�C���x���g���[UI�̃I�u�W�F�N�g
	MapUI*				m_mapUI = nullptr;										//�}�b�vUI�̃I�u�W�F�N�g
	StartButtonUI*		m_startButtonUI = nullptr;								//�X�^�[�g�{�^��UI�̃I�u�W�F�N�g
	MakeEffect*			m_makeEfe = nullptr;									//�G�t�F�N�g�쐬�̃I�u�W�F�N�g
	ResultUI*			m_resultUI = nullptr;									//���U���gUI�̃I�u�W�F�N�g
	GameInformation*	m_gameInfo = nullptr;									//�Q�[���C���t�H���[�V�����̃I�u�W�F�N�g
	Fade*				m_fade = nullptr;										//�t�F�[�h�̃I�u�W�F�N�g
	PathStorage*		m_pathSt;												//�p�X�X�g���[�W�̃I�u�W�F�N�g

	SpriteRender		m_scorePanelSprite;										//�X�R�A�p�l���X�v���C�g

	Vector3				m_scorePanelSpritePos = Vector3(1050.0f, 550.0f, 0.0f);	//�X�R�A�p�l���̍��W

	ScorePanelSetPos	m_setScorePosState = POS_SCORE_OUTSIDE;					//�X�R�A�p�l���̍��W�̏��

	int					m_nowScore = 0.0f;										//���݂̃X�R�A
	
	bool				m_isFinish = false;										//�Q�[���I�����Ă��邩
	bool				m_isFinishStarted = false;								//�I�������J�n���Ă��邩

	float				m_finishStartTime = 0.0f;								//�I���J�n����

	
};


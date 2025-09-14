#pragma once
#include <functional>
#include <map>
#include <vector>

enum class GameEvents{
	GameFinished,
	ResultUIReady,
};

//�C�x���g�̍w�ǎ�(�֐�)���Ǘ�����}�b�v
//�L�[�̓C�x���g�̎�ށA�l�͂��̃C�x���g�ɓo�^���ꂽ�֐��̃��X�g
//��: m_listeners[GameEvents::GameFinished] = {func1, func2, ...}
using EventListeners = std::map<GameEvents, std::vector<std::function<void()>>>;

//EventManager�N���X
//�V���O���g���Ƃ��Ď���
class EventManager {
public:
	static EventManager& GetInstance() {
		static EventManager instance;
		return instance;
	}

	//�C�x���g�̍w��
	//�C�x���g�����������Ƃ��ɌĂяo�����֐���o�^
	//listener�͊֐��I�u�W�F�N�g(std::function)�Ƃ��Ď󂯎��
	//subscribe(GameEvents::GameFinished,[&](){player->ResetPosition();});
	void Subscribe(GameEvents event, std::function<void()> listener) {
		m_listeners[event].push_back(listener);
	}
	//�C�x���g�̍w�ǉ���
	//���ׂĂ̓o�^���N���A
	void ClearListeners() {
		m_listeners.clear();
	}
	//�C�x���g�̔���
	//�o�^���ꂽ�֐������ׂČĂяo��
	//��: Trigger(GameEvents::GameFinished);
	void Trigger(GameEvents event) {
		if (m_listeners.count(event)) {
			for (const auto& listener : m_listeners[event]) {
				listener(); //�o�^���ꂽ�֐����Ăяo��
			}
		}
	}
private:
	EventManager() {}
	~EventManager() {}
	EventListeners m_listeners; //�C�x���g�Ƃ��̍w�ǎ҂��Ǘ�����}�b�v

	//�R�s�[�R���X�g���N�^�Ƒ�����Z�q���폜���ăV���O���g����ۏ�
	EventManager(const EventManager&) = delete;
	EventManager& operator = (const EventManager&) = delete;
};

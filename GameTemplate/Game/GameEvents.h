#pragma once
#include <functional>
#include <map>
#include <vector>

enum class GameEvents{
	GameFinished,
	ResultUIReady,
};

//イベントの購読者(関数)を管理するマップ
//キーはイベントの種類、値はそのイベントに登録された関数のリスト
//例: m_listeners[GameEvents::GameFinished] = {func1, func2, ...}
using EventListeners = std::map<GameEvents, std::vector<std::function<void()>>>;

//EventManagerクラス
//シングルトンとして実装
class EventManager {
public:
	static EventManager& GetInstance() {
		static EventManager instance;
		return instance;
	}

	//イベントの購読
	//イベントが発生したときに呼び出される関数を登録
	//listenerは関数オブジェクト(std::function)として受け取る
	//subscribe(GameEvents::GameFinished,[&](){player->ResetPosition();});
	void Subscribe(GameEvents event, std::function<void()> listener) {
		m_listeners[event].push_back(listener);
	}
	//イベントの購読解除
	//すべての登録をクリア
	void ClearListeners() {
		m_listeners.clear();
	}
	//イベントの発生
	//登録された関数をすべて呼び出す
	//例: Trigger(GameEvents::GameFinished);
	void Trigger(GameEvents event) {
		if (m_listeners.count(event)) {
			for (const auto& listener : m_listeners[event]) {
				listener(); //登録された関数を呼び出す
			}
		}
	}
private:
	EventManager() {}
	~EventManager() {}
	EventListeners m_listeners; //イベントとその購読者を管理するマップ

	//コピーコンストラクタと代入演算子を削除してシングルトンを保証
	EventManager(const EventManager&) = delete;
	EventManager& operator = (const EventManager&) = delete;
};

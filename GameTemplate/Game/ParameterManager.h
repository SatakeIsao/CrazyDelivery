#pragma once
#include "json.hpp"
#include "Util/CRC32.h"
#include <iostream>
#include <fstream>

/**
 * NOTE: ���ׂẴp�����[�^�[�ɕt����
 */
#define appParameter(name)\
public:\
	static constexpr uint32_t ID() { return Hash32(#name); }


 /** ���N���X�B�K���p�����邱�ƁI */
struct IMasterParameter {};

/** �v���C���[�̃X�e�[�^�X */
struct MasterPlayerStatus : public IMasterParameter
{
	appParameter(MasterPlayerStatus);
	//�����x
	float m_addAccele;
	//��]���x
	float m_rotSpeed;
	// �h���t�g���̉�]���x�{��
	float m_driftRotSpeedMultiplaer;
	//�n�ʂ̍���
	float m_groundHeight;
	//�d��
	float m_gravity;
	//�����ɂ����鎞��
	float m_decelerationTime;
	//�����W���̍ŏ��l
	float m_minDecelerationFactor;
	//���ςׂ̂���̎w��
	float m_maxDotPower;
	//���C�͂̍ŏ��l
	float m_minFriction;
	//���C�͂̍ő�l
	float m_maxFriction;
	//�ŏ�������
	float m_minDeceleration;
	//�ő匸����
	float m_maxDeceleration;
	//�@���x�N�g����Y�l(�Œ�)
	float m_normalYValue;
	//���ˌv�Z�p�̃X�J���[�l
	float m_reflectionScale;
	//�L�����N�^�[�R���g���[���[�̔��a
	float m_charaConRadius;
	//�L�����N�^�[�R���g���[���[�̍���
	float m_charaConHeight;
	//���x��~�̂������l
	float m_stopThreshold;
	//�X�s�[�h���Z�b�g�̂������l
	float m_speedThreshold;
	//�W�����v���鐔�l
	float m_jumpPower;
	//���x���
	float m_speedMax;
	//�_�b�V���ɂ���ē�����u�[�X�g
	float m_dashBoost;
	//�u�[�X�g�K�p���J�n����x������
	float m_startBoostDelay;
};


/** define�̎g�p�I�� */
#undef appParameter


/**
 * �p�����[�^�[�Ǘ��N���X
 */
class ParameterManager
{
private:
	// �����p�����[�^�[�������Ă��ǂ��悤��
	using ParameterVector = std::vector<IMasterParameter*>;
	// �e�p�����[�^�[���Ƃɕێ�����
	using ParameterMap = std::map<uint32_t, ParameterVector>;

private:
	ParameterMap m_parameterMap;		// �p�����[�^�[��ێ�

private:
	ParameterManager();
	~ParameterManager();

public:
	/// <summary>
	/// �p�����[�^�[�ǂݍ���
	/// NOTE: Unload���ĂԂ��Ƃ�Y��Ȃ��悤��
	///       ��2�����̃����_���Ńe���v���[�g�Ŏw�肷��^�̏��ɕϊ�����
	/// </summary>
	template <typename T>
	void LoadParameter(const char* path, const std::function<void(const nlohmann::json& j, T& p)>& func)
	{
		std::ifstream file(path);
		if (!file.is_open()) {
			return;
		}

		nlohmann::json jsonRoot;
		file >> jsonRoot;

		std::vector<IMasterParameter*> parameters;
		for (const auto& j : jsonRoot) {
			T* parameter = new T();
			func(j, *parameter);
			parameters.push_back(static_cast<IMasterParameter*>(parameter));
		}

		m_parameterMap.emplace(T::ID(), parameters);
	}

	/// <summary>
	/// �p�����[�^�[���
	/// </summary>
	template <typename T>
	void UnloadParameter()
	{
		auto it = m_parameterMap.find(T::ID());
		if (it != m_parameterMap.end()) {
			auto& parameters = it->second;
			for (auto* p : parameters) {
				delete p;
			}
			m_parameterMap.erase(it);
		}
	}

	/// <summary>
	/// 1�����p�����[�^�[���擾����
	/// </summary>
	template <typename T>
	const T* GetParameter(const int index = 0) const
	{
		const auto parameters = GetParameters<T>();
		if (parameters.size() == 0) { return nullptr; }
		if (parameters.size() <= index) { return nullptr; }
		return parameters[index];
	}
	/// <summary>
	/// �����p�����[�^�[���擾����
	/// </summary>
	template <typename T>
	inline const std::vector<T*> GetParameters() const
	{
		std::vector<T*> parameters;
		auto it = m_parameterMap.find(T::ID());
		if (it != m_parameterMap.end()) {
			for (auto* parameter : it->second) {
				parameters.push_back(reinterpret_cast<T*>(parameter));
			}
		}
		return parameters;
	}
	/// <summary>
	/// �p�����[�^�[�������_���ŉ�ForEach
	/// </summary>
	template <typename T>
	void ForEach(std::function<void(const T&)> func) const
	{
		const std::vector<T*> parameters = GetParameters<T>();
		for (const T* paramter : parameters) {
			func(*paramter);
		}
	}




	/**
	 * �V���O���g���p
	 */
public:
	/// <summary>
	/// �C���X�^���X�����
	/// </summary>
	static void CreateInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new ParameterManager();
		}
	}

	/// <summary>
	/// �C���X�^���X���擾
	/// </summary>
	static ParameterManager& Get()
	{
		return *m_instance;
	}

	/// <summary>
	/// �C���X�^���X��j��
	/// </summary>
	static void DestroyInstance()
	{
		if (m_instance != nullptr)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

private:
	static ParameterManager* m_instance; //�V���O���g���C���X�^���X
};
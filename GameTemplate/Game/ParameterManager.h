#pragma once
#include "json.hpp"
#include "Utill/CRC32.h"
#include <iostream>
#include <fstream>

/**
 * NOTE:���ׂẴp�����[�^�ɕt����
 */
#define appParameter(name)\
public:\
	static constexpr uint32_t ID(){return Hash32(#name);}

/*���N���X�B�K���p�����邱��*/
struct IMasterParameter {};

/*�v���C���[�̃X�e�[�^�X*/
struct MasterPlayerStatus : public IMasterParameter
{
	appParameter(MasterPlayerStatus);

	
};
/* define�̎g�p�I�� */
#undef appParameter

/**
 * �p�����[�^�Ǘ��N���X
 */
class ParameterManager
{
private:
	//�����p�����[�^�������Ă��ǂ��悤�ɁAID��uint32_t�Œ�`
	using ParameterVector = std::vector<IMasterParameter*>;
	//�e�p�����[�^���Ƃɕێ�
	using ParameterMap = std::map<uint32_t,ParameterVector>;
	ParameterMap m_parameterMap;

private:
	ParameterMap m_parameterMap; // �p�����[�^��ێ�����}�b�v
private:
	ParameterManager();
	~ParameterManager();

public:
	static void CreateInstance();
	static ParameterManager& Get();
	static void DestroyInstance();
private:
	static ParameterManager* m_instance;

};



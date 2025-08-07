#pragma once
#include "json.hpp"
#include "Utill/CRC32.h"
#include <iostream>
#include <fstream>

/**
 * NOTE:すべてのパラメータに付ける
 */
#define appParameter(name)\
public:\
	static constexpr uint32_t ID(){return Hash32(#name);}

/*基底クラス。必ず継承すること*/
struct IMasterParameter {};

/*プレイヤーのステータス*/
struct MasterPlayerStatus : public IMasterParameter
{
	appParameter(MasterPlayerStatus);

	
};
/* defineの使用終了 */
#undef appParameter

/**
 * パラメータ管理クラス
 */
class ParameterManager
{
private:
	//複数パラメータがあっても良いように、IDをuint32_tで定義
	using ParameterVector = std::vector<IMasterParameter*>;
	//各パラメータごとに保持
	using ParameterMap = std::map<uint32_t,ParameterVector>;
	ParameterMap m_parameterMap;

private:
	ParameterMap m_parameterMap; // パラメータを保持するマップ
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



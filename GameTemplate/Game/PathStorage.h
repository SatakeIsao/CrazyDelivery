#pragma once
class Path;
/// <summary>
/// パスを保持するストーレジ
/// </summary>
/// <remark>
///		このクラスはシングルトンパターンで設計されている
///		このクラスはゲーム中のパスを保持するストレージです。
///		パスを番号とセットで記憶している
/// </remark>
class PathStorage
{
private:
	//本人以外の制御
	PathStorage();
	~PathStorage();

public:
	//シングルトン
	static PathStorage* GetPathStorage() {
		return m_pathStorage;
	}
	
	/// <summary>
	/// １セット目のパス先頭取得
	/// </summary>
	/// <returns></returns>
	Path* GetFirstPath();
	Path* GetFirstPath2();
	Path* GetFirstPath3();
	Path* GetFirstPath4();
	Path* GetLastPath();
	Path* GetLastPath2();

	/// <summary>
	/// ストレージに追加するための関数
	/// </summary>
	/// <param name="number">検索可能なキー</param>
	/// <param name="path">キーに対応する値</param>
	void AddPath(int number, Path& path);
	
	/// <summary>
	/// PathStorageにpathNoの＊パスが保存されているか調べるための関数
	/// </summary>
	/// <param name="number"></param>
	/// <param name="path"></param>
	bool Exist(int number);

	/// <summary>
	/// インスタンスを作成する関数
	/// </summary>
	/// <returns></returns>
	static PathStorage* CreateInstance();

	/// <summary>
	/// インスタンスを削除する関数
	/// </summary>
	/// <returns></returns>
	static void DeleteInstance();

	/// <summary>
	/// パスを取得
	/// </summary>
	/// <param name="number">検索可能なキー</param>
	/// <returns></returns>
	Path* GetPath(int number)
	{
		auto it = m_paths.find(number);
		//すでに同じ番号のパスが存在していない場合
		if (it == m_paths.end()) 
		{
			//指定された番後のパスがない
			return nullptr;
		}
		//キーに対応する値を返す
		return it->second;
	}
	/// <summary>
	/// パスの数を取得
	/// </summary>
	/// <returns></returns>
	int GetPathCount() const
	{
		return m_paths.size();
	}

	
	
private:
	static PathStorage* m_pathStorage;	//PathStorageクラスのインスタンス
	std::map<int, Path*>	m_paths;	//番号とパス
};


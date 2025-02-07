#pragma once
struct Point {
	int no;	// �|�C���g�ԍ�
	Vector3 position;	// ���W
};
/// <summary>
/// �ړ��p�X��\���N���X
/// </summary>
class Path 
{
public:
	Path();
	~Path();

	/// <summary>
	/// �p�X�ɐV�������W��ǉ�
	/// </summary>
	/// <param name="point"></param>
	void AddPointPos(int no, Vector3& position)
	{
		Point point = { no, position };
		m_pointList.push_back(point);
	}
	/// <summary>
	/// ���W���ꂽ�|�C���g�̏�񂩂�p�X���\�z����
	/// </summary>
	void Build();

	///// <summary>
	///// ���W��ݒ�
	///// </summary>
	///// <param name="pos"></param>
	//void SetPosition(const Vector3& pos)
	//{
	//	m_position = pos;
	//}

	///// <summary>
	///// ���W�̎擾
	///// </summary>
	///// <returns></returns>
	//const Vector3& GetPosition() const	{
	//	return m_position;
	//}

	/// <summary>
	/// �p�X�̃|�C���g���X�g���擾
	/// </summary>
	/// <returns></returns>
	const std::vector<Point>& GetPointList() const
	{
		return m_pointList;
	}

	const Point& GetFirstPoint() const 
	{ 
		return m_pointList.front();
	}

	const Point& GetLastPoint() const
	{
		return m_pointList.back();
	}

private:
	std::vector<Point>	m_pointList;	//�|�C���g�̃��X�g
};


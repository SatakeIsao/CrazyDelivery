#include "stdafx.h"
#include "Path.h"

Path::Path()
{
}

Path::~Path()
{
}

void Path::Build()
{
	// ポイントリストをソートする(昇順)
	std::sort(m_pointList.begin(), m_pointList.end(), [](Point const& lhs, Point const& rhs)
	{
		return lhs.no < rhs.no;
	});

	
}


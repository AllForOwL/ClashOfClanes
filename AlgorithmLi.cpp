#include "AlgorithmLi.h"
#include "constants.h"

AlgorithmLi::AlgorithmLi()
{

}

AlgorithmLi::AlgorithmLi(AlgorithmLi& i_AlgorithmLi)
{

}


AlgorithmLi::AlgorithmLi(Point i_begin, Point i_end, std::vector<std::vector<int>>& i_field)
{
	m_wayFound = false;

	SearchWay(i_begin, i_end, i_field);
}

bool AlgorithmLi::WayFound()
{
	return m_wayFound;
}

AlgorithmLi::~AlgorithmLi()
{

}

std::vector<Point>& AlgorithmLi::GetFoundWay()
{
	return m_vecFoundWay;
}

void AlgorithmLi::SearchWay(Point i_pointBegin, Point i_pointEnd, std::vector<std::vector<int>>& i_field)
{
	point _begin;
	_begin.x		= i_pointBegin.x;
	_begin.y		= i_pointBegin.y;
	_begin.index	= 9;

	m_vecPassableElement.push_back(_begin); // добавляем начало в список

	bool endWay = false;

	int _indexCurrent = 10;
	
	point _current;
	_current.x = _begin.x;
	_current.y = _begin.y;
	_current.index = 10;
	
	int _iterInVector = 0;

	while (true)
	{
		_current.x		= m_vecPassableElement[_iterInVector].x;
		_current.y		= m_vecPassableElement[_iterInVector].y;
		_current.index	= m_vecPassableElement[_iterInVector].index;

		if (_current.index == _indexCurrent)
		{
			++_indexCurrent;
		}

		if (_current.x == (int)i_pointEnd.x && _current.y == (int)i_pointEnd.y)
		{
			RestoreWay();
			m_wayFound = true;

			return;
		}

		if (i_field[_current.x][_current.y - 1] == CNT_POSITION_FREE)
		{
			point _tempPoint;
			_tempPoint.x		= _current.x;
			_tempPoint.y		= _current.y - 1;
			_tempPoint.index	= _indexCurrent;
			m_vecPassableElement.push_back(_tempPoint);
			i_field[_current.x][_current.y - 1] = CNT_POSITION_BUSY_SEARCH_WAY;
		}
		if (i_field[_current.x - 1][_current.y] == CNT_POSITION_FREE)
		{
			point _tempPoint;
			_tempPoint.x = _current.x - 1;
			_tempPoint.y = _current.y;
			_tempPoint.index = _indexCurrent;
			m_vecPassableElement.push_back(_tempPoint);
			i_field[_current.x - 1][_current.y] = CNT_POSITION_BUSY_SEARCH_WAY;
		}
		if (i_field[_current.x][_current.y + 1] == CNT_POSITION_FREE)
		{
			point _tempPoint;
			_tempPoint.x = _current.x;
			_tempPoint.y = _current.y + 1;
			_tempPoint.index = _indexCurrent;
			m_vecPassableElement.push_back(_tempPoint);
			i_field[_current.x][_current.y + 1] = CNT_POSITION_BUSY_SEARCH_WAY;
		}
		if (i_field[_current.x + 1][_current.y] == CNT_POSITION_FREE)
		{
			point _tempPoint;
			_tempPoint.x = _current.x + 1;
			_tempPoint.y = _current.y;
			_tempPoint.index = _indexCurrent;
			m_vecPassableElement.push_back(_tempPoint);
			i_field[_current.x + 1][_current.y] = CNT_POSITION_BUSY_SEARCH_WAY;
		}

		++_iterInVector;
	}
}

void AlgorithmLi::RestoreWay()
{
	int _iterInVector	= m_vecPassableElement.size() - 1;
	int _indexElement	= m_vecPassableElement[_iterInVector].index;
	m_vecFoundWay.push_back(Point(m_vecPassableElement[_iterInVector].x, m_vecPassableElement[_iterInVector].y));

	int _indexInVecFoundWay = 0;

	while (_indexElement)
	{
		for (int i = 0; i < m_vecPassableElement.size(); i++)
		{
			if ((m_vecPassableElement[i].x		== m_vecFoundWay[_indexInVecFoundWay].x &&
				(m_vecPassableElement[i].y - 1	== m_vecFoundWay[_indexInVecFoundWay].y ||
				m_vecPassableElement[i].y + 1	== m_vecFoundWay[_indexInVecFoundWay].y)
				)
				||
				(m_vecPassableElement[i].y		== m_vecFoundWay[_indexInVecFoundWay].y &&
				(m_vecPassableElement[i].x - 1	== m_vecFoundWay[_indexInVecFoundWay].x ||
				m_vecPassableElement[i].x + 1	== m_vecFoundWay[_indexInVecFoundWay].x))
				)
			{
				m_vecFoundWay.push_back(Point(m_vecPassableElement[i].x, m_vecPassableElement[i].y));
				++_indexInVecFoundWay;
				_indexElement = i;
				break;
			}
		}
	}
}
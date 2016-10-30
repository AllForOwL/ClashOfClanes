#include "AlgorithmLi.h"
#include "constants.h"

const int POSITION_FREE = 0;

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

		if (_current.x == i_pointEnd.x && _current.y == i_pointEnd.y)
		{
			RestoreWay();
			m_wayFound = true;
			return;
		}

		if (i_field[_current.x][_current.y - 1] == POSITION_FREE)
		{
			point _tempPoint;
			_tempPoint.x		= _current.x;
			_tempPoint.y		= _current.y - 1;
			_tempPoint.index	= _indexCurrent;
			m_vecPassableElement.push_back(_tempPoint);
		}
		if (i_field[_current.x - 1][_current.y] == POSITION_FREE)
		{
			point _tempPoint;
			_tempPoint.x = _current.x - 1;
			_tempPoint.y = _current.y;
			_tempPoint.index = _indexCurrent;
			m_vecPassableElement.push_back(_tempPoint);
		}
		if (i_field[_current.x][_current.y + 1] == POSITION_FREE)
		{
			point _tempPoint;
			_tempPoint.x = _current.x;
			_tempPoint.y = _current.y + 1;
			_tempPoint.index = _indexCurrent;
			m_vecPassableElement.push_back(_tempPoint);
		}
		if (i_field[_current.x + 1][_current.y] == POSITION_FREE)
		{
			point _tempPoint;
			_tempPoint.x = _current.x + 1;
			_tempPoint.y = _current.y;
			_tempPoint.index = _indexCurrent;
			m_vecPassableElement.push_back(_tempPoint);
		}

		++_indexCurrent;
		++_iterInVector;
	}
}

void AlgorithmLi::RestoreWay()
{
	int _iterInVector	= m_vecPassableElement.size() - 1;
	int _indexElement	= m_vecPassableElement[_iterInVector].index;
	m_vecFoundWay.push_back(Point(m_vecPassableElement[_iterInVector].x, m_vecPassableElement[_iterInVector].y));

	--_indexElement;
	while (_indexElement > 8)
	{
		for (int i = 0; i < _iterInVector; i++)
		{
			if (m_vecPassableElement[i].index == _indexElement)
			{
				m_vecFoundWay.push_back(Point(m_vecPassableElement[i].x, m_vecPassableElement[i].y));
				--_indexElement;

				break;
				break;
			}
		}
	}

}
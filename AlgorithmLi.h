#ifndef __ALGORITHM_LI_H__
#define __ALGORITHM_LI_H__

#include "cocos2d.h"

USING_NS_CC;

class AlgorithmLi
{
public:

	struct point
	{
		int x;
		int y;
		int index;

		point() : x(0), y(0), index(0)
		{

		}
	};

	AlgorithmLi();
	AlgorithmLi(AlgorithmLi& i_AlgorithmLi);
	AlgorithmLi(Point i_begin, Point i_end, std::vector<std::vector<int>>& i_field);

	~AlgorithmLi();

	void SearchWay(Point i_pointBegin, Point i_pointEnd, std::vector<std::vector<int>>& i_field);
	void RestoreWay();
	bool WayFound();

	std::vector<Point>& GetFoundWay();

private:
	bool m_wayFound;
	std::vector<point> m_vecPassableElement;
	std::vector<Point> m_vecFoundWay;
};

#endif
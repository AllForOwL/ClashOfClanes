#ifndef __AI_DIRECTION_H__
#define __AI_DIRECTION_H__

#include "cocos2d.h"
#include "AI.h"

const int CNT_INPUT_NEURONS_WANDER = 4;
const int CNT_HIDDEN_NEURONS_WANDER = 3;
const int CNT_OUTPUT_NEURONS_WANDER = 4;

const int CNT_MAX_SAMPLES_WANDER	=	9;

USING_NS_CC;

class AIDirection : public AI
{
public:
	AIDirection();
	AIDirection(AIDirection& i_AIDirection);

	~AIDirection(){};

	virtual void Train();

	int FindAct(double i_forward, double i_back, double i_right, double i_left);

private:
	/*	1 - free, 0 - busy	*/
	typedef struct
	{
		double m_positionTop;
		double m_positionRight;
		double m_positionBottom;
		double m_positionLeft;
		double m_targetAct[CNT_OUTPUT_NEURONS_WANDER];
	} ELEMENT_WANDER;

	/* F B R L F(ou) B(ou) R(ou) L(ou) */
	static const ELEMENT_WANDER m_samples[CNT_MAX_SAMPLES_WANDER];
	static const std::vector<std::string>	m_actWander;
};

#endif
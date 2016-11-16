#ifndef __AI_DIRECTION_H__
#define __AI_DIRECTION_H__

#include "cocos2d.h"
#include "AI.h"

const int CNT_MAX_SAMPLES	=	9;

USING_NS_CC;

class AIDirection : public AI
{
public:
	AIDirection();
	AIDirection(AIDirection& i_AIDirection);

	~AIDirection();

	virtual void Train();

private:
	/*	1 - free, 0 - busy	*/
	typedef struct
	{
		double m_positionTop;
		double m_positionRight;
		double m_positionBottom;
		double m_positionLeft;
		double m_targetAct[m_outputNeurons];
	} ELEMENT;

	/* F B R L F(ou) B(ou) R(ou) L(ou) */
	static const ELEMENT m_samples[CNT_MAX_SAMPLES];
};

#endif
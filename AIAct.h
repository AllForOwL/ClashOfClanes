#ifndef __AI_ACT_H__
#define __AI_ACT_H__

#include "cocos2d.h"
#include "AI.h"

const int CNT_INPUT_HEURONS = 3;
const int CNT_HIDDEN_NEURONS = 3;
const int CNT_OUTPUT_NEURONS = 4;


const int CNT_MAX_SAMPLES	= 16;

USING_NS_CC;


class AIAct : public AI
{
public:
	AIAct();
	AIAct(AIAct& i_AIAct);

	~AIAct(){};

	virtual void Train();

	int FindAct(double i_health, double i_spear, double i_enemy);

private:

	typedef struct
	{
		double m_health;	/*2 - perfectly;	1 - good;		0 - bad;		*/
		double m_spear;		/*1 - is;							0 - not have;	*/
		double m_enemy;		/*2 - lot;			1 - little;		0 - not have;	*/
		double m_targetAct[CNT_OUTPUT_NEURONS];
	} ELEMENT;

	static const ELEMENT	m_samples[CNT_MAX_SAMPLES];
	static const std::vector<std::string>	m_act;
};

#endif
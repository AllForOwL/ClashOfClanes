#ifndef __AI_H__
#define __AI_H__

#include "cocos2d.h"

const int CNT_OUTPUT_NEURONS		= 4;
const int CNT_MAX_SAMPLES			= 16;
const int CNT_MAX_SAMPLES_WANDER	= 4;

USING_NS_CC;

class AI
{
public:
	AI();
	AI(AI& i_AI);

	void AssignRandomWeights();
	void FeedForward();
	void BackPropagate();
	int  Action(std::vector<double> i_vector);
	void Train();
	int	 FindAct(double i_health, double i_spear, double i_enemy);

	void TrainWander();
	int	 FindActWander(double i_top, double i_right, double i_bottom, double i_left);

	double Sigmoid(double i_value);
	double SigmoidDerivative(double i_value);

	~AI();

private:
	std::vector<std::vector<double>>	m_weightInputHidden;
	std::vector<std::vector<double>>	m_weightHiddenOutput;
	
	std::vector<double>	m_vectorInputs;
	std::vector<double>	m_vectorTarget;

	std::vector<double>	m_valueFunctionInLayerHidden;
	std::vector<double>	m_valueFunctionInLayerOutput;

	std::vector<double>	m_valueErrorLayerHidden;
	std::vector<double>	m_valueErrorLayerOutput;

	static const std::vector<std::string>	m_act;
	static const std::vector<std::string>	m_actWander;

	typedef struct 
	{
		double m_health;	/*2 - perfectly;	1 - good;		0 - bad;		*/
		double m_spear;		/*1 - is;							0 - not have;	*/
		double m_enemy;		/*2 - lot;			1 - little;		0 - not have;	*/
		double m_targetAct[CNT_OUTPUT_NEURONS];
	} ELEMENT;


						/*	1 - free, 0 - busy	*/
	typedef struct
	{
		double m_positionTop;
		double m_positionRight;
		double m_positionBottom;
		double m_positionLeft;
		double m_targetActWander[CNT_OUTPUT_NEURONS];
	} WANDER_ELEMENT;

	/* H S E A R W H */
	static const ELEMENT		m_samples[CNT_MAX_SAMPLES];
	
	/* F B R L F(ou) B(ou) R(ou) L(ou) */
	static const WANDER_ELEMENT m_samplesWander[CNT_MAX_SAMPLES_WANDER];
};

#endif
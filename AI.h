#ifndef __AI_H__
#define __AI_H__

#include "cocos2d.h"

const int CNT_OUTPUT_NEURONS = 4;
const int CNT_MAX_SAMPLES = 18;

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

	std::vector<std::string> m_strings;

	typedef struct 
	{
		double health;
		double knife;
		double gun;
		double enemy;
		double out[CNT_OUTPUT_NEURONS];
	} ELEMENT;

	/* H K G E A R W H */
	static const ELEMENT samples[CNT_MAX_SAMPLES];

};

#endif
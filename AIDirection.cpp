#include "AIDirection.h"

const AIDirection::ELEMENT_WANDER AIDirection::m_samples[CNT_MAX_SAMPLES_WANDER] =
{
	{ 1.0, 0.0, 0.0, 0.0, { 1.0, 0.0, 0.0, 0.0 } },
	{ 0.0, 1.0, 0.0, 0.0, { 0.0, 1.0, 0.0, 0.0 } },
	{ 0.0, 0.0, 1.0, 0.0, { 0.0, 0.0, 1.0, 0.0 } },
	{ 0.0, 0.0, 0.0, 1.0, { 0.0, 0.0, 0.0, 1.0 } },
	{ 1.0, 1.0, 0.0, 0.0, { 1.0, 0.0, 0.0, 0.0 } },
	{ 1.0, 0.0, 1.0, 0.0, { 1.0, 0.0, 0.0, 0.0 } },
	{ 1.0, 0.0, 0.0, 1.0, { 0.0, 0.0, 0.0, 0.0 } },
	{ 0.0, 1.0, 1.0, 0.0, { 0.0, 0.0, 1.0, 0.0 } },
	{ 0.0, 1.0, 0.0, 1.0, { 0.0, 0.0, 0.0, 1.0 } }
};


const std::vector<std::string> AIDirection::m_actWander	= { "Forward", "Back", "Right", "Left" };

AIDirection::AIDirection() : AI(CNT_INPUT_NEURONS_WANDER, 
								CNT_HIDDEN_NEURONS_WANDER,
								CNT_OUTPUT_NEURONS_WANDER)
{
	Train();
}

AIDirection::AIDirection(AIDirection& i_AIDirection) : AI(	CNT_INPUT_NEURONS_WANDER, 
															CNT_HIDDEN_NEURONS_WANDER,
															CNT_OUTPUT_NEURONS_WANDER)
{

}

/*virtual*/ void AIDirection::Train()
{
	int _samples = 0;
	double _err = 0.0;
	int _iterators = 0;

	AssignRandomWeights();

	while (true)
	{
		if (++_samples == CNT_MAX_SAMPLES_WANDER)
		{
			_samples = 0;
		}

		m_vectorInputs[0] = m_samples[_samples].m_positionTop;
		m_vectorInputs[1] = m_samples[_samples].m_positionRight;
		m_vectorInputs[2] = m_samples[_samples].m_positionBottom;
		m_vectorInputs[3] = m_samples[_samples].m_positionLeft;

		m_vectorTarget[0] = m_samples[_samples].m_targetAct[0];
		m_vectorTarget[1] = m_samples[_samples].m_targetAct[1];
		m_vectorTarget[2] = m_samples[_samples].m_targetAct[2];
		m_vectorTarget[3] = m_samples[_samples].m_targetAct[3];

		FeedForward();

		_err = 0.0;
		for (int i = 0; i < m_outputNeurons; i++)
		{
			_err += sqr(m_samples[_samples].m_targetAct[i] - m_valueFunctionInLayerOutput[i]);
		}
		_err *= 0.5;

		if (++_iterators == 100000)
		{
			break;
		}

		BackPropagate();
	}

	int _quentityMatches = 0;
	for (int i = 0; i < CNT_MAX_SAMPLES_WANDER; i++)
	{
		m_vectorInputs[0] = m_samples[i].m_positionTop;
		m_vectorInputs[1] = m_samples[i].m_positionRight;
		m_vectorInputs[2] = m_samples[i].m_positionBottom;
		m_vectorInputs[3] = m_samples[i].m_positionLeft;

		m_vectorTarget[0] = m_samples[i].m_targetAct[0];
		m_vectorTarget[1] = m_samples[i].m_targetAct[1];
		m_vectorTarget[2] = m_samples[i].m_targetAct[2];
		m_vectorTarget[3] = m_samples[i].m_targetAct[3];

		FeedForward();

		if (Action(m_vectorInputs) == Action(m_vectorTarget))
		{
			++_quentityMatches;
		}
	}

	int _numberAct = 0;
	m_vectorInputs[0] = 0.0; m_vectorInputs[1] = 0.0; m_vectorInputs[2] = 1.0; m_vectorInputs[3] = 1.0;
	FeedForward();
	_numberAct = Action(m_valueFunctionInLayerOutput);

	m_vectorInputs[0] = 0.0; m_vectorInputs[1] = 1.0; m_vectorInputs[2] = 0.0; m_vectorInputs[3] = 0.0;
	FeedForward();
	_numberAct = Action(m_valueFunctionInLayerOutput);

	m_vectorInputs[0] = 0.0; m_vectorInputs[1] = 1.0; m_vectorInputs[2] = 1.0; m_vectorInputs[3] = 0.0;
	FeedForward();
	_numberAct = Action(m_valueFunctionInLayerOutput);

	_numberAct = Action(m_valueFunctionInLayerOutput);

}

int AIDirection::FindAct(double i_forward, double i_back, double i_right, double i_left)
{
	m_vectorInputs[0] = i_forward; m_vectorInputs[1] = i_back; m_vectorInputs[2] = i_right; m_vectorInputs[3] = i_left;
	FeedForward();
	int _numberAct = Action(m_valueFunctionInLayerOutput);

	return _numberAct;
}
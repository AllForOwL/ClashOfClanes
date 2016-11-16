#include "AIAct.h"

const AIAct::ELEMENT AIAct::m_samples[CNT_MAX_SAMPLES] =
{
	{ 2.0, 1.0, 1.0, { 1.0, 0.0, 0.0, 0.0 } },
	{ 2.0, 1.0, 0.0, { 0.0, 0.0, 1.0, 0.0 } },
	{ 2.0, 1.0, 2.0, { 0.0, 0.0, 0.0, 1.0 } },
	{ 2.0, 0.0, 1.0, { 0.0, 0.0, 0.0, 1.0 } },
	{ 2.0, 0.0, 2.0, { 0.0, 1.0, 0.0, 0.0 } },
	{ 1.0, 1.0, 1.0, { 1.0, 0.0, 0.0, 0.0 } },
	{ 1.0, 1.0, 2.0, { 0.0, 0.0, 0.0, 1.0 } },
	{ 1.0, 1.0, 0.0, { 0.0, 0.0, 1.0, 0.0 } },
	{ 1.0, 0.0, 1.0, { 0.0, 1.0, 0.0, 0.0 } },
	{ 1.0, 0.0, 2.0, { 0.0, 1.0, 0.0, 0.0 } },
	{ 1.0, 0.0, 0.0, { 0.0, 0.0, 1.0, 0.0 } },
	{ 0.0, 1.0, 1.0, { 0.0, 1.0, 0.0, 0.0 } },
	{ 0.0, 1.0, 2.0, { 0.0, 1.0, 0.0, 0.0 } },
	{ 0.0, 1.0, 0.0, { 0.0, 0.0, 1.0, 0.0 } },
	{ 0.0, 0.0, 1.0, { 0.0, 1.0, 0.0, 0.0 } },
	{ 0.0, 0.0, 2.0, { 0.0, 1.0, 0.0, 0.0 } },
};

const std::vector<std::string> AIAct::m_act	= { "Attack", "Run", "Wander", "Hide" };

AIAct::AIAct() : AI(CNT_INPUT_HEURONS,
					CNT_HIDDEN_NEURONS,
					CNT_OUTPUT_NEURONS)
{
	Train();
}

AIAct::AIAct(AIAct& i_AIAct) : AI(	CNT_INPUT_HEURONS,
									CNT_HIDDEN_NEURONS,
									CNT_OUTPUT_NEURONS)
{

}

/*virtual*/ void AIAct::Train()
{
	double _err;
	int _sample = 0, iterations = 0;
	srand(time(NULL));
	AssignRandomWeights();
	// навчання мережі
	while (true)
	{
		if (++_sample == CNT_MAX_SAMPLES)
		{
			_sample = 0;
		}

		// задати вектор вхідних значень та значень які повинні бути на виході
		m_vectorInputs[0] = m_samples[_sample].m_health;
		m_vectorInputs[1] = m_samples[_sample].m_spear;
		m_vectorInputs[2] = m_samples[_sample].m_enemy;
		m_vectorTarget[0] = m_samples[_sample].m_targetAct[0];
		m_vectorTarget[1] = m_samples[_sample].m_targetAct[1];
		m_vectorTarget[2] = m_samples[_sample].m_targetAct[2];
		m_vectorTarget[3] = m_samples[_sample].m_targetAct[3];
		FeedForward();
		_err = 0.0;
		for (int i = 0; i < CNT_OUTPUT_NEURONS; i++)
		{
			_err += sqr((m_samples[_sample].m_targetAct[i] - m_valueFunctionInLayerOutput[i]));
		}
		_err *= 0.5;

		if (++iterations > 100000)
		{
			break;
		}
		BackPropagate();
	}
	// перевірити мережу
	for (int i = 0; i < CNT_MAX_SAMPLES; i++)
	{
		m_vectorInputs[0] = m_samples[i].m_health;
		m_vectorInputs[1] = m_samples[i].m_spear;
		m_vectorInputs[2] = m_samples[i].m_enemy;
		m_vectorTarget[0] = m_samples[i].m_targetAct[0];
		m_vectorTarget[1] = m_samples[i].m_targetAct[1];
		m_vectorTarget[2] = m_samples[i].m_targetAct[2];
		m_vectorTarget[3] = m_samples[i].m_targetAct[3];

		FeedForward();

		int _quentityConcurrence = 0;
		if (Action(m_valueFunctionInLayerOutput) == Action(m_vectorTarget))
		{
			++_quentityConcurrence;
		}
	}

	// тест
	int _numberAct = 0;
	m_vectorInputs[0] = 0.0; m_vectorInputs[1] = 0.0; m_vectorInputs[2] = 0.0;
	FeedForward();
	_numberAct = Action(m_valueFunctionInLayerOutput);

	m_vectorInputs[0] = 1.0; m_vectorInputs[1] = 1.0; m_vectorInputs[2] = 1.0;
	FeedForward();
	_numberAct = Action(m_valueFunctionInLayerOutput);

	m_vectorInputs[0] = 0.0; m_vectorInputs[1] = 0.0; m_vectorInputs[2] = 0.0;
	FeedForward();
	_numberAct = Action(m_valueFunctionInLayerOutput);

	m_vectorInputs[0] = 0.0; m_vectorInputs[1] = 1.0; m_vectorInputs[2] = 1.0;
	FeedForward();
	_numberAct = Action(m_valueFunctionInLayerOutput);

	m_vectorInputs[0] = 2.0; m_vectorInputs[1] = 0.0; m_vectorInputs[2] = 1.0;
	FeedForward();
	_numberAct = Action(m_valueFunctionInLayerOutput);

	m_vectorInputs[0] = 2.0; m_vectorInputs[1] = 1.0; m_vectorInputs[2] = 0.0;
	FeedForward();
	_numberAct = Action(m_valueFunctionInLayerOutput);

	m_vectorInputs[0] = 0.0; m_vectorInputs[1] = 1.0; m_vectorInputs[2] = 0.0;
	FeedForward();
	_numberAct = Action(m_valueFunctionInLayerOutput);
}

int AIAct::FindAct(double i_health, double i_spear, double i_enemy)
{
	m_vectorInputs[0] = i_health; m_vectorInputs[1] = i_spear; m_vectorInputs[2] = i_enemy;
	FeedForward();
	int _numberAct = Action(m_valueFunctionInLayerOutput);

	return _numberAct;
}
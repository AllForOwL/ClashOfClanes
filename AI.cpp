#include "AI.h"
#include "constants.h"

const int CNT_INPUT_NEURONS		= 3;
const int CNT_HIDDEN_NEURONS	= 3;


#define LEARN_RATE 0.2 // ���������� ��������
#define RAND_WEIGHT ( ((float)rand() / (float)RAND_MAX) - 0.5)
#define sqr(x) ((x) * (x))

const AI::ELEMENT AI::m_samples[CNT_MAX_SAMPLES] =
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

const std::vector<std::string> AI::m_act = { "Attack", "Run", "Wander", "Hide" };

AI::AI()
{
	m_weightInputHidden.resize(CNT_INPUT_NEURONS + 1);
	for (int i = 0; i < CNT_INPUT_NEURONS + 1; i++)
	{
		m_weightInputHidden[i].resize(CNT_HIDDEN_NEURONS);
	}

	m_weightHiddenOutput.resize(CNT_HIDDEN_NEURONS + 1);
	for (int i = 0; i < CNT_HIDDEN_NEURONS + 1; i++)
	{
		m_weightHiddenOutput[i].resize(CNT_OUTPUT_NEURONS);
	}

	m_valueFunctionInLayerHidden.resize(CNT_HIDDEN_NEURONS);
	m_valueFunctionInLayerOutput.resize(CNT_OUTPUT_NEURONS);

	m_valueErrorLayerHidden.resize(CNT_HIDDEN_NEURONS);
	m_valueErrorLayerOutput.resize(CNT_OUTPUT_NEURONS);

	m_vectorInputs.resize(CNT_INPUT_NEURONS);
	m_vectorTarget.resize(CNT_OUTPUT_NEURONS);
}

AI::AI(AI& i_AI)
{

}

/*	������ ���� ��:
		- ������� �������� ���� �� ��������� ��������� ����;
		- ��������� ��������� ���� �� ��������� ��������� ����;
*/
void AI::AssignRandomWeights()
{
	// �'������� ������ ����� � ���� ��������� ��������� ���� �������� ����(��������� �����(-0.5; 0.5))
	for (int i = 0; i < CNT_INPUT_NEURONS + 1; i++) 
	{
		for (int j = 0; j < CNT_HIDDEN_NEURONS; j++) 
		{
			m_weightInputHidden[i][j] = RAND_WEIGHT;
		}
	}
	// �'������� ������� ��������� ���� � ���� ��������� ��������� ���� �������� ����(��������� �����(-0.5; 0.5))
	for (int i = 0; i < CNT_HIDDEN_NEURONS + 1; i++) 
	{
		for (int j = 0; j < CNT_OUTPUT_NEURONS; j++) 
		{
			m_weightHiddenOutput[i][j] = RAND_WEIGHT;
		}
	}
}

// ���������� �������(������� ���������) �� ���� ������� �� ���������� ����(�����, �������)
double AI::Sigmoid(double val)
{
	return (1.0 / (1.0 + exp(-val)));
}

// ������� ��� ��������� ��� ������� ��������� ����
double AI::SigmoidDerivative(double i_value)
{
	return (i_value * (1.0 - i_value));
}

/*	���������� �������� ������� �����:
		- � ������� ����� � ������� ��������� ����;
		- � ������� ��������� ���� � ������� ��������� ����;
*/
void AI::FeedForward()
{
	double _sum;
	// ���������� ���� ����� � ������� ����� � ������� ��������� ����
	for (int i = 0; i < CNT_HIDDEN_NEURONS; i++) 
	{
		_sum = 0.0;
		for (int j = 0; j < CNT_INPUT_NEURONS; j++) 
		{
			_sum += m_vectorInputs[j] * m_weightInputHidden[j][i];	// ������� �������� ������ ����� � ���� �� ������� ������ � 
																	// �������� ��������� ����
		}
		_sum += m_weightInputHidden[CNT_INPUT_NEURONS][i];	// �������� ������� 
		m_valueFunctionInLayerHidden[i] = Sigmoid(_sum);	// �������� ������ ���� ����
	}
	// ���������� ���� ����� � ������� ��������� ���� � ������� ��������� ����
	for (int i = 0; i < CNT_OUTPUT_NEURONS; i++) 
	{
		_sum = 0.0;
		for (int j = 0; j < CNT_HIDDEN_NEURONS; j++) 
		{
			_sum += m_valueFunctionInLayerHidden[j] * m_weightHiddenOutput[j][i];
		}
		_sum += m_weightHiddenOutput[CNT_HIDDEN_NEURONS][i];	// �������� �������
		m_valueFunctionInLayerOutput[i] = Sigmoid(_sum);		// �������� ������ ���� ����
	}
}

// ������� ��������� �������
void AI::BackPropagate()
{
	// ���������� ������� ��� ��������� ����
	for (int i = 0; i < CNT_OUTPUT_NEURONS; i++) 
	{
		m_valueErrorLayerOutput[i] = (m_vectorTarget[i] - m_valueFunctionInLayerOutput[i]) *
												SigmoidDerivative(m_valueFunctionInLayerOutput[i]);
	}
	// ���������� ������� ��� ��������� ����
	for (int i = 0; i < CNT_HIDDEN_NEURONS; i++) 
	{
		m_valueErrorLayerHidden[i] = 0.0;
		for (int j = 0; j < CNT_OUTPUT_NEURONS; j++) 
		{
			m_valueErrorLayerHidden[i] += m_valueErrorLayerOutput[j] * m_weightHiddenOutput[i][j];
		}
		m_valueErrorLayerHidden[i] *= SigmoidDerivative(m_valueFunctionInLayerHidden[i]);
	}
	// �������� ���� ��� ��������� ����
	for (int i = 0; i < CNT_OUTPUT_NEURONS; i++) 
	{
		for (int j = 0; j < CNT_HIDDEN_NEURONS; j++) 
		{
			m_weightHiddenOutput[j][i] += (LEARN_RATE * m_valueErrorLayerOutput[i] * m_valueFunctionInLayerHidden[j]);
		}
		// �������� �������
		m_weightHiddenOutput[CNT_HIDDEN_NEURONS][i] += (LEARN_RATE * m_valueErrorLayerOutput[i]);
	}
	// �������� ���� ��� ��������� ����
	for (int i = 0; i < CNT_HIDDEN_NEURONS; i++) 
	{
		for (int j = 0; j < CNT_INPUT_NEURONS; j++) 
		{
			m_weightInputHidden[j][i] += (LEARN_RATE * m_valueErrorLayerHidden[i] * m_vectorInputs[j]);
		}
		// �������� �������
		m_weightInputHidden[CNT_INPUT_NEURONS][i] += (LEARN_RATE * m_valueErrorLayerHidden[i]);
	}
}

int AI::Action(std::vector<double> i_vector)
{
	double _max;
	int _indexWeightMaxNeuron = 0;

	_max = i_vector[_indexWeightMaxNeuron];
	for (int i = 1; i < CNT_OUTPUT_NEURONS; i++) 
	{
		if (i_vector[i] > _max) 
		{
			_max = i_vector[i]; 
			_indexWeightMaxNeuron = i;
		}
	}
	return(_indexWeightMaxNeuron);
}

void AI::Train()
{
	double _err;
	int _sample = 0, iterations = 0;
	srand(time(NULL));
	AssignRandomWeights();
	// �������� �����
	while (1) 
	{
		if (++_sample == CNT_MAX_SAMPLES)
		{
			_sample = 0;
		}
		
		// ������ ������ ������� ������� �� ������� �� ������ ���� �� �����
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
	// ��������� ������
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
	
	// ����
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

int AI::FindAct(double i_health, double i_spear, double i_enemy)
{
	int _numberAct = 0;
	m_vectorInputs[0] = i_health; m_vectorInputs[1] = i_spear; m_vectorInputs[2] = i_enemy;
	FeedForward();
	_numberAct = Action(m_valueFunctionInLayerOutput);

	return _numberAct;
}

AI::~AI()
{
	CCLOG("Destructor AI");
}


/*
	Tasks on 10:11:2016
		+ good understand algorithm;
		+ optimize for knight;

	Tasks on 11:11:2016
		- create factory for enemy;
		- create enemy;
		- execute AI in game;
*/
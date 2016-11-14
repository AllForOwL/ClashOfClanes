#include "AI.h"

const int CNT_INPUT_NEURONS		= 3;
const int CNT_HIDDEN_NEURONS	= 3;

const int CNT_INPUT_NEURONS_WANDER = 4;

#define LEARN_RATE 0.2 // коефіцієнт навчання
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

const AI::WANDER_ELEMENT AI::m_samplesWander[CNT_MAX_SAMPLES_WANDER] =
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


const std::vector<std::string> AI::m_act		= { "Attack", "Run", "Wander", "Hide" };
const std::vector<std::string> AI::m_actWander	= { "Forward", "Back", "Right", "Left" };

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

/*	Задати вагу між:
		- клітками вхідного шару та нейронами схованого шару;
		- нейронами схованого шару та нейронами вихідного шару;
*/
void AI::AssignRandomWeights()
{
	// з'єднанню вхідної клітки з усіма нейронами схованого шару задається вага(випадкове число(-0.5; 0.5))
	for (int i = 0; i < CNT_INPUT_NEURONS + 1; i++) 
	{
		for (int j = 0; j < CNT_HIDDEN_NEURONS; j++) 
		{
			m_weightInputHidden[i][j] = RAND_WEIGHT;
		}
	}
	// з'єднанню нейрона схованого шару з усіма нейронами вихідного шару задається вага(випадкове число(-0.5; 0.5))
	for (int i = 0; i < CNT_HIDDEN_NEURONS + 1; i++) 
	{
		for (int j = 0; j < CNT_OUTPUT_NEURONS; j++) 
		{
			m_weightHiddenOutput[i][j] = RAND_WEIGHT;
		}
	}
}

// Обчислення сигмоіда(функція активації) від суми добутків між елементами шарів(кліток, нейронів)
double AI::Sigmoid(double val)
{
	return (1.0 / (1.0 + exp(-val)));
}

// функція для обрахунку для нейронів схованого шару
double AI::SigmoidDerivative(double i_value)
{
	return (i_value * (1.0 - i_value));
}

/*	Обчислення значення функцій входу:
		- з вхідних кліток в нейрони схованого шару;
		- з нейронів схованого шару в нейрони вихідного шару;
*/
void AI::FeedForward()
{
	double _sum;
	// обрахувати вагу входу з вхідних кліток в нейрони схованого шару
	for (int i = 0; i < CNT_HIDDEN_NEURONS; i++) 
	{
		_sum = 0.0;
		for (int j = 0; j < CNT_INPUT_NEURONS; j++) 
		{
			_sum += m_vectorInputs[j] * m_weightInputHidden[j][i];	// добуток значення вхідної клітки і ваги між вхідною кліткою і 
																	// нейроном схованого шару
		}
		_sum += m_weightInputHidden[CNT_INPUT_NEURONS][i];	// добавити зміщення 
		m_valueFunctionInLayerHidden[i] = Sigmoid(_sum);	// обчислює сигмоід даної суми
	}
	// обрахувати вагу входу з нейронів схованого шару в нейрони вихідного шару
	for (int i = 0; i < CNT_OUTPUT_NEURONS; i++) 
	{
		_sum = 0.0;
		for (int j = 0; j < CNT_HIDDEN_NEURONS; j++) 
		{
			_sum += m_valueFunctionInLayerHidden[j] * m_weightHiddenOutput[j][i];
		}
		_sum += m_weightHiddenOutput[CNT_HIDDEN_NEURONS][i];	// добавити зміщення
		m_valueFunctionInLayerOutput[i] = Sigmoid(_sum);		// обчислює сигмоід даної суми
	}
}

// зворотнє поширення помилки
void AI::BackPropagate()
{
	// обрахувати помилку для вихідного шару
	for (int i = 0; i < CNT_OUTPUT_NEURONS; i++) 
	{
		m_valueErrorLayerOutput[i] = (m_vectorTarget[i] - m_valueFunctionInLayerOutput[i]) *
												SigmoidDerivative(m_valueFunctionInLayerOutput[i]);
	}
	// обрахувати помилку для схованого шару
	for (int i = 0; i < CNT_HIDDEN_NEURONS; i++) 
	{
		m_valueErrorLayerHidden[i] = 0.0;
		for (int j = 0; j < CNT_OUTPUT_NEURONS; j++) 
		{
			m_valueErrorLayerHidden[i] += m_valueErrorLayerOutput[j] * m_weightHiddenOutput[i][j];
		}
		m_valueErrorLayerHidden[i] *= SigmoidDerivative(m_valueFunctionInLayerHidden[i]);
	}
	// обновити ваги для вихідного шару
	for (int i = 0; i < CNT_OUTPUT_NEURONS; i++) 
	{
		for (int j = 0; j < CNT_HIDDEN_NEURONS; j++) 
		{
			m_weightHiddenOutput[j][i] += (LEARN_RATE * m_valueErrorLayerOutput[i] * m_valueFunctionInLayerHidden[j]);
		}
		// обновити зміщення
		m_weightHiddenOutput[CNT_HIDDEN_NEURONS][i] += (LEARN_RATE * m_valueErrorLayerOutput[i]);
	}
	// обновити ваги для схованого шару
	for (int i = 0; i < CNT_HIDDEN_NEURONS; i++) 
	{
		for (int j = 0; j < CNT_INPUT_NEURONS; j++) 
		{
			m_weightInputHidden[j][i] += (LEARN_RATE * m_valueErrorLayerHidden[i] * m_vectorInputs[j]);
		}
		// обновити зміщення
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

int AI::FindAct(double i_health, double i_spear, double i_enemy)
{
	int _numberAct = 0;
	m_vectorInputs[0] = i_health; m_vectorInputs[1] = i_spear; m_vectorInputs[2] = i_enemy;
	FeedForward();
	_numberAct = Action(m_valueFunctionInLayerOutput);

	return _numberAct;
}

void AI::TrainWander()
{
	int _samples	= 0;
	double _err		= 0.0;
	int _iterators	= 0;

	AssignRandomWeights();
	
	m_vectorInputs.resize(CNT_INPUT_NEURONS_WANDER);
	while (true)
	{
		if (++_samples == CNT_MAX_SAMPLES_WANDER)
		{
			_samples = 0;
		}

		m_vectorInputs[0] = m_samplesWander[_samples].m_positionTop;
		m_vectorInputs[1] = m_samplesWander[_samples].m_positionRight;
		m_vectorInputs[2] = m_samplesWander[_samples].m_positionBottom;
		m_vectorInputs[3] = m_samplesWander[_samples].m_positionLeft;

		m_vectorTarget[0] = m_samplesWander[_samples].m_targetActWander[0];
		m_vectorTarget[1] = m_samplesWander[_samples].m_targetActWander[1];
		m_vectorTarget[2] = m_samplesWander[_samples].m_targetActWander[2];
		m_vectorTarget[3] = m_samplesWander[_samples].m_targetActWander[3];

		FeedForward();

		_err = 0.0;
		for (int i = 0; i < CNT_OUTPUT_NEURONS; i++)
		{
			_err += sqr(m_samplesWander[_samples].m_targetActWander[i] - m_valueFunctionInLayerOutput[i]);
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
		m_vectorInputs[0] = m_samplesWander[i].m_positionTop;
		m_vectorInputs[1] = m_samplesWander[i].m_positionRight;
		m_vectorInputs[2] = m_samplesWander[i].m_positionBottom;
		m_vectorInputs[3] = m_samplesWander[i].m_positionLeft;

		m_vectorTarget[0] = m_samplesWander[i].m_targetActWander[0];
		m_vectorTarget[1] = m_samplesWander[i].m_targetActWander[1];
		m_vectorTarget[2] = m_samplesWander[i].m_targetActWander[2];
		m_vectorTarget[3] = m_samplesWander[i].m_targetActWander[3];

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

int AI::FindActWander(double i_top, double i_right, double i_bottom, double i_left)
{
	int _numberActWander = 0;

	m_vectorInputs[0] = i_top; m_vectorInputs[1] = i_right; m_vectorInputs[2] = i_bottom; m_vectorInputs[3] = i_left;
	FeedForward();
	_numberActWander = Action(m_valueFunctionInLayerOutput);

	return _numberActWander;
}

AI::~AI()
{
	CCLOG("Destructor AI");
}

/*
	Tasks on 10:11:2016
		+ good understand algorithm;
		+ optimize for knight;

	Tasks on 11:11:2016					!-!-!-(Day Enemy!!!!!)-!-!-!
		+ create factory for enemy(warrior and machine);
		// create manager factory for enemy????;(not need)
		+ create enemy;
		
		|
		|			Tasks on 12:11:2016
  ------|------		step for execute AI in game:
		|				+ fill region for each objects;
		|				+ need add AI for act---> Wander <---;

		Tasks on 13:11:2016
			+ Execute AI;

		Tasks on 14:11:2016
			+ add AI for all objects;

		Tasks on 15:11:2016
			- create and realize possibility add for knight tasks ():
				+ list tasks:
					- find gold;
					- find tree;
					- find oil;
				- add on map region from recources for execute tasks:
					+ fill region for each type resources;
					- show tasks when click on hero;
				- each hero responsible zone on map(gold, tree and etc.);
			- add act : 
			{
				- attack;
				- run;
				- hide;
				- wander;
			};
			- save game  write mapCoordinate in XML (need read about best solution) /;
*/
#include "AI.h"
#include "constants.h"

const int CNT_INPUT_NEURONS		= 4;
const int CNT_HIDDEN_NEURONS	= 3;


#define LEARN_RATE 0.2 /* Коэффициент обучения */
#define RAND_WEIGHT ( ((float)rand() / (float)RAND_MAX) - 0.5)
#define sqr(x) ((x) * (x))

AI::AI()
{
	m_weightInputHidden.resize(CNT_INPUT_NEURONS);
	for (int i = 0; i < CNT_INPUT_NEURONS; i++)
	{
		m_weightInputHidden[i].resize(CNT_HIDDEN_NEURONS);
	}

	m_weightHiddenOutput.resize(CNT_HIDDEN_NEURONS);
	for (int i = 0; i < CNT_HIDDEN_NEURONS; i++)
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

//  set weight between layers network
void AI::AssignRandomWeights()
{
	for (int i = 0; i < CNT_INPUT_NEURONS + 1; i++) 
	{
		for (int j = 0; j < CNT_HIDDEN_NEURONS; j++) 
		{
			m_weightInputHidden[i][j] = RAND_WEIGHT;
		}
	}
	for (int i = 0; i < CNT_HIDDEN_NEURONS + 1; i++) 
	{
		for (int j = 0; j < CNT_OUTPUT_NEURONS; j++) 
		{
			m_weightHiddenOutput[i][j] = RAND_WEIGHT;
		}
	}
}

double AI::Sigmoid(double val)
{
	return (1.0 / (1.0 + exp(-val)));
}
double AI::SigmoidDerivative(double i_value)
{
	return (i_value * (1.0 - i_value));
}

// обчислення значення функцій входу для схованого і вихідного шару
void AI::FeedForward()
{
	double _sum;
	/* Вычислить вход в скрытый слой */
	for (int i = 0; i < CNT_HIDDEN_NEURONS; i++) 
	{
		_sum = 0.0;
		for (int j = 0; j < CNT_INPUT_NEURONS; j++) 
		{
			_sum += m_vectorInputs[j] * m_weightInputHidden[j][i];
		}
		/* Добавить смещение */
		_sum += m_weightInputHidden[CNT_INPUT_NEURONS][i];
		m_valueFunctionInLayerHidden[i] = Sigmoid(_sum);
	}
	/* Вычислить вход в выходной слой */
	for (int i = 0; i < CNT_OUTPUT_NEURONS; i++) 
	{
		_sum = 0.0;
		for (int j = 0; j < CNT_HIDDEN_NEURONS; j++) 
		{
			_sum += m_valueFunctionInLayerHidden[j] * m_weightHiddenOutput[j][i];
		}
		/* Добавить смещение */
		_sum += m_weightHiddenOutput[CNT_HIDDEN_NEURONS][i];
		m_valueFunctionInLayerOutput[i] = Sigmoid(_sum);
	}
}

// зворотнє поширення помилки
void AI::BackPropagate()
{
	/* Вычислить ошибку выходного слоя (шаг 3 для выходных ячеек) */
	for (int i = 0; i < CNT_OUTPUT_NEURONS; i++) 
	{
		m_valueErrorLayerOutput[i] = (m_vectorTarget[i] - m_valueFunctionInLayerOutput[i]) *
												SigmoidDerivative(m_valueFunctionInLayerOutput[i]);
	}
	/* Вычислить ошибку скрытого слоя (шаг 3 для скрытого слоя) */
	for (int i = 0; i < CNT_HIDDEN_NEURONS; i++) 
	{
		m_valueErrorLayerHidden[i] = 0.0;
		for (int j = 0; j < CNT_OUTPUT_NEURONS; j++) 
		{
			m_valueErrorLayerHidden[i] += m_valueErrorLayerOutput[j] * m_weightHiddenOutput[i][j];
		}
		m_valueErrorLayerHidden[i] *= SigmoidDerivative(m_valueFunctionInLayerHidden[i]);
	}
	/* Обновить веса для выходного слоя (шаг 4 для выходных ячеек) */
	for (int i = 0; i < CNT_OUTPUT_NEURONS; i++) 
	{
		for (int j = 0; j < CNT_HIDDEN_NEURONS; j++) 
		{
			m_weightHiddenOutput[j][i] += (LEARN_RATE * m_valueErrorLayerOutput[i] * m_valueFunctionInLayerHidden[j]);
		}
		/* Обновить смещение */
		m_weightHiddenOutput[CNT_HIDDEN_NEURONS][i] += (LEARN_RATE * m_valueErrorLayerOutput[i]);
	}
	/* Обновить веса для скрытого слоя (шаг 4 для скрытого слоя) */
	for (int i = 0; i < CNT_HIDDEN_NEURONS; i++) 
	{
		for (int j = 0; j < CNT_INPUT_NEURONS; j++) 
		{
			m_weightInputHidden[j][i] += (LEARN_RATE * m_valueErrorLayerHidden[i] * m_vectorInputs[j]);
		}
		/* Обновить смещение */
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
	int sum = 0;
	//out = fopen("stats.txt", "w");
	/* Инициализировать генератор случайных чисел */
	srand(time(NULL));
	AssignRandomWeights();
	/* Обучить сеть */
	while (1) 
	{
		if (++_sample == CNT_MAX_SAMPLES) _sample = 0;
		
		m_vectorInputs[0] = samples[_sample].health;
		m_vectorInputs[1] = samples[_sample].knife;
		m_vectorInputs[2] = samples[_sample].gun;
		m_vectorInputs[3] = samples[_sample].enemy;
		m_vectorTarget[0] = samples[_sample].out[0];
		m_vectorTarget[1] = samples[_sample].out[1];
		m_vectorTarget[2] = samples[_sample].out[2];
		m_vectorTarget[3] = samples[_sample].out[3];
		FeedForward();
		_err = 0.0;
		for (int i = 0; i < CNT_OUTPUT_NEURONS; i++) 
		{
			_err += sqr((samples[_sample].out[i] - m_valueFunctionInLayerOutput[i]));
		}
		_err = 0.5 * _err;
	
		if (iterations++ > 100000) break;
		BackPropagate();
	}
	/* Проверить сеть */
	for (int i = 0; i < CNT_MAX_SAMPLES; i++) 
	{
		m_vectorInputs[0] = samples[i].health;
		m_vectorInputs[1] = samples[i].knife;
		m_vectorInputs[2] = samples[i].gun;
		m_vectorInputs[3] = samples[i].enemy;
		m_vectorTarget[0] = samples[i].out[0];
		m_vectorTarget[1] = samples[i].out[1];
		m_vectorTarget[2] = samples[i].out[2];
		m_vectorTarget[3] = samples[i].out[3];
		FeedForward();
		if (Action(m_valueFunctionInLayerOutput) != Action(m_vectorTarget)) 
		{
			m_vectorInputs[0], m_vectorInputs[1], m_vectorInputs[2], m_vectorInputs[3],
				strings[Action(m_valueFunctionInLayerOutput)], strings[Action(m_vectorTarget)];
		}
		else 
		{
			sum++;
		}
	}
	/* Выполнение тестов */
	/* Здоровье Нож Пистолет Враг*/
	m_vectorInputs[0] = 2.0; m_vectorInputs[1] = 1.0; m_vectorInputs[2] = 1.0; m_vectorInputs[3] = 1.0;
	FeedForward();

	m_vectorInputs[0] = 1.0; m_vectorInputs[1] = 1.0; m_vectorInputs[2] = 1.0; m_vectorInputs[3] = 2.0;
	FeedForward();
	
	m_vectorInputs[0] = 0.0; m_vectorInputs[1] = 0.0; m_vectorInputs[2] = 0.0; m_vectorInputs[3] = 0.0;
	FeedForward();
	
	m_vectorInputs[0] = 0.0; m_vectorInputs[1] = 1.0; m_vectorInputs[2] = 1.0; m_vectorInputs[3] = 1.0;
	FeedForward();
	
	m_vectorInputs[0] = 2.0; m_vectorInputs[1] = 0.0; m_vectorInputs[2] = 1.0; m_vectorInputs[3] = 3.0;
	FeedForward();
	
	m_vectorInputs[0] = 2.0; m_vectorInputs[1] = 1.0; m_vectorInputs[2] = 0.0; m_vectorInputs[3] = 3.0;
	FeedForward();
	
	m_vectorInputs[0] = 0.0; m_vectorInputs[1] = 1.0; m_vectorInputs[2] = 0.0; m_vectorInputs[3] = 3.0;
	FeedForward();
	
	//fclose(out);
}

AI::~AI()
{
	CCLOG("Destructor AI");
}
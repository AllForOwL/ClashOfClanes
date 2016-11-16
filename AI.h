#ifndef __AI_H__
#define __AI_H__

#include "cocos2d.h"

#define LEARN_RATE 0.2 // коефіцієнт навчання
#define RAND_WEIGHT ( ((float)rand() / (float)RAND_MAX) - 0.5)
#define sqr(x) ((x) * (x))

USING_NS_CC;

class AI
{
public:
	AI(int i_inputNeurons, int i_hiddenNeurons, int i_outputNeurons)
	{
		m_inputNeurons	=	i_inputNeurons;
		m_hiddenNeurons	=	i_hiddenNeurons;
		m_outputNeurons	=	i_outputNeurons;

		m_weightInputHidden.resize(m_inputNeurons + 1);
		for (int i = 0; i < m_inputNeurons + 1; i++)
		{
			m_weightInputHidden[i].resize(m_inputNeurons);
		}

		m_weightHiddenOutput.resize(m_hiddenNeurons + 1);
		for (int i = 0; i < m_hiddenNeurons + 1; i++)
		{
			m_weightHiddenOutput[i].resize(m_outputNeurons);
		}

		m_valueFunctionInLayerHidden.resize(m_hiddenNeurons);
		m_valueFunctionInLayerOutput.resize(m_outputNeurons);

		m_valueErrorLayerHidden.resize(m_hiddenNeurons);
		m_valueErrorLayerOutput.resize(m_outputNeurons);

		m_vectorInputs.resize(m_inputNeurons);
		m_vectorTarget.resize(m_outputNeurons);
	}

	AI(AI& i_AI);

	void AssignRandomWeights()
	{
		// з'єднанню вхідної клітки з усіма нейронами схованого шару задається вага(випадкове число(-0.5; 0.5))
		for (int i = 0; i < m_inputNeurons + 1; i++)
		{
			for (int j = 0; j < m_hiddenNeurons; j++)
			{
				m_weightInputHidden[i][j] = RAND_WEIGHT;
			}
		}
		// з'єднанню нейрона схованого шару з усіма нейронами вихідного шару задається вага(випадкове число(-0.5; 0.5))
		for (int i = 0; i < m_hiddenNeurons + 1; i++)
		{
			for (int j = 0; j < m_outputNeurons; j++)
			{
				m_weightHiddenOutput[i][j] = RAND_WEIGHT;
			}
		}

	}

	void FeedForward()
	{
		double _sum;
		// обрахувати вагу входу з вхідних кліток в нейрони схованого шару
		for (int i = 0; i < m_hiddenNeurons; i++)
		{
			_sum = 0.0;
			for (int j = 0; j < m_inputNeurons; j++)
			{
				_sum += m_vectorInputs[j] * m_weightInputHidden[j][i];	// добуток значення вхідної клітки і ваги між вхідною кліткою і 
				// нейроном схованого шару
			}
			_sum += m_weightInputHidden[m_inputNeurons][i];	// добавити зміщення 
			m_valueFunctionInLayerHidden[i] = Sigmoid(_sum);	// обчислює сигмоід даної суми
		}
		// обрахувати вагу входу з нейронів схованого шару в нейрони вихідного шару
		for (int i = 0; i < m_outputNeurons; i++)
		{
			_sum = 0.0;
			for (int j = 0; j < m_hiddenNeurons; j++)
			{
				_sum += m_valueFunctionInLayerHidden[j] * m_weightHiddenOutput[j][i];
			}
			_sum += m_weightHiddenOutput[m_hiddenNeurons][i];	// добавити зміщення
			m_valueFunctionInLayerOutput[i] = Sigmoid(_sum);		// обчислює сигмоід даної суми
		}

	}

	void BackPropagate()
	{
		// обрахувати помилку для вихідного шару
		for (int i = 0; i < m_outputNeurons; i++)
		{
			m_valueErrorLayerOutput[i] = (m_vectorTarget[i] - m_valueFunctionInLayerOutput[i]) *
				SigmoidDerivative(m_valueFunctionInLayerOutput[i]);
		}
		// обрахувати помилку для схованого шару
		for (int i = 0; i < m_hiddenNeurons; i++)
		{
			m_valueErrorLayerHidden[i] = 0.0;
			for (int j = 0; j < m_outputNeurons; j++)
			{
				m_valueErrorLayerHidden[i] += m_valueErrorLayerOutput[j] * m_weightHiddenOutput[i][j];
			}
			m_valueErrorLayerHidden[i] *= SigmoidDerivative(m_valueFunctionInLayerHidden[i]);
		}
		// обновити ваги для вихідного шару
		for (int i = 0; i < m_outputNeurons; i++)
		{
			for (int j = 0; j < m_hiddenNeurons; j++)
			{
				m_weightHiddenOutput[j][i] += (LEARN_RATE * m_valueErrorLayerOutput[i] * m_valueFunctionInLayerHidden[j]);
			}
			// обновити зміщення
			m_weightHiddenOutput[m_hiddenNeurons][i] += (LEARN_RATE * m_valueErrorLayerOutput[i]);
		}
		// обновити ваги для схованого шару
		for (int i = 0; i < m_hiddenNeurons; i++)
		{
			for (int j = 0; j < m_inputNeurons; j++)
			{
				m_weightInputHidden[j][i] += (LEARN_RATE * m_valueErrorLayerHidden[i] * m_vectorInputs[j]);
			}
			// обновити зміщення
			m_weightInputHidden[m_inputNeurons][i] += (LEARN_RATE * m_valueErrorLayerHidden[i]);
		}
	}

	int  Action(std::vector<double> i_vector)
	{
		double _max;
		int _indexWeightMaxNeuron = 0;

		_max = i_vector[_indexWeightMaxNeuron];
		for (int i = 1; i < m_outputNeurons; i++)
		{
			if (i_vector[i] > _max)
			{
				_max = i_vector[i];
				_indexWeightMaxNeuron = i;
			}
		}
		return(_indexWeightMaxNeuron);
	}

	virtual void Train() = 0;

	double Sigmoid(double i_value)
	{
		return (1.0 / (1.0 + exp(-i_value)));
	}

	double SigmoidDerivative(double i_value)
	{
		return (i_value * (1.0 - i_value));
	}

	virtual ~AI();

protected:
	std::vector<std::vector<double>>	m_weightInputHidden;
	std::vector<std::vector<double>>	m_weightHiddenOutput;
	
	std::vector<double>	m_vectorInputs;
	std::vector<double>	m_vectorTarget;

	std::vector<double>	m_valueFunctionInLayerHidden;
	std::vector<double>	m_valueFunctionInLayerOutput;

	std::vector<double>	m_valueErrorLayerHidden;
	std::vector<double>	m_valueErrorLayerOutput;

	static const std::vector<std::string>	m_act;

	int	m_inputNeurons;
	int m_hiddenNeurons;
	int m_outputNeurons;
};

#endif
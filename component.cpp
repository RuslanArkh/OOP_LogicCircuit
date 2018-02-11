#include "component.h"
#include "inputportelement.h"
#include "unaryelement.h"
#include "multiargelement.h"

#include <cmath>
#include <sstream>

Component::Component(ComponentType _CompType)
	: m_CompType(_CompType)
{
}

Component::Component(ComponentType _CompType,
	std::string const & _inputPortNames,
	std::string const & _outputPortNames)
	: m_CompType(_CompType)
{

	std::vector<std::string> resultIn, resultOut;

	std::istringstream iss(_inputPortNames), oss(_outputPortNames);
	for (std::string token; std::getline(iss, token, ' ');)
		resultIn.push_back(std::move(token));

	for (std::string token; std::getline(oss, token, ' ');)
		resultOut.push_back(std::move(token));

	if (IsValid(resultIn.size(), resultOut.size()))
	{
		switch (m_CompType)
		{
		case MUX:
			MakeMUX(resultIn, resultOut);
			break;
		}
	}
}

bool Component::IsValid(int _inputSize, int _outputSize)
{
	bool isvalid = true;
	switch (m_CompType)
	{
		//	По умолчанию мультиплексор создается без стробирующего входа
		//	Только функция  , работающая только для мультиплексоров может добавить стробирующий вход.
	case ComponentType::MUX:
		if ((pow(2, (int)log2(_inputSize)) + log2(_inputSize) + 1) == _inputSize ||
			_outputSize != 1)
			isvalid = false;
		break;
	default:
		break;
	}

	return isvalid;
}

void Component::SetInput(std::string const & _portName, bool _value)
{
	m_inPorts.find(_portName)->second.get()->SetPortState(_value);
}

void Component::ShowPort(std::string const & _portName, std::ostream & _o)
{

	if (m_outPorts.find(_portName)->second != nullptr)
		_o << m_outPorts.find(_portName)->second.get()->getValue() << "\n";
	else
		_o << "port does not exist\n";
}

void Component::addV(std::string const & _v, bool _state)
{

	if (!V)
	{
		V = true;
		m_inPorts[_v] = std::unique_ptr<InputPort>( new InputPort(_v, _state) );
		//m_inPorts.insert(std::pair<std::string, std::shared_ptr<InputPort>>(_v, std::shared_ptr<InputPort>(new InputPort(_v, _state))));
		std::unique_ptr<InputPortElement> _inputport{};
		m_inElements.push_back(std::unique_ptr<InputPortElement>(new InputPortElement(*m_inPorts.find(_v)->second.get())));

		for (int i = A_controllers - 1; i < A_controllers + D_inputs; ++i)
			m_elements.at(i)->addArgument(*m_inElements.back().get());
	}
	else
		throw std::logic_error("Logic error: V is already added!");
}


void Component::MakeMUX(std::vector<std::string> const & _inputPortNames,
						std::vector<std::string> const & _outputPortNames)
{
	
	int amountOfInputs = _inputPortNames.size();
	Q_outputs = 1;
	//	Количества информационных и управляющих входов определяются 
	//	по разработанной математической формуле
	A_controllers = (int)log2(amountOfInputs - log2(amountOfInputs)) + 1;
	D_inputs = amountOfInputs - A_controllers;

	//	Сохраняем введенные порты в таблицу
	for (int i = 0; i < amountOfInputs; ++i)
	{
		m_inPorts[_inputPortNames.at(i)] = std::unique_ptr<InputPort>(new InputPort(_inputPortNames.at(i)));
		//m_inPorts.insert(std::pair<std::string, std::shared_ptr<InputPort>>(_inputPortNames.at(i), 
		//	std::shared_ptr<InputPort>(new InputPort(_inputPortNames.at(i)))));

		// И заодно создаем элементы, которые будут храниться в векторе
		m_inElements.push_back(std::unique_ptr<InputPortElement>(new InputPortElement(*m_inPorts.find(_inputPortNames.at(i))->second.get())));
		//m_inElements.push_back(std::shared_ptr<InputPortElement>(new InputPortElement(*m_inPorts.find(_inputPortNames.at(i))->second.get())));
	}

	//	Создание первого вектора инвертирующих элементов
	for (int i = 0; i < A_controllers; ++i)
	{
		m_elements.push_back(std::unique_ptr<UnaryElement>(new UnaryElement (UnaryElement::TypeUnary::INVERTER, *m_inElements.at(D_inputs + i).get()) ));
	}

	//	Добавляем в него бинарные элементы "И"
	for (int i = 0; i < D_inputs; ++i)
	{
		m_elements.push_back(std::unique_ptr<MultiArgElement>(new MultiArgElement(MultiArgElement::TypeBinary::AND,  m_inElements.at(i).get() )));

		//m_elements.push_back(std::shared_ptr<BinaryElement>(new BinaryElement(BinaryElement::TypeBinary::AND,  m_inElements.at(i))));

		//	Добавляем в текущий элемент контролирующие элементы 
		//	Инвертированные/неинвертированные - в зависимости от номера обрабатываемого порта (элемента)
		for (int j = 0 ; j < A_controllers; ++j)
		{
			if ((i >> j ) & 1)
				m_elements.back().get()->addArgument(*m_inElements.at(D_inputs + j).get());
			else
				m_elements.back().get()->addArgument(*m_elements.at(j).get());
		}
	}

	//	И замыкающий элемент "ИЛИ"
	m_elements.push_back(std::unique_ptr<MultiArgElement>(new MultiArgElement(MultiArgElement::TypeBinary::OR)));
	for (int i = A_controllers; i < amountOfInputs; ++i)
		m_elements.at(m_elements.size() - 1).get()->addArgument(*m_elements.at(i).get());

	m_outPorts[_outputPortNames.at(0)] = std::unique_ptr<OutputPort>(new OutputPort(_outputPortNames.at(0), *m_elements.back().get()));
	//m_outPorts.insert(std::pair<std::string, std::shared_ptr<OutputPort>>(_outputPortNames.at(0),
	//	std::shared_ptr<OutputPort>(new OutputPort(_outputPortNames.at(0)))));

	//	Привязываем замыкающий элемент "ИЛИ" к выходному порту
	m_outPorts.find(_outputPortNames.at(0))->second.get()->BindElement(*m_elements.back().get());

	
}
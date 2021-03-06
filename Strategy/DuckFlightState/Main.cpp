#include "stdafx.h"

using namespace std;

struct IFlyBehavior
{
	virtual ~IFlyBehavior() = default;
	virtual void Fly() = 0;
};

class FlyWithWings : public IFlyBehavior
{
public:
	FlyWithWings(const shared_ptr<int>& flyCounter)
		: m_flyCounter(flyCounter)
	{
	}

	void Fly() override
	{
		cout << "I'm flying with wings!! Flights: " << ++(*m_flyCounter) << endl;
	}

private:
	shared_ptr<int> m_flyCounter;
};

class FlyWithRocketEngine : public IFlyBehavior
{
public:
	FlyWithRocketEngine(const shared_ptr<int>& flyCounter)
		: m_flyCounter(flyCounter)
	{
	}

	void Fly() override
	{
		cout << "I'm flying with rocket engine!! Flights: " << ++(*m_flyCounter) << endl;
	}

private:
	shared_ptr<int> m_flyCounter;
};

class FlyNoWay : public IFlyBehavior
{
public:
	void Fly() override
	{
	}
};

struct IQuackBehavior
{
	virtual ~IQuackBehavior() = default;
	virtual void Quack() = 0;
};

class QuackBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
		cout << "Quack Quack!!!" << endl;
	}
};

class SqueakBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
		cout << "Squeek!!!" << endl;
	}
};

class MuteQuackBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
	}
};

struct IDanceBehavior
{
	virtual ~IDanceBehavior() = default;
	virtual void Dance() = 0;
};

class WaltzDanceBehavior : public IDanceBehavior
{
public:
	void Dance() override
	{
		cout << "I'm dancing waltz!" << endl;
	}
};

class MinuetDanceBehavior : public IDanceBehavior
{
public:
	void Dance() override
	{
		cout << "I'm dancing minuet!" << endl;
	}
};

class NoDanceBehavior : public IDanceBehavior
{
public:
	void Dance() override
	{
		cout << "Men don't dance!" << endl;
	}
};

class Duck
{
public:
	Duck(unique_ptr<IFlyBehavior>&& flyBehavior,
		unique_ptr<IQuackBehavior>&& quackBehavior,
		unique_ptr<IDanceBehavior>&& danceBehavior)
		: m_quackBehavior(move(quackBehavior))
		, m_danceBehavior(move(danceBehavior))
	{
		assert(m_quackBehavior);
		assert(m_danceBehavior);
		SetFlyBehavior(move(flyBehavior));
	}
	void Quack() const
	{
		m_quackBehavior->Quack();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_flyBehavior->Fly();
	}
	void Dance()
	{
		m_danceBehavior->Dance();
	}
	void SetFlyBehavior(unique_ptr<IFlyBehavior>&& flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = move(flyBehavior);
	}
	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	unique_ptr<IFlyBehavior> m_flyBehavior;
	unique_ptr<IQuackBehavior> m_quackBehavior;
	unique_ptr<IDanceBehavior> m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck(const shared_ptr<int>& flyCounter)
		: Duck(make_unique<FlyWithWings>(flyCounter),
			make_unique<QuackBehavior>(),
			make_unique<WaltzDanceBehavior>())
	{
	}
	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck(const shared_ptr<int>& flyCounter)
		: Duck(make_unique<FlyWithWings>(flyCounter),
			make_unique<QuackBehavior>(),
			make_unique<MinuetDanceBehavior>())
	{
	}
	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};

class DeckoyDuck : public Duck
{
public:
	DeckoyDuck()
		: Duck(make_unique<FlyNoWay>(),
			make_unique<MuteQuackBehavior>(),
			make_unique<NoDanceBehavior>())
	{
	}
	void Display() const override
	{
		cout << "I'm deckoy duck" << endl;
	}
};

class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(make_unique<FlyNoWay>(),
			make_unique<SqueakBehavior>(),
			make_unique<NoDanceBehavior>())
	{
	}
	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(make_unique<FlyNoWay>(),
			make_unique<QuackBehavior>(),
			make_unique<NoDanceBehavior>())
	{
	}
	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	cout << endl;
}

void main()
{
	// Для подсчёта количества полётов храним указатель сверху
	//  и передаём его каждый раз при создании новой стратегии полёта.
	//  Это позволяет не создавать дополнительные методы классу стратегии
	//  для передачи данных от старого объекта к новому, а также не нарушать
	//  инкапсуляцию класса стратегии.
	// Тем не менее, приходиться создавать дополнительную переменную в коде сверху
	// и передавать её в конструктор класса утки, умеющей летать.
	auto mallardDuckFlyCounter = make_shared<int>(0);
	MallardDuck mallardDuck(mallardDuckFlyCounter);
	PlayWithDuck(mallardDuck);
	mallardDuck.SetFlyBehavior(make_unique<FlyWithRocketEngine>(mallardDuckFlyCounter));
	PlayWithDuck(mallardDuck);

	auto redheadDuckFlyCounter = make_shared<int>(0);
	RedheadDuck redheadDuck(redheadDuckFlyCounter);
	PlayWithDuck(redheadDuck);

	// Эти утки летать не умеют, поэтому счётчик полётов им не нужен
	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DeckoyDuck deckoyDuck;
	PlayWithDuck(deckoyDuck);

	// Модель утки - по умолчанию не летает
	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);

	// Однако можно нацепить на неё крылья и она полетит, подсчитывая количество полётов
	auto modelDuckFlyCounter = make_shared<int>(0);
	modelDuck.SetFlyBehavior(make_unique<FlyWithWings>(modelDuckFlyCounter));
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(make_unique<FlyWithRocketEngine>(modelDuckFlyCounter));
	PlayWithDuck(modelDuck);
}

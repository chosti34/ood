#include "stdafx.h"

using namespace std;

using FlyBehavior = function<void()>;
using QuackBehavior = function<void()>;
using DanceBehavior = function<void()>;

namespace
{
// Можно было бы использовать обычные функции
const function<void()> DO_NOT_DO_ANYTHING = []() {};
const QuackBehavior QUACK_AS_USUAL = []() { cout << "Quack Quack!!!" << endl; };
const QuackBehavior SQUEEK = []() { cout << "Squeek!!!" << endl; };
const DanceBehavior DANCE_WALTZ = []() { cout << "I'm dancing waltz!" << endl; };
const DanceBehavior DANCE_MINUET = []() { cout << "I'm dancing minuet!" << endl; };
const DanceBehavior DO_NOT_DANCE = []() { cout << "Men don't dance!" << endl; };
} // namespace

// Возвращаемая функция будет хранить в себе изменяемое значение счётчика
auto MakeFlyWithWingsBehavior()
{
	return [counter = 0]() mutable {
		cout << "I am flying with wings. Flight counter is: " << (++counter) << "\n";
	};
}

auto MakeFlyWithRocketEngineBehavior()
{
	return [counter = 0]() mutable {
		cout << "I am flying with rocket engine. Flight counter is: " << (++counter) << "\n";
	};
}

// Альтернатива функциям MakeFlyBehavior - структуры с перегруженным оператором ()
// Хранят значение счётчика полётов
struct FlyWithWingsBehavior
{
	void operator()()
	{
		cout << "I am flying with wings. Flight counter is: " << (++m_counter) << "\n";
	}

private:
	int m_counter = 0;
};

struct FlyWithRocketEngineBehavior
{
	void operator()()
	{
		cout << "I am flying with wings. Flight counter is: " << (++m_counter) << "\n";
	}

private:
	int m_counter = 0;
};

class Duck
{
public:
	Duck(const FlyBehavior& flyBehavior,
		const QuackBehavior& quackBehavior,
		const DanceBehavior& danceBehavior)
		: m_quackBehavior(quackBehavior)
		, m_danceBehavior(danceBehavior)
	{
		SetFlyBehavior(flyBehavior);
	}
	void Quack() const
	{
		m_quackBehavior();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_flyBehavior();
	}
	void Dance()
	{
		m_danceBehavior();
	}
	void SetFlyBehavior(const FlyBehavior& flyBehavior)
	{
		m_flyBehavior = flyBehavior;
	}
	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	FlyBehavior m_flyBehavior;
	QuackBehavior m_quackBehavior;
	DanceBehavior m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(FlyWithWingsBehavior(), QUACK_AS_USUAL, DANCE_WALTZ)
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
	RedheadDuck()
		: Duck(FlyWithWingsBehavior(), QUACK_AS_USUAL, DANCE_MINUET)
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
		: Duck(DO_NOT_DO_ANYTHING, DO_NOT_DO_ANYTHING, DO_NOT_DANCE)
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
		: Duck(DO_NOT_DO_ANYTHING, SQUEEK, DO_NOT_DANCE)
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
		: Duck(DO_NOT_DO_ANYTHING, QUACK_AS_USUAL, DO_NOT_DANCE)
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
	MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);
	PlayWithDuck(mallardDuck);
	// Счётчик полётов будет сброшен =(
	mallardDuck.SetFlyBehavior(MakeFlyWithRocketEngineBehavior());
	PlayWithDuck(mallardDuck);

	RedheadDuck redheadDuck;
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
	modelDuck.SetFlyBehavior(MakeFlyWithWingsBehavior());
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(MakeFlyWithRocketEngineBehavior());
	PlayWithDuck(modelDuck);
}

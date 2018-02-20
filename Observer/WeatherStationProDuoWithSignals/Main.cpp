#include "stdafx.h"
#include <boost/signals2/signal.hpp>

struct HelloWorld
{
	void operator()() const
	{
		std::cout << "Hello, world" << std::endl;
	}
};

int main()
{
	boost::signals2::signal<void()> signal;
	HelloWorld hello;
	signal.connect(hello);
	signal();
	return 0;
}

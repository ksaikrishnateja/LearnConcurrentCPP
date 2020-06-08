#include <iostream>
#include <thread>

void threadFunction()
{
	std::cout << "Hello from thread!\n";
}

class Callable {
public:
	operator()() {
		std::cout << "Hello from Callable\n";
	}
};

int main()
{
	std::thread th1(&threadFunction);

	Callable c;
	std::thread th2(c);

	th1.join();
	th2.join();

	std::cout << "Hello World\n";
	return 0;
}

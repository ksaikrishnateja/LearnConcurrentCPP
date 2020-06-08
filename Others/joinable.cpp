#include <iostream>
#include <thread>

void nestedThread(){
	std::cout << "Hello from Nested thread\n";
}

void threadFunction()
{
	std::thread th(nestedThread);
	th.join();
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

	if (th1.joinable())
		std::cout << "Thread 1 is joinable\n";
	else
		std::cout << "Thread 1 is not joinable\n";

	th1.join();

	if (th1.joinable())
		std::cout << "Thread 1 is joinable\n";
	else
		std::cout << "Thread 1 is not joinable\n";
	
	
	std::thread th0;
	
	if (th0.joinable())
		std::cout << "Thread 0 is joinable\n";
	else
		std::cout << "Thread 0 is not joinable\n";
	
	/*Callable c;
	std::thread th2(c);

	std::thread th3([](){
		std::cout << "Hello from Lambda\n";
	});
	
	th2.join();
	th3.join();

	std::cout << "Hello World\n";
	*/
	return 0;
}

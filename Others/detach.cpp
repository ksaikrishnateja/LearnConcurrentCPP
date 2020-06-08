#include <iostream>
#include <thread>
#include <chrono>


void threadFunction()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	std::cout << "Hello from function!\n";
}

class Callable {
public:
	operator()() {
	        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		std::cout << "Hello from callable!\n";
	}
};

int main()
{
	std::thread th1(&threadFunction);

	Callable c;
	std::thread th2(c);

	std::thread th3([](){
		std::cout << "Hello from lambda!\n";
	});
	
	std::cout << "Before detaching the thread!\n";
	th1.detach();
	std::cout << "After detaching the thread!\n";
	th2.join();
	std::cout << "After Joining the callable!\n";
	th3.join();

	std::cout << "Hello World\n";
	return 0;
}

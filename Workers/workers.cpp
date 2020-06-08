#include <iostream>
#include <thread>
#include <vector>
#include <cassert>

void threadFunction(int i)
{
	std::cout << "Hello from thread! " << i << "\n";
}

int main()
{
	std::vector<std::thread> workers;
        for(int i=0; i < 8; ++i) {
		auto th = std::thread(&threadFunction, i);
		workers.push_back(std::move(th));
		assert(!th.joinable());
	}
	std::cout << "Hello World\n";
	for(auto& th : workers) {
		assert(th.joinable());
		th.join();
	} 
	return 0;
}

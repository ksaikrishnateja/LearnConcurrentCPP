#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>

int main()
{
	std::vector<std::thread> workers;
	for (int i=0; i < 10 ; i++) {
	    workers.push_back(std::thread([i](){
		std::cout << "Hello from thread " << i << "!\n";
	    }));
	}
	std::cout << "Hello World\n";
	for(auto& th : workers) {
	    th.join();
	}

	return 0;
}

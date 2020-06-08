#include <iostream>
#include <thread>

void nestedThread(){
    std::cout << "Hello from Nested thread\n";
}

void threadFunction(int i)
{
    std::thread th(nestedThread);
    th.join();
    std::cout << "Hello from thread!\n";
    std::cout << "Got param <" << i << "> in thread " 
              << std::this_thread::get_id() << std::endl;
}

class Callable {
public:
    void operator()() {
        std::cout << "Hello from Callable\n";
    }
};

int main()
{
    std::thread th1(&threadFunction, 10);

    th1.join();

    Callable c;
    std::thread th2(c);

    std::thread th3([](){
        std::cout << "Hello from Lambda\n";
    });
    
    th2.join();
    th3.join();

    std::cout << "Hello World\n";
    return 0;
}

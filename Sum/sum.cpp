#include <iostream>
#include <thread>
#include <vector>
#include <future>

using namespace std;

const unsigned int BLOCK_SIZE = 5;

void sum_per_thread(unsigned int id, std::vector<int>arr, int stride, 
        std::promise<long long int>& prm) {

    long long int sum = 0;

    for (unsigned int i = id * BLOCK_SIZE ; i < (id+1) * BLOCK_SIZE; i++)
        sum += arr[i];

    prm.set_value(sum);
}

long long int parallel_sum(std::vector<int>& arr) {
    int stride = 1;

    std::vector<std::thread> workers;
    std::vector<std::promise<long long int>> prms;
    std::vector<std::future<long long int>> ftrs;
    
    for (unsigned int i=0; i<arr.size()/BLOCK_SIZE; i++) {
        std::promise<long long int> prm;
        ftrs.push_back(prm.get_future());
        workers.push_back(std::thread(sum_per_thread, i, arr, stride,
                                        std::ref(prm)));
    }

    for (auto& th : workers) {
        th.join();
    }

    long long int overall_sum = 0;
    for (auto& ftr : ftrs) {
        overall_sum += ftr.get();
    }

    return overall_sum;
}


long long int serial_sum(std::vector<int>& arr) {
    long long int sum = 0;
    for (auto& elem : arr)
        sum += elem;
    return sum;
}


int main() {
    unsigned int N = 0;
    std::vector<int> arr;
    std::cin >> N;
    while(N--) {
        int x = 0;
        std::cin >>  x;
        arr.push_back(x);
    }

    long long int ssum = 0, psum = 0;
    ssum = serial_sum(arr);
    std::cout << "serial_sum: " << ssum << std::endl;
    psum = parallel_sum(arr);
    std::cout << "parallel_sum: " << psum << std::endl;

    if (psum != ssum) {
        std::cout << "Parallel and Serial versions are *NOT* Matching." << std::endl;
    }
    else {
        std::cout << "Parallel and Serial versions are Matching." << std::endl;
    }
}

#include<iostream>
#include<mutex>
#include<thread>
#include<condition_variable>

std::mutex m;
std::condition_variable cv;
bool label = true;

void func1() {
    std::unique_lock<std::mutex> ulock(m);
    for (int odd = 1; odd <= 100; odd += 2) {
        cv.wait(ulock, []{ return label; });
        std::cout << odd << std::endl;
        label = false;
        cv.notify_one();
    }
}

void func2() {
    std::unique_lock<std::mutex> ulock(m);
    for (int even = 2; even <= 100; even += 2) {
        cv.wait(ulock, []{ return !label; });
        std::cout << even << std::endl;
        label = true;
        cv.notify_one();
    }
}

int main() {
    std::thread t1(func1);
    std::thread t2(func2);
    t1.join();
    t2.join();
    return 0;
}


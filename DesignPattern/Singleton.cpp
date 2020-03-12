#include<iostream>

class Singleton {
public:
    static Singleton& Instance() {
        static Singleton instance;
        return instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
private:
    Singleton() { std::cout << "constructor called! " << std::endl; }
};

int main() {
    Singleton& instance = Singleton::Instance();
    return 0;
}
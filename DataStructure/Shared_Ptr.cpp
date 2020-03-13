#include<iostream>

template<typename T>
class Shared_Ptr {
public:
    Shared_Ptr(T* ptr): _ptr(ptr), count(new size_t(1)) { }
    Shared_Ptr(const Shared_Ptr<T>& rhs) {
        _ptr = rhs._ptr;
        count = rhs.count;
        (*count)++;
    }
    Shared_Ptr& operator=(const Shared_Ptr<T>& rhs) {
        if (this == &rhs)
            return *this;
        free();
        _ptr = rhs._ptr;
        count = rhs.count;
        (*count)++;
    }
    ~Shared_Ptr() { free(); }
private:
    T* _ptr;
    size_t* count;

    void free() {
        (*count)--;
        if (*count == 0) {
            std::cout << "deleted" << std::endl;
            delete count;
            delete _ptr;
        }
    }
};

template<typename T, typename... Args>
Shared_Ptr<T> Make_Shared(Args&& ... args) {
    T* raw = new T(std::forward<Args>(args)...);
    return Shared_Ptr<T>(raw);
}

int main() {
    Shared_Ptr<int> sp(new int(1));
    Shared_Ptr<int> sp1 = sp;
    Shared_Ptr<int> sp2 = Make_Shared<int>(3);
    return 0;
}
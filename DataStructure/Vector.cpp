#include<memory>
#include<iostream>

//简化版vector实现
template<typename T>
class Vector {
public:
    //显式构造函数
    explicit Vector(size_t size = 0) {
        _begin = _free = alloc.allocate(size);
        _end = _begin + size;
    }
    //复制构造函数
    Vector(const Vector<T>& rhs) {
        _begin = alloc.allocate(rhs.capacity());
        _free = _begin + rhs.size();
        _end = _begin + rhs.capacity();
        auto src = rhs._begin;
        for (auto it = _begin; it != _free; ++it)
            alloc.construct(it, *(src++));
    }

    //重载赋值运算符
    Vector& operator=(const Vector<T>& rhs) {
        if (this == &rhs)
            return this;
        free();
        _begin = alloc.allocate(rhs.capacity());
        _free = _begin + rhs.size();
        _end = _begin + capacity;
        auto src = rhs._begin;
        for (auto it = _begin; it != _free; ++it)
            alloc.construct(it, *(src++));
    }

    //析构函数
    ~Vector() { free(); }
    //末尾插入
    void push_back(const T& val) {
        check_n_alloc();
        alloc.construct(_free++, val);
    }

    //实现[]运算符
    T& operator[](size_t pos) { return *(_begin + pos); }

    size_t size() const { return _free - _begin; }
    size_t capacity() const { return _end - _begin; }

private:
    //释放动态申请的内存
    void free() {
        for (T* it = _begin; it != _end; ++it)
            alloc.destroy(it);
        alloc.deallocate(_begin, capacity());
    }
    //重新分配内存
    void reallocate() {
        size_t newSize = size() == 0 ? 1 : 2 * size();
        auto newData = alloc.allocate(newSize);
        auto dest = newData;
        for (auto it = _begin; it != _free; ++it)
            alloc.construct(dest++, std::move(*it));
        free();
        _begin = newData;
        _free = dest;
        _end = _begin + newSize;
    }
    //检查是否需要重新分配内存
    void check_n_alloc() {
        if (size() == capacity())
            reallocate();
    }

    T *_begin, *_free, *_end;
    static std::allocator<T> alloc;
};

template<typename T>
std::allocator<T> Vector<T>::alloc;


int main() {
    Vector<int> vi;
    std::cout << vi.size() << std::endl;

    for (int i = 0; i < 10; ++i) {
        vi.push_back(i);
        std::cout << vi.size() << std::endl;
    }

    for (int i = 0; i < 10; ++i) {
        std::cout << vi[i] << std::endl;
    }
    Vector<int> vi2 = vi;
    for (int i = 0; i < 10; ++i) {
        std::cout << vi2[i] << std::endl;
    }
}
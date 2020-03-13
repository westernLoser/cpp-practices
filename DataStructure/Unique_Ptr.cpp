template<typename T>
class Unique_Ptr {
public:
    Unique_Ptr(T* ptr): _ptr(ptr) { }
    Unique_Ptr(const Unique_Ptr<T>&) = delete;
    Unique_Ptr& operator=(const Unique_Ptr&) = delete;
    ~Unique_Ptr() { delete _ptr; }
private:
    T* _ptr;
};

int main() {
    Unique_Ptr<int> up(new int(1));
    return 0;
}
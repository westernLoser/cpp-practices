#include<iostream>
#include<cstring>

class String {
public:
    friend std::ostream& operator<<(std::ostream& os, const String& s);

    String(const char* data = nullptr);
    String(const String&);
    String& operator=(const String&);
    ~String();
private:
    char* data_;
};

String::String(const char* data) {
    if (data == nullptr) {
        data_ = new char[1];
        data_[0] = '\0';
    }
    else {
        int len = strlen(data);
        data_ = new char[len + 1];
        strcpy(data_, data);
    }
}

String::String(const String& rhs) {
    int len = strlen(rhs.data_);
    data_ = new char[len + 1];
    strcpy(data_, rhs.data_);
}

String& String::operator=(const String& rhs) {
    if (this == &rhs)
        return *this;
    delete[] data_;
    int len = strlen(rhs.data_);
    data_ = new char[len + 1];
    strcpy(data_, rhs.data_);
    return *this;
}

String::~String() {
    delete[] data_;
}

std::ostream& operator<<(std::ostream& os, const String& s) {
    os << s.data_;
    return os;
}

int main() {
    String s = "abcde";
    String s1 = s;
    std::cout << s << " " << s1 << std::endl;
    return 0;
}
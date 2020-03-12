#include<thread>
#include<mutex>
#include<condition_variable>
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>

class BoundedBuffer {
public:
    BoundedBuffer(size_t size): begin_(0), end_(0), buffered_(0), buffer(size) { }
    BoundedBuffer(const BoundedBuffer&) = delete;
    BoundedBuffer& operator=(const BoundedBuffer&) = delete;
    
    void produce(int n) {
        {
            std::unique_lock<std::mutex> lck(mutex_);
            not_full.wait(lck, [=]{ return buffered_ < buffer.size(); });
            buffer[end_] = n;
            end_ = (end_ + 1) % buffer.size();
            ++buffered_;
        }
        not_empty.notify_one(); 
    }

    int consume() {
        int result = 0;
        {
            std::unique_lock<std::mutex> lck(mutex_);
            not_empty.wait(lck, [=]{ return buffered_ > 0; });
            result = buffer[begin_];
            begin_ = (begin_ + 1) % buffer.size();
            --buffered_;
        }
        not_full.notify_one();
        return result;
    }

private:
    size_t begin_, end_, buffered_;
    std::vector<int> buffer;
    std::mutex mutex_;
    std::condition_variable not_empty, not_full;
};

BoundedBuffer g_buffer(10);
std::mutex g_io_mutex;

void Producer() {
    for (int i = 0; i < 20; ++i) {
        g_buffer.produce(i);
    }
}

void Consumer() {
    for (int i = 0; i < 10; ++i) {
        int result = g_buffer.consume();
        std::unique_lock<std::mutex> lck(g_io_mutex);
        std::cout << std::this_thread::get_id() << ": " << result << std::endl;
    }
}

int main() {
    std::vector<std::thread> threads;
    threads.emplace_back(Producer);
    threads.emplace_back(Consumer);
    threads.emplace_back(Consumer);
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    return 0;
}
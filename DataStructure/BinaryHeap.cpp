#include<vector>
#include<iostream>

using std::vector;

//自顶向下调整堆
void TopDown(vector<int>& data, int pos, int n) {
    if (n > data.size() || pos >= data.size() || pos < 0)
        return;
    while (pos < n) {
        int left = 2 * pos + 1, right = 2 * pos + 2, npos = pos;
        if (left < n && data[left] > data[pos]) {
            npos = left;
        }
        if (right < n && data[right] > data[left]) {
            npos = right;
        }
        if (npos == pos) break;
        std::swap(data[pos], data[npos]);
        pos = npos;
    }
}

//自底向上调整堆
void BottomUp(vector<int>& data, int pos) {
    if (pos >= data.size()) return;
    while (pos > 0) {
        int parent = (pos - 1) / 2;
        if (data[pos] > data[parent]) {
            std::swap(data[pos], data[parent]);
            pos = parent;
        }
        else {
            break;
        }
    }
}

//将数组转为大顶堆
void Heapify(vector<int>& data) {
    for (int i = (data.size() - 1) / 2; i >= 0; --i)
        TopDown(data, i, data.size());
}

//堆排序
void HeapSort(vector<int>& data) {
    if (data.empty()) return;
    Heapify(data);
    for (int i = data.size() - 1; i > 0; --i) {
        std::swap(data[0], data[i]);
        TopDown(data, 0, i);
    }
}

//一个堆类
class Heap {
public:
    Heap() { }
    explicit Heap(const vector<int>& data): _data(data) { Heapify(_data); }

    void push(int val) {
        _data.push_back(val);
        BottomUp(_data, _data.size() - 1);
    }

    //不考虑异常
    int top() const {
        return _data[0];
    }
    //不考虑异常
    void pop() {
        std::swap(_data[0], _data.back());
        _data.pop_back();
        TopDown(_data, 0, _data.size());
    }

    size_t size() const { return _data.size(); }
private:
    vector<int> _data; //存放数据
};


int main() {

    //测试堆排序的正确性
    vector<int> vi = {-1, 0, 3, 1, 2, 5};
    HeapSort(vi);
    for (auto num : vi)
        std::cout << num << " ";
    std::cout << std::endl;

    //测试堆类的使用
    vi = {-1, 0, 3, 1, 2, 5};
    Heap heap;
    for (auto num : vi)
        heap.push(num);
    while (heap.size()) {
        std::cout << heap.top() << " ";
        heap.pop();
    }
    std::cout << std::endl;
    return 0;
}

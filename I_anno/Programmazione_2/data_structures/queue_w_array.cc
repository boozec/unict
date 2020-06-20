#include<iostream>

using namespace std;

template<class H>
class queue {
public:
    queue(int n) : _size{n}, _counter{0}, _head{0}, _tail{0} {
        _arr = new H[n];
    }
    ~queue() {
        delete _arr;
    }
    bool is_empty() {
        return _counter == 0;
    }
    bool is_full() {
        return _counter == _size;
    }

    queue<H>* enqueue(H x) {
        if(!is_full()) {
            _arr[_tail] = x;
            if(_tail == _size-1)
                _tail = 0;
            else
                ++_tail;
            _counter++;
        }

        return this;
    }
    H dequeue() {
        if(is_empty()) return -1;
        H x = _arr[_head];

        if(_head == _size-1)
            _head = 0;
        else
            ++_head;

        _counter--;
        return x;
    }
private:
    H* _arr;
    int _size;
    short _counter;
    short _head;
    short _tail;
};

int main() {
    queue<int>* q = new queue<int>{4};
    q->enqueue(5)->enqueue(13)->enqueue(3);
    cout << q->dequeue() << '\n';
    q->enqueue(4)->enqueue(6)->enqueue(7);
    q->dequeue();
    q->enqueue(7);

    for(int i = 0; i < 6; ++i) {
        cout << q->dequeue() << ' ';
    }
    delete q;
    return 0;
}

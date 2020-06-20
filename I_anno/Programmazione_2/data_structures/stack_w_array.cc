#include<iostream>

using namespace std;

template<class H>
class stack {
public:
    stack(int n) : _size{n}, _top{-1} {
        _arr = new H[n];
    }
    ~stack() {
        delete _arr;
    }
    bool is_empty() {
        return _top == -1;
    }
    bool is_full() {
        return _top == _size-1;
    }
    stack<H>* push(H x) {
        if(!is_full()) {
            _arr[++_top] = x;
        }
        return this;
    }
    H pop() {
        if(is_empty()) 
            return -1;
        _top--;
        return _arr[_top+1];
    }
private:
    int _size;
    H* _arr;
    short _top;
};

int main() {
    stack<int>* s = new stack<int>{7};

    s->push(15)->push(6)->push(2)->push(9)->push(17)->push(3);
    cout << s->pop() << '\n';
    s->push(18)->push(19)->push(12);

    for(int i = 0; i < 7; ++i)
        cout << s->pop() << ' ';

    delete s;
    return 0;
}

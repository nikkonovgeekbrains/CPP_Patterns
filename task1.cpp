#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

std::mutex m1;

class ChocolateBoiler{
private:
    bool _empty;
    bool _boiled;
    static ChocolateBoiler* _uniqueInstance;

//    Перенесли конструктов в private
    ChocolateBoiler(){
        _empty = true;
        _boiled = false;
    }

public:
//    Запрещаем копирование и присваивание
    ChocolateBoiler(ChocolateBoiler& other) = delete;
    void operator=(const ChocolateBoiler&) = delete;

    static ChocolateBoiler* getInstance() {
        m1.lock();
        if (_uniqueInstance == nullptr) {
            _uniqueInstance = new ChocolateBoiler();
        }
        m1.unlock();

        return _uniqueInstance;
    }

    virtual ~ChocolateBoiler(){
        delete _uniqueInstance;
    }

    bool isEmpty() const{
        return _empty;
    }

    bool isBoiled() const{
        return _boiled;
    }

    void fill(){
        if (isEmpty()){
            _empty = false;
            _boiled = false;
        }
    }

    void drain(){
        if (!isEmpty() && isBoiled()){
            _empty = true;
        }
    }

    void boil(){
        if (!isEmpty() && !isBoiled()){
            _boiled = true;
        }
    }
};

ChocolateBoiler* ChocolateBoiler::_uniqueInstance = nullptr;

int main()
{

    ChocolateBoiler* b1 = ChocolateBoiler::getInstance();
    ChocolateBoiler* b2 = ChocolateBoiler::getInstance();

    cout << "empty:" << endl;
    cout << b1->isEmpty() << endl;
    cout << b2->isEmpty() << endl;
    b1 ->fill();
    cout << b1->isEmpty() << endl;
    cout << b2->isEmpty() << endl;

    cout << "boiled:" << endl;
    cout << b1->isBoiled() << endl;
    cout << b2->isBoiled() << endl;
    b2->boil();
    cout << b1->isBoiled() << endl;
    cout << b2->isBoiled() << endl;

    cout << "drain:" << endl;
    cout << b1->isEmpty() << endl;
    cout << b2->isEmpty() << endl;
    b1->drain();
    cout << b1->isEmpty() << endl;
    cout << b2->isEmpty() << endl;

    return 0;
}

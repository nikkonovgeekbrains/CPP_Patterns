#include <iostream>
#include <map>

using namespace std;

class Beverage{            // Абстрактный класс
public:
    virtual std::string getDescription() const;
    virtual double cost() const = 0;
    virtual ~Beverage() {}
};

std::string Beverage::getDescription() const {
    return std::string();
}

class HouseBlend: public Beverage{   // Молотый
public:
    HouseBlend()= default;
    double cost() const override {
        return 5.5;
    }
};

class DarkRoast: public Beverage{  // Темной обжарки
public:
    double cost() const override {
        return 6.0;
    }

};

class Decaf: public Beverage{    // Без кофеина
public:
    double cost() const override {
        return 7.3;
    }

};

class Espresso: public Beverage{  // Эспрессо
public:
    double cost() const override {
        return 3.5;
    }

};

class Decorator: public Beverage{
public:
    Decorator(Beverage* beverage): _beverage(beverage){};

    virtual double cost() const override{
        return this->_beverage->cost();
    };


private:
    Beverage* _beverage;
};

class Chocolate: public Decorator{
private:
    Beverage* _beverage;
public:
    Chocolate(Beverage* beverage): Decorator(beverage){};
    double cost() const override{
        return Decorator::cost() + 0.8;
    };
};

class Cinnamon: public Decorator{
private:
    Beverage* _beverage;
public:
    Cinnamon(Beverage* beverage): Decorator(beverage){};
    double cost() const override{
        return Decorator::cost() + 0.7;
    };
};

class Without_milk: public Decorator{
private:
    Beverage* _beverage;
public:
    Without_milk(Beverage* beverage): Decorator(beverage){};
    double cost() const override{
        return Decorator::cost() - 0.5;
    };
};

class Without_sugar: public Decorator{
private:
    Beverage* _beverage;
public:
    Without_sugar(Beverage* beverage): Decorator(beverage){};
    double cost() const override{
        return Decorator::cost() - 0.1;
    };
};


int main() {
    Beverage* cof1 = new HouseBlend;
    Beverage* cof2 = new Chocolate(cof1);
    Beverage* cof3 = new Without_sugar(new Cinnamon(new Without_milk(cof1)));

    cout << cof1->cost() << endl;
    cout << cof2->cost() << endl;
    cout << cof3->cost() << endl;

    return 0;
}

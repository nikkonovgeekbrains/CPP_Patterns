#ifndef HW4_FABRIC_METHOD_H
#include <iostream>

using namespace std;

class Pizza{
public:
    virtual void prepare(string){};
    virtual void print(){};
    virtual void bake() {};
    virtual void cut() {};
    virtual void box() {};
};

class CheesePizza: public Pizza{
    void print() override{
        cout << "chesee" << endl;
    }
};
class GreekPizza: public Pizza{
    void print() override{
        cout << "greek" << endl;
    }
};
class PepperoniPizza: public Pizza{
    void print() override{
        cout << "pepperoni" << endl;
    }
};

class Factory{
public:
    virtual Pizza* createPizza() = 0;
    virtual ~Factory(){}
};

class CheesePizzaFactory : public Factory{
public:
    Pizza* createPizza() override{
        return new CheesePizza;
    }
};

class GreekPizzaFactory : public Factory{
public:
    Pizza* createPizza() override{
        return new GreekPizza;
    }
};

class PepperoniPizzaFactory : public Factory{
public:
    Pizza* createPizza() override{
        return new PepperoniPizza;
    }
};

Pizza* orderPizza(string type){
    CheesePizzaFactory* cheese_pizza_factory = new CheesePizzaFactory;
    GreekPizzaFactory* greek_pizza_factory = new GreekPizzaFactory;
    PepperoniPizzaFactory* pepperoni_pizza_factory = new PepperoniPizzaFactory;

    Factory *pFactory = nullptr;

    Pizza* pizza = nullptr;
    if (type == "cheese"){
        pFactory = cheese_pizza_factory;
    }
    else if (type == "greek"){
        pFactory = greek_pizza_factory;
    }
    else if (type == "pepperoni"){
        pFactory = pepperoni_pizza_factory;
    }
    pizza = pFactory->createPizza();

    return pizza;
}
#define HW4_FABRIC_METHOD_H

#endif //HW4_FABRIC_METHOD_H

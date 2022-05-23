#include <iostream>
using namespace std;

class Pizza{
public:
    virtual void prepare(std::string) {};
    virtual void bake() {};
    virtual void cut() {};
    virtual void box() {};
    virtual ~Pizza() {};
};

class CheesePizza:public Pizza{
public:
    CheesePizza(){
        cout << "Cheese Pizza added!" << endl;
    }
    void prepare(std::string){}
    void bake() {}
    void cut() {}
    void box() {}
};

class GreekPizza:public Pizza{
public:
    GreekPizza(){
        cout << "Greek Pizza added!" << endl;
    }
    void prepare(std::string){}
    void bake() {}
    void cut() {}
    void box() {}
};

class PepperoniPizza:public Pizza{
public:
    PepperoniPizza(){
        cout << "Pepperoni Pizza added!" << endl;
    }
    void prepare(std::string){}
    void bake() {}
    void cut() {}
    void box() {}
};

class PizzaFactory
{
public:
    virtual Pizza* createPizza() = 0;

    virtual ~PizzaFactory() {};
};

class CheesePizzaFactory : public PizzaFactory
{
public:
    Pizza* createPizza(){
        return new CheesePizza;
    }
};

class GreekPizzaFactory : public PizzaFactory
{
public:
    Pizza* createPizza(){
        return new GreekPizza;
    }
};

class PepperoniPizzaFactory : public PizzaFactory
{
public:
    Pizza* createPizza(){
        return new PepperoniPizza;
    }
};

Pizza* orderPizza(PizzaFactory& factory){
    Pizza* pizza = factory.createPizza();
//    Pizza* pizza = nullptr;
//    if (type == "cheese"){
//        pizza = new CheesePizza;
//    }
//    else if (type == "greek"){
//        pizza = new GreekPizza;
//    }
//    else if (type == "pepperoni"){
//        pizza = new PepperoniPizza;
//    }
    return pizza;
}

int main() {
    //Закажем сырную пиццу
    CheesePizzaFactory pz1_factory;
    Pizza* pz1 = orderPizza(pz1_factory);

    //Закажем греческую пиццу
    GreekPizzaFactory pz2_factory;
    Pizza* pz2 = orderPizza(pz2_factory);

    //Закажем пиццу пеперони
    PepperoniPizzaFactory pz3_factory;
    Pizza* pz3 = orderPizza(pz3_factory);
    return 0;
}

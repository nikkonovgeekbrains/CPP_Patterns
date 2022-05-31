#ifndef HW4_BUILDER_H
#include <iostream>
#include <vector>
#include <optional>

using namespace std;

class Events{
public:
    virtual void getEvent() = 0;
    virtual ~Events() {};
};

class Hotel: public Events{
public:
    void getEvent() {
        std::cout << "Booking Hotel" << std::endl;
    }
};

class Park: public Events{
    void getEvent() {
        std::cout << "Park visiting" << std::endl;
    }
};

class Food: public Events{
public:
    virtual void getEvent() = 0;
    virtual ~Food() {};
};

class Dinner: public Food{
public:
    Dinner(const std::string &type) : _type("breakfast") {}
    void getEvent() override{
        std::cout << _type << std::endl;
    } ;
private:
    std::string _type;
};

class Lunch: public Food{
public:
    Lunch() : _type("lunch") {}
    void getEvent () override{
        std::cout << _type << std::endl;
    } ;
private:
    std::string _type;
};

class Breakfast: public Food{
public:
    Breakfast() : _type("breakfast") {}
    void getEvent () override{
        std::cout << _type << std::endl;
    } ;
private:
    std::string _type;
};

class Special: public Events{
public:
    virtual void getEvent() override = 0;
    virtual ~Special() {};
};

class Skating:public Special{
public:
    Skating(const std::string &type) : _type("skating") {}
    void getEvent() override {
        std::cout << _type << std::endl;
    } ;
private:
    std::string _type;
};

class Circus:public Special{
public:
    Circus(const std::string &type) : _type("circus") {}
    void getEvent(){
        std::cout << _type << std::endl;
    } ;
private:
    std::string _type;
};



struct MyDayEvents{
    optional<Hotel> hotel = nullopt;
    optional<Park> park = nullopt;
    vector<Food*> food;
    vector<Special*> specials;

    void eventsList(){
        if (hotel.has_value()){
            cout << "Hotel" << endl;
        }
        if (park.has_value()){
            cout << "Park" << endl;
        }
        if (static_cast<int>(food.size())){
            cout << "Food:" << endl;
            for(int i = 0; i < static_cast<int>(food.size()); i++){
                cout << "   ";
                food[i]->getEvent();
            }
        }

        if (static_cast<int>(specials.size())){
            cout << "Specials:" << endl;
            for(int i = 0; i < static_cast<int>(specials.size()); i++){
                cout << "   ";
                specials[i]->getEvent();
            }
        }
    }
    ~MyDayEvents(){
        for (const auto& event: food){
            delete event;
        }
        for (const auto& spec: specials){
            delete spec;
        }
    }
};

class EventBuilder{
protected:
    MyDayEvents* mde = nullptr;
public:
    EventBuilder(): mde(0) {}
    virtual ~EventBuilder() {}
    virtual void createMyDayEvents() {}
    virtual void buildHotel() {}
    virtual void buildPark() {}
    virtual void buildDinner() {}
    virtual void buildLunch() {}
    virtual void buildBreakfast() {}
    virtual void buildSkating() {}
    virtual void buildCircus() {}
    virtual MyDayEvents* getDayEvents() {return mde; }
};

class MinimumBuilder : public EventBuilder{
    void createMyDayEvents() override {mde = new MyDayEvents;}
    void buildHotel() override {mde->hotel = Hotel();}
    void buildPark() override {mde->park = Park();}
    void buildDinner() override {mde->food.push_back(new Dinner("Dinner"));}
};

class MediumBuilder : public EventBuilder{
    void createMyDayEvents() override {mde = new MyDayEvents;}
    void buildPark() override {mde->park = Park();}
    void buildLunch() override {mde->food.push_back(new Lunch());}
    void buildBreakfast() override {mde->food.push_back(new Breakfast());}
    void buildCircus() override {mde->specials.push_back(new Circus("Cirkus"));}
};

class AllInclusiveBuilder : public EventBuilder{
    void createMyDayEvents() override {mde = new MyDayEvents;}
    void buildHotel() override {mde->hotel = Hotel();}
    void buildPark() override {mde->park = Park();}
    void buildDinner() override {mde->food.push_back(new Dinner("Dinner"));}
    void buildLunch() override {mde->food.push_back(new Lunch());}
    void buildBreakfast() override {mde->food.push_back(new Breakfast());}
    void buildSkating() override {mde->specials.push_back(new Skating("Skating"));}
    void buildCircus() override {mde->specials.push_back(new Circus("Cirkus"));}
};

class Director{
public:
    MyDayEvents* createDayEvents(EventBuilder& builder){
        builder.createMyDayEvents();
        builder.buildHotel();
        builder.buildPark();
        builder.buildBreakfast();
        builder.buildLunch();
        builder.buildDinner();
        builder.buildSkating();
        builder.buildCircus();
        return(builder.getDayEvents());
    }
};
#define HW4_BUILDER_H

#endif //HW4_BUILDER_H

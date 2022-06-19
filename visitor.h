//
// Created by nikko on 19.06.2022.
//

#ifndef HW5_KONOVALTSEV_VISITOR_H
#define HW5_KONOVALTSEV_VISITOR_H

#include <iostream>
#include <vector>

using namespace std;

class Ingredient;
class Menu;
class MenuItem;

class Visitor{
public:
    virtual void getState(Ingredient* ing) = 0;
//    virtual void getState(Menu* menu) = 0;
    virtual void getState(MenuItem* menu_item) = 0;
};



class Menu{
private:
    vector<MenuItem*> menuItemsList = {};
public:
    Menu(){}

    void addMenuItem(MenuItem* new_menu_item){
        menuItemsList.push_back(new_menu_item);
    }

    vector<MenuItem*> getMenuItemList(){
        return menuItemsList;
    }

    void getState(Visitor& v){
        cout << "Menu:" << endl << endl;
        for(auto menu_item: getMenuItemList()){
            v.getState(menu_item);
        }
    }
};

class Ingredient{
public:
    std::string name;
    int healthRating;
    float Calories;
    float Protein;
    float Carbs;
    float Fats;

    Ingredient(){}

    Ingredient(string name, int healthRating, float cals, float prts, float cabs, float fats): name(name),
                                                                                               healthRating(healthRating), Calories(cals), Protein(prts), Carbs(cabs), Fats(fats){}
};

class MenuItem: public Menu, public Ingredient{
private:
    std::string name;
    std::string description;
    float price;
    std::vector<Ingredient*> ingredients;
public:

    MenuItem(const std::string &name, const std::string &description, float price, vector<Ingredient*> inp_ingr) : name(name),
                                                                                                                   description(description),
                                                                                                                   price(price),  ingredients(inp_ingr){}

    const std::string &getName() const {
        return name;
    }

    const std::string &getDescription() const {
        return description;
    }

    float getPrice() const {
        return price;
    }

    std::vector<Ingredient*> getItemsList() const {
        return ingredients;
    }
};

class StandartVisitor: public Visitor{
    void getState(Ingredient* ing) override{
        cout << ing->name;
    }

    void getState(MenuItem* menu_item) override{
        cout << "name: " << menu_item->getName() << endl;
        cout << "description: " << menu_item->getDescription() << endl;
        cout << "price: " << menu_item -> getPrice() << endl;
    }

//    void getState(Menu* menu) override{
//        cout << "Menu:" << endl << endl;
//        for(auto menu_item: menu->getMenuItemList()){
//            this->getState(menu_item);
//        }
//    }
};

class DietVisitor: public Visitor{
    void getState(Ingredient* ing) override{
        cout << endl << "name: " << ing->name;
        cout << " calories: " << ing -> Calories;
    }

    void getState(MenuItem* menu_item) override{
        cout << "name: " << menu_item->getName() << endl;
        cout << "description: " << menu_item->getDescription() << endl;
        cout << "price: " << menu_item -> getPrice() << endl;
        cout << "ingredients:" << endl;
        float total_cal = 0;
        for(auto ingr: menu_item->getItemsList()){
            total_cal += ingr->Calories;
            this->getState(ingr);
        }
        cout << " total_cals: " << total_cal << endl;
    }

//    void getState(Menu* menu) override{
//        cout << "Menu:" << endl << endl;
//        for(auto menu_item: menu->getMenuItemList()){
//            this->getState(menu_item);
//        }
//    }
};

class FitnessVisitor: public Visitor{
    void getState(Ingredient* ing) override{
        cout << endl << "name: " << ing->name;
        cout << " calories: " << ing -> Calories;
        cout << " proteins: " << ing -> Protein;
        cout << " carbs: " << ing -> Carbs;
        cout << " fats: " << ing -> Fats;
    }

    void getState(MenuItem* menu_item) override{
        cout << "name: " << menu_item->getName() << endl;
        cout << " description: " << menu_item->getDescription() << endl;
        cout << " price: " << menu_item -> getPrice() << endl;
        cout << " ingredients:" << endl;
        float total_cal = 0;
        float total_prots = 0;
        float total_carbs = 0;
        float total_fats = 0;

        for(auto ingr: menu_item->getItemsList()){
            total_cal += ingr->Calories;
            total_prots += ingr->Protein;
            total_carbs += ingr->Carbs;
            total_fats += ingr->Fats;
            this->getState(ingr);
        }
        cout << endl << "total_cals: " << total_cal << endl;
        cout << "total_prots: " << total_prots << endl;
        cout << "total_carbs: " << total_carbs << endl;
        cout << "total_fats: " << total_fats << endl;
    }

//    void getState(Menu* menu) override{
//        cout << "Menu:" << endl << endl;
//        for(auto menu_item: menu->getMenuItemList()){
//            this->getState(menu_item);
//        }
//    }
};

#endif //HW5_KONOVALTSEV_VISITOR_H

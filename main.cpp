#include <iostream>
#include "observer.h"
#include "visitor.h"
#include "facade.h"

using namespace std;


int main() {
    cout << "Task 1:" << endl;
    MyFacade movie_pl;
    cout << "On:" << endl;
    movie_pl.play_movie();

    // Посмотрели? А теперь все обратно надо выключить)
    cout << endl << endl << "Off:" << endl;
    movie_pl.off_all();


    cout << endl << endl << endl << "Task 2:" << endl;
    Ingredient ing1("ing 1", 1, 300, 50, 20, 10);
    Ingredient ing2("ing 2", 2, 600, 500, 50, 50);
    Ingredient ing3("ing 3", 3, 400, 100, 70, 30);
    Ingredient ing4("ing 4", 4, 800, 200, 40, 100);

    MenuItem item1("item 1", " discription 1", 450, {&ing1,&ing2,&ing4});
    MenuItem item2("item 2", " discription 2", 650, {&ing1,&ing3,&ing4});
    MenuItem item3("item 3", " discription 3", 800, {&ing3,&ing2,&ing4});

    Menu my_menu;

    my_menu.addMenuItem(&item1);
    my_menu.addMenuItem(&item2);
    my_menu.addMenuItem(&item3);

    StandartVisitor v1;
    DietVisitor v2;
    FitnessVisitor v3;

    cout << endl << endl << "Visitor 1" << endl;
    my_menu.getState(v1);
    cout << endl << endl << "Visitor 2" << endl;
    my_menu.getState(v2);
    cout << endl << endl << "Visitor 3" << endl;
    my_menu.getState(v3);


    cout << endl << endl << endl << "Task 3:" << endl;
    Herald* hr = new Herald;
    Doctor* dc = new Doctor;
    Blacksmith* bl = new Blacksmith;
    Child* chl = new Child;

    hr->registerObserver(dc);
    hr->registerObserver(bl);
    hr->registerObserver(chl);

    hr->setVoicePower(20);
    hr->setAnnouncement("Hello!");
    cout << endl;

    hr->setVoicePower(70);
    hr->setAnnouncement("World!");
    cout << endl;

    hr->setVoicePower(150);
    hr->setAnnouncement("Warning!");
    cout << endl;

    hr->removeObserver(dc);
    hr->setVoicePower(70);
    hr->setAnnouncement("World!");

    delete hr;
    delete dc;
    delete bl;
    delete chl;


    return 0;
}

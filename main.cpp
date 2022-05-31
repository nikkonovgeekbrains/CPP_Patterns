#include <iostream>
#include "fabric_method.h"
#include "bridge.h"
#include "builder.h"

int main() {
    cout << "Task 1:" << endl;
    Pizza* pizza1 = orderPizza("cheese");
    Pizza* pizza2 = orderPizza("greek");
    Pizza* pizza3 = orderPizza("pepperoni");
    pizza1->print();
    pizza2->print();
    pizza3->print();

    cout << endl << endl << "Task 2:" << endl;
    Director dir;
    AllInclusiveBuilder build_all;
    MinimumBuilder build_min;
    MediumBuilder build_med;

    cout << "Day 1:" << endl;
    MyDayEvents* mde1 = dir.createDayEvents(build_all);
    mde1->eventsList();

    cout << endl << endl << "Day 2:" << endl;
    MyDayEvents* mde2 = dir.createDayEvents(build_min);
    mde2->eventsList();

    cout << endl << endl << "Day 3:" << endl;
    MyDayEvents* mde3 = dir.createDayEvents(build_med);
    mde3->eventsList();
    

    cout << endl << endl << "Task 3:" << endl;
    Rectangle rec1(10,15);
    BrushImplementor bi(&rec1);
    PencilImplementor pi(&rec1);
    bi.drawRectangle(4);
    pi.drawRectangle(4);
    return 0;
}

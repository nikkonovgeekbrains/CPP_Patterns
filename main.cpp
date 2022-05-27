#include <iostream>
#include "strategy.h"
#include "myiterator.h"
#include "adapter.h"

int main() {
//    Task1
    TextEditor tx1("Hello world");
    tx1.Divide(DivideMethod::ByScreenWidth, 1);
    tx1.Divide(DivideMethod::BySentence, 2);        // В данном случае второй аргумент просто игнорируется, сделано чтобы у всех классов был схожий интерфейс
    tx1.Divide(DivideMethod::ByUserWidth, 3);

//    Task2
    cout << "vector:" << endl;
    vector<double> inp_vector = {10,1,2,3,5,7,8,6};
    MyArray<double, vector<double>> arr1(inp_vector);

    MyArray<double, vector<double>>::MyIterator it1 = arr1.begin();
    for(; it1 != arr1.end(); ++it1){
        cout<< *it1 <<" ";
    }
    cout<<endl<<endl;

    cout << "deque:" << endl;
    deque<double> inp_deq = {10,1,2,3,5,7,8,6};
    MyArray<double, deque<double>> arr2(inp_deq);

    MyArray<double, deque<double>>::MyIterator it2 = arr2.begin();
    for(; it2 != arr2.end(); ++it2){
        cout<< *it2 <<" ";
    }
    cout<<endl<<endl;

    cout << "list:" << endl;
    list<double> inp_list = {10,1,2,3,5,7,8,6};
    MyArray<double, list<double>> arr3(inp_list);

    MyArray<double, list<double>>::MyIterator it3 = arr3.begin();
    for(; it3 != arr3.end(); ++it3){
        cout<< *it3 <<" ";
    }
    cout<<endl<<endl;

//    Task3
    Text inp_text("Hello world!", 12);

    TextAdapter adapt_text(inp_text);
    cout << "Flip:" << endl;
    adapt_text.print();
    adapt_text.flip();
    adapt_text.print();

    cout << endl << "Rotate" << endl;
    cout << adapt_text.getAngle() << endl;
    adapt_text.rotate(15);
    cout << adapt_text.getAngle() << endl;

    cout << endl << "Scale:" << endl;
    adapt_text.printSize();
    adapt_text.scale(1.5);
    adapt_text.printSize();

    return 0;
}

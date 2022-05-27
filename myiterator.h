//
// Created by nikko on 27.05.2022.
//

#ifndef HW3_MYITERATOR_H
#define HW3_MYITERATOR_H

#include <iostream>
#include<vector>
#include <deque>
#include <list>

using namespace std;

template <typename T>
void print_vector(vector<T> inp_vector){
    for(int i = 0; i < static_cast<int>(inp_vector.size()); i++)
        cout << inp_vector[i] << " ";
    cout << endl;
}

template <typename var_T, typename cont_T>
class MyArray{
    cont_T arr;

public:

    MyArray(cont_T inp_arr): arr(inp_arr) {}

    cont_T get_data(){
        return arr;
    }
    void push_back(var_T num) { arr.push_back(num);}
    void clear() { arr.clear(); }

    class MyIterator {//«Итератор»почетнымчисламвмассиве
        cont_T& refArr;
        int curIndex;
        var_T* ptr;

    public:
        MyIterator(cont_T& ref) : refArr(ref),curIndex(-1), ptr(nullptr) { ++(*this); }
        void reset() { curIndex =-1; ptr =nullptr;}

        MyIterator &operator++ () {//префиксныйинкремент
            curIndex++;
            if(curIndex ==-1)
                curIndex =0;
            auto it = refArr.begin();
            for(int i = 0; i< curIndex; i++){
                it++;
            }
            ptr = &(*it);



            if(curIndex == refArr.size()){
                curIndex =-1;
                ptr =nullptr;
            }
            return *this;
        }

        MyIterator&operator-- () {//префексныйдекремент
            if(curIndex ==-1)
                curIndex = refArr.size() -1;

            ptr = &refArr[curIndex];


            if(curIndex ==-1)
                ptr =nullptr;

            return *this;
        }

        var_T& operator*() {//операцияразыменованияитератора
            auto it = refArr.begin();
            for(int i = 0; i< curIndex; i++){
                it++;
            }
            return *it;
            //return refArr.at(curIndex);
        }

        bool operator==(MyIterator it) {//проверканалог.равенствоитераторов
            if(curIndex == it.curIndex &&
               ptr == it.ptr &&
               refArr == it.refArr){
                return true;
            }
            return false;
        }

        bool operator!=(MyIterator it) {//проверканалог.неравенство
            return !(*this== it);
        }
    };

    MyIterator begin() { MyIterator it(arr); return it; }

    MyIterator end() { MyIterator it(arr); it.reset(); return it; }
};

template<typename var_T>
class MyArray<list<var_T>, var_T>{
    list<var_T> arr;

public:
    list<var_T> get_data(){
        return arr;
    }
    void push_back(var_T num) { arr.push_back(num);}
    void clear() { arr.clear(); }

    class MyIterator {//«Итератор»почетнымчисламвмассиве
        list<var_T>& refArr;
        int curIndex;
        var_T* ptr;

    public:
        MyIterator(list<var_T>& ref) : refArr(ref),curIndex(-1), ptr(nullptr) { ++(*this); }
        void reset() { curIndex =-1; ptr =nullptr;}

        MyIterator &operator++ () {//префиксныйинкремент
            curIndex++;
            if(curIndex ==-1)
                curIndex =0;
            ptr = &refArr[curIndex];



            if(curIndex == refArr.size()){
                curIndex =-1;
                ptr =nullptr;
            }
            return *this;
        }

        MyIterator&operator-- () {//префексныйдекремент
            if(curIndex ==-1)
                curIndex = refArr.size() -1;

            ptr = &refArr[curIndex];


            if(curIndex ==-1)
                ptr =nullptr;

            return *this;
        }

        var_T& operator*() {//операцияразыменованияитератора
            return refArr.at(curIndex);
            //return refArr.at(curIndex);
        }

        bool operator==(MyIterator it) {//проверканалог.равенствоитераторов
            if(curIndex == it.curIndex &&
               ptr == it.ptr &&
               refArr == it.refArr){
                return true;
            }
            return false;
        }

        bool operator!=(MyIterator it) {//проверканалог.неравенство
            return !(*this== it);
        }
    };

    MyIterator begin() { MyIterator it(arr); return it; }

    MyIterator end() { MyIterator it(arr); it.reset(); return it; }
};

#endif //HW3_MYITERATOR_H

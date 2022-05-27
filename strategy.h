//
// Created by nikko on 27.05.2022.
//
#include <fstream>
#include <iostream>
#ifndef HW3_STRATEGY_H
#define HW3_STRATEGY_H
using namespace std;

enum class DivideMethod{
    ByScreenWidth,
    ByUserWidth,
    BySentence
};

class MyDivide{
public:
    virtual ~MyDivide(){}
    virtual void use(int width=0) = 0;
};

class DivideByScreenWidth: public MyDivide{
    void use(int width=0){
        cout << "DivideByScreenWidth by screen width = " << width << endl;
    }
};

class DivideBySentence: public MyDivide{
    void use(int width=0){
        cout << "Divided by Sentences" << endl;
    }
};

class DivideByUserWidth: public MyDivide{
    void use(int width=0){
        cout << "DivideByScreenWidth by screen width = " << width << endl;
    }
};

class MyDividesBase{
protected:
    MyDivide* operation;

public:
    virtual ~MyDividesBase(){}
    virtual void useStrategy(int)=0;
    virtual void setStrategy(MyDivide* st)=0;
};

DivideByScreenWidth str1;
DivideBySentence str2;
DivideByUserWidth str3;

class ITextWork: public MyDividesBase{
public:
    virtual void Divide(DivideMethod, int) = 0;

    void useStrategy(int width=0){
        operation->use(width);
    }

    void setStrategy(MyDivide* st){
        operation = st;
    }
};

class TextEditor: ITextWork{
private:
    size_t EditorWidth;
    std::string all_text;



public:
    TextEditor(){};
    TextEditor(const std::string &text) : all_text(text) {};

    TextEditor(std::ifstream& file) {
        std::string line;
        if (file.is_open()){
            while (getline(file, line))
            {
                all_text+=line;
            }
        }
    }

    void PrintText() const{
        std::cout << all_text << std::endl;
    }



    void Divide(DivideMethod method, int width=0) override {
        switch (method) {
            case DivideMethod::ByScreenWidth:
                this->setStrategy(&str1);
                this->useStrategy(width);
//                DivideByScreenWidth();
                break;
            case DivideMethod::BySentence:
                this->setStrategy(&str2);
                this->useStrategy(width);
//                DivideBySentence();
                break;
            case DivideMethod::ByUserWidth:
                this->setStrategy(&str3);
                this->useStrategy(width);
//                DivideByUserWidth();
                break;
            default:
                this->setStrategy(&str1);
                this->useStrategy(width);
//                DivideByScreenWidth();

        }
    }
};


#endif //HW3_STRATEGY_H

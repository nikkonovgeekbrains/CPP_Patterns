//
// Created by nikko on 27.05.2022.
//

#ifndef HW3_ADAPTER_H
#define HW3_ADAPTER_H
#include <iostream>
#include <utility>

using namespace std;

class IShape{
public:
    virtual void scale(double scale_percentage) = 0;// Масштабируем фигуру
    virtual void rotate(double angle) = 0;          // Поворачиваем фигуру
    virtual void flip() = 0;                        // Отражаем фигуру
};

class Figure: IShape{
private:
    int width;
    int height;
    double angle;
    bool isFlipped;
public:
    Figure(int width, int height) : width(width), height(height), angle(0.0), isFlipped(false) {}

    void scale(double scale_percentage) override {
        width *= scale_percentage;
        height *= scale_percentage;
    }

    void rotate(double angle) override {
        angle += angle;
    }

    void flip() override {
        isFlipped = !isFlipped;
    }

    double getAngle() const{
        return angle;
    };
};

class IText{
    virtual void newSize(int size) = 0;   // Изменяем размер шрифта текста
    virtual void rotate(double angle) = 0;   // Поворачиваем текст
    virtual void reverse() = 0;              // Изменяем направление текста
};

class Text: IText{
private:
    int size;
    double angle;
    bool isReversed;
    std::string text;
public:
    Text(const std::string text, int size, double angle=0, bool isReversed=false) : text(text), size(size), angle(angle), isReversed(isReversed) {}

    void newSize(int newSize) override {
        size = newSize;
    }

    int getSize() const{
        return size;
    }

    double getAngle() const{
        return angle;
    }

    void rotate(double newAngle) override {
        angle = newAngle;
    }

    void reverse() override {
        for (int i = 0; i < text.size()/2; ++i) {
            char c = text[i];
            text[i] = text[text.size() - 1 - i];
            text[text.size() - 1 - i] = c;
        }
        isReversed = !isReversed;
    }

    void print(){
        cout << text << endl;
    }
};

class TextAdapter : public Figure{
private:
    Text text;
public:
    TextAdapter(Text inp_text) : Figure(0, 0), text(std::move(inp_text)) {}

    void scale(double scale_percentage) override {
        text.newSize(int(text.getSize() * scale_percentage));
    }

    void rotate(double angle) override{
        text.rotate(angle);
    }

    void flip() override{
        text.reverse();
    }

    void print(){
        text.print();
    }

    double getAngle() const{
        return text.getAngle();
    }

    void printSize() const{
        cout << text.getSize() << endl;
    }
};

#endif //HW3_ADAPTER_H

#ifndef HW4_BRIDGE_H
#include <iostream>

using namespace std;

// Abstraction
class Shape {
public:
    virtual void draw()= 0; // low-level
    virtual void resize(double pct) = 0; // high-level
    virtual ~Shape() {
    }
};

class Rectangle: public Shape{
private:
    double height;
    double width;
public:
    Rectangle(double width, double height): width(width), height(height) {}
    void draw(){
        cout << "Draw our rectangle";
    }

    void resize(double pct){
        cout << "Resize our rectangle with coef " << pct << ". ";
        height *= pct;
        width *= pct;
        cout << "New size: " << width << "x" << height << "." << endl;
    }
};

// Implementor
class DrawingImplementor {
protected:
    Rectangle* rect;
public:
    DrawingImplementor(Rectangle *rect): rect(rect) {}
    virtual void drawRectangle(double) = 0;

    virtual ~DrawingImplementor() {
    }
};

class BrushImplementor: public DrawingImplementor {
public:
    BrushImplementor(Rectangle *rec): DrawingImplementor(rec){}
    void drawRectangle(double line_width){
        rect->draw();
        cout << " with brush." << endl;
    }

    virtual ~BrushImplementor() {
    }
};

class PencilImplementor: public DrawingImplementor {
public:
    PencilImplementor(Rectangle *rec): DrawingImplementor(rec){}
    void drawRectangle(double line_width){
        rect->draw();
        cout << " with pencil." << endl;
    }

    virtual ~PencilImplementor() {
    }
};
#define HW4_BRIDGE_H

#endif //HW4_BRIDGE_H

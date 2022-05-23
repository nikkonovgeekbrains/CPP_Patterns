#include <iostream>
using namespace std;

enum Colors {
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    CYAN,
    BLUE,
    VIOLET,
    WHITE
};

Colors& operator++( Colors &c ) {
    using IntType = typename std::underlying_type<Colors>::type;
    if ( c == Colors::WHITE )
        c = static_cast<Colors>(0);
    else
        c = static_cast<Colors>( static_cast<IntType>(c) + 1 );
    return c;
}

Colors& operator--( Colors &c ) {
    using IntType = typename std::underlying_type<Colors>::type;
    if ( c == Colors::RED )
        c = Colors::WHITE;
    else
        c = static_cast<Colors>( static_cast<IntType>(c) - 1);
    return c;
}

class Light{
public:
    Light():state(false), color(Colors::WHITE){};
    void On(){
        if(!state){
            state = true;
        }
    };

    void Off(){
        if(state){
            state = false;
        }
    };

    void changeColor(Colors newColor){
        color = newColor;
    }

    bool getState() const {
        return state;
    }

    Colors getColor() const{
        return color;
    }

    void printColorNumber() const{
        cout << static_cast<int>(color) << endl;
    }

private:
    bool state;
    Colors color;
};

class Command{
protected:
    Light* light;
public:
    virtual ~Command() {};
    virtual  void Execute() = 0;
    virtual void Back() = 0;

    void setLight(Light* _light){
        light = _light;
    }
};

class ChangeColorCommand : public Command{
    Colors color;
public:
    ChangeColorCommand(Colors color) : color(color) {}

    void Execute() override{
        if(light->getState())       // Разрешаем переключаеть цвет только на включенной лампочке
            light ->changeColor(++color);
        else
            cout << "Light is off" << endl;
    }

    void Back() override{
        if(light->getState())       // Разрешаем переключаеть цвет только на включенной лампочке
            light ->changeColor(--color);
        else
            cout << "Light is off" << endl;
    }
};



int main() {
//    std::cout << "Hello, World!" << std::endl;
    Light *my_light = new Light;
    my_light->printColorNumber();
    ChangeColorCommand my_cmd = ChangeColorCommand(my_light->getColor());
    my_cmd.setLight(my_light);
    my_cmd.Execute();       //Выведет Light is off
    my_light->On();
    my_cmd.Execute();
    my_light->printColorNumber();
    my_cmd.Execute();
    my_light->printColorNumber();
    my_cmd.Back();
    my_light->printColorNumber();
    my_cmd.Back();
    my_light->printColorNumber();
    my_light->Off();
    my_cmd.Back();          //Выведет Light is off
    return 0;
}

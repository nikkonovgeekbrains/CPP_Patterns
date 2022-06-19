//
// Created by nikko on 19.06.2022.
//

#ifndef HW5_KONOVALTSEV_FACADE_H
#define HW5_KONOVALTSEV_FACADE_H
#include <iostream>
using namespace std;


class Device{
public:
    std::string type;

    Device(const std::string &type) : type(type) {}
    virtual void On(){
        std::cout << type <<" is on" << std::endl;
    }
    virtual void Off(){
        std::cout << type <<" is off" << std::endl;
    }


};

class MediaPlayer: public Device{
private:
    std::string currentMovie;
public:
    MediaPlayer(const std::string &type) : Device(type) {}
    void play(std::string newMovie) {
        currentMovie = newMovie;
        std::cout << "Movie " << currentMovie << " started" << std::endl;

    }
};

class Amplifier: public Device{

    Device* streamingPLayer;
    int volume;
public:
    Amplifier(const std::string &type) : Device(type), volume(0) {}
    void setStreamingPlayer(Device* d){
        streamingPLayer = d;
        std::cout << "Streaming player is " << d->type << std::endl;
    }

    void setSurroundSound(){
        std::cout << "Surround Sound Mode" << std::endl;
    };

    void setVolume(int v){
        volume = v;
    }

};

class Projector: public Device{
private:
    Amplifier* _amplifier;
    Device* _input;
public:
    Projector(const std::string &type) : Device(type) {}

    void setInput(Device* d){
        _input = d;
        std::cout << "Projector input is " << d->type << std::endl;
    }
    void wideScreenMode(){
        std::cout << "Wide Screen Mode" << std::endl;
    };
};

class Tuner{
private:
    Amplifier* _amplifier;
public:
    void on(){
        std::cout << "Tuner on" << std::endl;
    }

    void off(){
        std::cout << "Tuner off" << std::endl;
    }
};

class Popper: public Device{
public:
    Popper(const std::string &type) : Device(type) {}

    void pop(){
        std::cout << "Popcorn will be ready soon" << std::endl;
    }
};

class Lights: public Device{
private:
    int currentLight;
public:
    Lights(const std::string &type) : Device(type), currentLight(100) {}
    void dim(int light){
        currentLight = light;
    }
};

class Screen: public Device{
public:
    Screen(const std::string &type) : Device(type) {}
    void down(){
        std::cout << "Screen is down" << std::endl;
    };
    void up(){
        std::cout << "Screen is up" << std::endl;
    };
};

class MyFacade{
private:
    enum States{
        All_off, Popper_on, Popper_pop, Popper_off, Light_dim, Screen_down, Projector_on, Projector_set_input,
        Projector_wide_scr_mode, Amp_on, Amp_set_strm_plr, Amp_set_surround_sound, Amp_set_volume,
        Mp_on, Mp_play
    };
    MediaPlayer* _mp = new MediaPlayer("media player");
    Popper _popper = Popper("popper");
    Lights _light = Lights("light");
    Projector _projector = Projector("projector");
    Screen _screen = Screen("screen");
    Amplifier _amp = Amplifier("Amplifier");

    int _state;
public:

    MyFacade(){
        _state = All_off;
    }

private:
    bool checkOnStatus(){
        switch (_state) {
            case All_off:
                _popper.On();
                _state++;
                return false;

            case Popper_on:
                _popper.pop();
                _state++;
                return false;

            case Popper_pop:
                _popper.Off();
                _state++;
                return false;

            case Popper_off:
                _light.dim(0);
                _state++;
                return false;

            case Light_dim:
                _screen.down();
                _state++;
                return false;

            case Screen_down:
                _projector.On();
                _state++;
                return false;

            case Projector_on:
                _projector.setInput(_mp);
                _state++;
                return false;

            case Projector_set_input:
                _projector.wideScreenMode();
                _state++;
                return false;

            case Projector_wide_scr_mode:
                _amp.On();
                _state++;
                return false;

            case Amp_on:
                _amp.setStreamingPlayer(_mp);
                _state++;
                return false;

            case Amp_set_strm_plr:
                _amp.setSurroundSound();
                _state++;
                return false;

            case Amp_set_surround_sound:
                _amp.setVolume(5);
                _state++;
                return false;

            case Amp_set_volume:
                _mp->On();
                _state++;
                return false;

            case Mp_on:
                _mp->play("Star Wars");
                _state++;
                return false;

            case Mp_play:
                return true;

            default:
                return false;
        }
    }

    bool checkOffStatus(){
        if (_state >= Mp_on){
            _mp->Off();
            _state = Amp_set_volume;
        }

        else if (_state >= Amp_on){
            _amp.Off();
            _state = Projector_wide_scr_mode;
        }

        else if (_state >= Projector_on){
            _projector.Off();
            _state = Screen_down;
        }

        else if (_state == Screen_down){
            _screen.up();
            _state--;
        }

        else if (_state == Light_dim){
            _light.dim(10);
            _state--;
        }

        else if (_state >= Popper_on){
            _popper.Off();
            _state = All_off;
            return true;
        }
        return false;
    }

public:
    void play_movie(){
        while (!checkOnStatus()){}
    }

    void off_all(){
        while(!checkOffStatus()){}
    }
};

#endif //HW5_KONOVALTSEV_FACADE_H

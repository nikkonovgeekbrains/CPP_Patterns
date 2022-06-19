//
// Created by nikko on 19.06.2022.
//

#ifndef HW5_KONOVALTSEV_OBSERVER_H
#define HW5_KONOVALTSEV_OBSERVER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;


class ICitizen{
public:
    virtual void listen(int, std::string) = 0;
};

class Isubject{
public:
    virtual void registerObserver(ICitizen* observer) = 0;
    virtual void removeObserver(ICitizen* observer) = 0;
    virtual void notifyObservers() = 0;
};

class Doctor: public ICitizen{
private:
    int hearingPower = 100;
public:
    void listen(int voicePower, std::string ann) override {
        cout << "Doctor hears: ";
        if (voicePower >= hearingPower)
            cout << ann << endl;
        else
            cout << "nothing" << endl;
    }
};

class Blacksmith: public ICitizen{
private:
    int hearingPower = 30;
public:
    void listen(int voicePower, std::string ann) override {
        cout << "Blacksmith hears: ";
        if (voicePower >= hearingPower)
            cout << ann << endl;
        else
            cout << "nothing" << endl;
    }
};

class Child: public ICitizen{
private:
    int hearingPower = 50;
public:
    void listen(int voicePower, std::string ann) override {
        cout << "Child hears: ";
        if (voicePower >= hearingPower)
            cout << ann << endl;
        else
            cout << "nothing" << endl;
    }
};

class Herald: public Isubject{
private:
    int voicePower;
    std::string announcement;
    std::vector<ICitizen*> citizens;

public:
//    Herald() : citizens(citizens) {
//        citizens = {new Doctor, new Child, new Blacksmith};
//    }

    void registerObserver(ICitizen* observer) override{
        citizens.push_back(observer);
    }
    void removeObserver(ICitizen* observer) override{
        auto it = std::find(citizens.begin(), citizens.end(), observer);
        citizens.erase(it);
    }
    void notifyObservers() override{
        for(auto& citizen: citizens){
            citizen->listen(voicePower, announcement);
        }
    }

    int getVoicePower();
    string getAnnouncement();
    void setVoicePower(int);
    void setAnnouncement(std::string);

//    void changeAnnouncment(){
//        for(const auto citizen : citizens){
//            citizen->listen(voicePower, announcement);
//        }
//    }
};

int Herald::getVoicePower() {
    return voicePower;
}

string Herald::getAnnouncement() {
    return announcement;
}

void Herald::setVoicePower(int vp) {
    voicePower = vp;
}

void Herald::setAnnouncement(std::string ann) {
    announcement = ann;
    notifyObservers();

}

#endif //HW5_KONOVALTSEV_OBSERVER_H

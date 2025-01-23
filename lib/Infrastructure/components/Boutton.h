#ifndef BOUTTON_H
#define BOUTTON_H

#include<Arduino.h>

#include "../../include/BSP.hpp"


class Boutton{
private:
    int _pin;
    bool etat;
    bool etatPresidente = false;

public:
    Boutton(int pin):
        _pin(pin)
    {}
    ~Boutton()
    {}
    
    void init(){
        pinMode(_pin, INPUT);
        etat = digitalRead(_pin);
    }
    bool estClicke(){
        etat = digitalRead(_pin);
        return etat;
    }
    
    void setPin(int pin){
        pin = pin;
    }
    int getPin(){
        return _pin;
    }
    
    void setEtat(bool etatBoutton){
        etat = etatBoutton;
    }
    bool getEtat(){
        return etat;
    }

    void setEtatPresidente(bool etatBoutton){
        etatPresidente = etatBoutton;
    }
    bool getEtatPresidente(){
        return etatPresidente;
    }
};

#endif
#ifndef L298N_H
#define L298N_H

#include <Arduino.h>
#include"../../include/BSP.hpp"

class L298N
{
private:
    int _motorPin1;
    
    bool _motorState;
    bool _motorSensor;
    
public:
    L298N(int motor1Pin1):
        _motorPin1(motor1Pin1)
    {
        
    }
    ~L298N(){
        
    }
    void init();
    void turnOffMotor();
    void turnOnMotor();
};

void L298N::init(){
    pinMode(_motorPin1, OUTPUT);
    digitalWrite(_motorPin1, TURN_OFF_MOTOR_1);
    _motorState = MOTOR_1_TURNED_ON;
}

void L298N::turnOffMotor(){
    digitalWrite(_motorPin1, TURN_OFF_MOTOR_1);
}
void L298N::turnOnMotor(){
    digitalWrite(_motorPin1, TURN_ON_MOTOR_1);
}


#endif
#ifndef DRIVERL298N
#define DRIVERL298N

#include"../components/L298N.h"

class DriverL298N
{
private:
    
public:
    L298N &_l298n;
    
    DriverL298N(L298N &l298n):
        _l298n(l298n)
    {}
    ~DriverL298N()
    {}
    void monterAscenseur();
    void decendreAscenseur();
    void arreter();
};

void DriverL298N::monterAscenseur(){
    _l298n.turnOnMotor();
}
void DriverL298N::decendreAscenseur(){
    _l298n.turnOnMotor();
}
void DriverL298N::arreter(){
    _l298n.turnOffMotor();
}


#endif
#ifndef DRIVERIRBOUTTON_H
#define DRIVERIRBOUTTON_H

#include"../components/Boutton.h"

class DriverBoutton
{
private:
    
public:
    Boutton &_boutton;

    DriverBoutton(Boutton &boutton):
        _boutton(boutton)
    {

    }
    ~DriverBoutton()
    {}
    
    bool estclicke();
    bool estFrontDescendente();
};

bool DriverBoutton::estclicke(){
    
    return _boutton.estClicke();
}
bool DriverBoutton::estFrontDescendente(){
    return (_boutton.getEtatPresidente() == true && _boutton.getEtat() == false);
}


#endif
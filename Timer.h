#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED
#include <SDL.h>
class Timer
{
private:
    Uint32 temps;
    bool firstTime=true;
public:
    Timer();
    bool attendre(int seconde);
};


#endif // TIMER_H_INCLUDED

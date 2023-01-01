#include"timer.h"
Timer::Timer()
{
    temps=0;
}
bool Timer::attendre(int seconde)
{
    if(firstTime){
        temps=SDL_GetTicks();
        firstTime=false;
    }
    if(SDL_TICKS_PASSED(SDL_GetTicks(),temps+seconde)==SDL_TRUE)
    {
        temps=SDL_GetTicks();
        return true;
    }
    return false;
}

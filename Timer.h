#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED
class Timer{
private:
    int temps;
    int c_time;
public:
    Timer(){
        c_time=0;
        temps=SDL_GetTicks();
    }
    void update(){
         c_time=SDL_GetTicks();
    }
    bool attendre(int seconde){
        temps=SDL_GetTicks();
        if(temps-c_time>seconde){
            c_time=temps;
            update();
            return true;
        }
        //update();
        return false;

    }
};
#endif // TIMER_H_INCLUDED

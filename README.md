# Simple SDL GUI Library for Game and Application (in delevelopment)
## You should need to have
first of all you need this SDL_Version :
>[SDL2.0.16 or up](https://pages.github.com/)
## Sample example
```c++
#include<SDL.h>
#include<iostream>

//header for font loading 
#include"FontManager.h"

//header for any state declaration
#include"AppStateMachine.h"

//header for bunch of gui (button,text,image,...)
#include"Widgets.h"

//state of the current Window
class MainState:public AppState{
private:
    UI_Button *btn;
public:
    static std::string stateID;
    MainState(Window *pWindow):AppState(pWindow){}

    bool onEnter()override{
        btn=new UI_Button(referenceWindow->getRenderer(),"ftexte","hello",10,10);
        btn->setOnClick([&]()->void{
            //exit the window
            referenceWindow->quit();
        });
        return true;
    }
    bool onExit()override{
        delete btn;
        return true;
    }

    void update()override{
        btn->update();
    }
    void render()override{
        btn->draw(referenceWindow->getRenderer());
    }

    std::string getStateID()const override{
        return stateID;
    }
};
std::string MainState::stateID="MAINSTATE";

//main window to display widget
class MyWindow:public Window{
private:
    AppStateMachine *states;
public:
    MyWindow():Window(){}
    
    MyWindow(std::string pTitle,int pX,int pY,int pW,int pH,Uint32 pFlagsWindow=SDL_WINDOW_SHOWN):Window(pTitle,pX,pY,pW,pH,pFlagsWindow){
        states=new AppStateMachine();
        states->pushState(new MainState(this));
    }
    
    void update()override{
        states->update();
    }
    
    void draw()override{
        SDL_RenderClear(getRenderer());
        SDL_SetRenderDrawColor(getRenderer(),255,255,255,255);
            states->render();
        SDL_RenderPresent(getRenderer());
    }
};

int main(int argc,char *argv[]){
    thefontManager::Instance()->load("font.ttf",30,"ftexte");
    MyWindow wind("teste Graphic lab",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640,480);
    while(wind.isRunning()){
        wind.handleEvent();
        wind.update();
        wind.draw();
    }
    wind.clean();
    return 0;
}
```

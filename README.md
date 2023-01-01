# Simple SDL GUI Library for Game and Application (in development)
## You should need to have
first of all you need this SDL_Version :
>[SDL2.0.16 or up](https://github.com/libsdl-org/SDL/releases/)

>[SDL_ttf 2.20.1 or up](https://github.com/libsdl-org/SDL_ttf/releases)

>[SDL_image 2.6.2 or up](https://github.com/libsdl-org/SDL_image/releases)

## Sample example
>few inclusion
```c++
    #include<SDL.h>
    //header for external font loading 
    #include"../include/FontManager.h"
    
    //header for any state declaration
    #include"../include/AppStateMachine.h"

    //header for bunch of gui (button,text,image,...)
    #include"../include/Widgets.h"
```
>create a state for the main Window

```c++
//state of the main Window
class MainState:public AppState{
private:
    UI_Button *btn;
public:
    static std::string stateID;
    MainState(Window *pWindow):AppState(pWindow){}

    bool onEnter()override{
        //initialization all stuff widget before to go displayed
        btn=new UI_Button(referenceWindow->getRenderer(),"ftexte","hello!",10,10);
        btn->onClickAttachTo([&](){
            //when the button is pressed close the window!
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
```
>declaration of mainWindow 
notice that one window can have **one** or **more** state according to your choices

```c++
//main window to display widget
class MyWindow:public Window{
private:
    AppStateMachine *states;
public:
    
    MyWindow():Window(){}
    
    MyWindow(std::string pTitle,
                    int  pX,
                    int  pY,
                    int  pW,
                    int  pH,
                    Uint32 pFlagsWindow=SDL_WINDOW_SHOWN):Window(pTitle,
                                                                 pX,
                                                                 pY,
                                                                 pW,
                                                                 pH,
                                                                 pFlagsWindow){
        states=new AppStateMachine();
        states->pushState(new MainState(this));
    }
    
    void update()override{
        states->update();
    }
    
    //when the window is drawing
    void draw()override{
        SDL_SetRenderDrawColor(getRenderer(),255,255,255,255);
        SDL_RenderClear(getRenderer());
            states->render();
        SDL_RenderPresent(getRenderer());
    }

    //when the window is cleaning
    void clean()override{
        Window::clean();
        states->clear();
        thefontManager::Instance()->cleanUp();
    }
};
```

>there is the **main** program

```c++
int main(int argc,char *argv[]){
    //loading a font for displaying to the button
    thefontManager::Instance()->load("font.ttf",20,"ftexte");

    //create a window
    MyWindow wind("my Window",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640,480);
    
    while(wind.isRunning()){
        wind.handleEvent();
        wind.update();
        wind.draw();
    }
    //clear window allocation and free up memory
    wind.clean();
    return 0;
}
```

## The ouput

![result](/screenshoots/sample.jpg)

feel free to commit :)

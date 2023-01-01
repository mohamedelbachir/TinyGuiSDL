#pragma once
#ifndef INPUTMANAGER_H_INCLUDED
#define INPUTMANAGER_H_INCLUDED
#include<map>
#include<vector>

#include<SDL.h>
#include"Window.h"
enum
{
    LEFT,
    RIGHT,
    MIDDLE
};
enum window_states
{
    KEYBOARD_FOCUS,
    MOUSE_FOCUS,
    SIZE_CHANGED
};

enum button_state
{
    MOUSE_OUT,
    MOUSE_HOVER,
    CLICKED
};
struct statesWindow{
    std::map<window_states,bool>s;
};
class InputManager
{
private:

    std::vector<bool> m_mouseStates;

    std::map<Uint32,statesWindow> m_windowState;

    bool isDroppedFile=false;

    char *fileDroped;

    static InputManager *instanceInput;

    SDL_Point m_mousePosition;

    const Uint8 *m_keyState;

    InputManager();

    ~InputManager() {}

    SDL_Event event;

    int m_mouseWhellVelocity=0;
public:
    static InputManager* instance()
    {
        if(instanceInput==NULL)
        {
            instanceInput=new InputManager();
        }
        return instanceInput;
    }
    void setEventHandler(SDL_Event *e){
        event=*e;
    }
    int getMouseWhellVelocity(){
        return m_mouseWhellVelocity;
    }

    bool getWindowState(window_states s,Uint32 windId)
    {
        return m_windowState[windId].s[s];
    }

    void setWindowState(Uint32 s,Uint32 windId)
    {
        SDL_Event customEvent;
        customEvent.window.windowID=windId;
        customEvent.window.type=s;
        SDL_PushEvent(&customEvent);
    }

    bool isDropFile();

    char *getFileDropped();

    /**
    @brief isKeyDown
    function to get Input of user
    @param key:the Key who pressed
    @return true if is pressed
    */
    bool isKeyDown(SDL_Scancode key);

    /**
    @brief getMousePosition
    function to allow to get mouse coordinate on window
    @return position of mouse in window
    */
    SDL_Point getMousePosition();

    /** @brief update
    * function for Update the InputHandler associate to specific Window
    * @sa init
    */
    void update(Window *pWindow);

    /** @brief getMouseState
    * function to get the Current Mouse State Clicked
    * @return true if the specific mouse button is clicked
    */
    bool getMouseState(int pMouseState);

    /** @brief getEvent
    * function to get the Current Event enumration
    */
    SDL_Event getEvent();

    /** @brief clean
    * function to clean all allocate Memory for initialization of the instance of InputHandler
    */
    void clean();
};
typedef InputManager theInputManager;
#endif // INPUTMANAGER_H_INCLUDED

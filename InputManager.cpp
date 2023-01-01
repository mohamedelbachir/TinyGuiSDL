#include"InputManager.h"
#include"Window.h"
InputManager* InputManager::instanceInput=NULL;

InputManager::InputManager()
{
    for(int i=0; i<3; i++)
    {
        m_mouseStates.push_back(false);
    }

}

SDL_Event InputManager::getEvent()
{
    return event;
}
bool InputManager::isDropFile(){
    return isDroppedFile;
}

char* InputManager::getFileDropped(){
    return fileDroped;
}

void InputManager::update(Window *pWindow)
{
    m_keyState=SDL_GetKeyboardState(0);
    bool isMouseWhell=false;
    while(SDL_PollEvent(&event))
    {
        switch(event.drop.type)
        {
            case SDL_DROPBEGIN:
            case SDL_DROPCOMPLETE:
                isDroppedFile=true;
                break;
            case SDL_DROPFILE:
                fileDroped=event.drop.file;
            default:
                isDroppedFile=false;
            break;
        }
        switch(event.type)
        {
        case SDL_MOUSEWHEEL:
           isMouseWhell=true;
           m_mouseWhellVelocity=event.wheel.y;
        break;

        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button==SDL_BUTTON_LEFT)
            {
                m_mouseStates[LEFT]=true;
            }
            if(event.button.button==SDL_BUTTON_RIGHT)
            {
                m_mouseStates[RIGHT]=true;
            }

            if(event.button.button==SDL_BUTTON_MIDDLE)
            {
                m_mouseStates[MIDDLE]=true;
            }

            break;

        case SDL_MOUSEBUTTONUP:
            if(event.button.button==SDL_BUTTON_LEFT)
            {
                m_mouseStates[LEFT]=false;
            }

            if(event.button.button==SDL_BUTTON_RIGHT)
            {
                m_mouseStates[RIGHT]=false;
            }

            if(event.button.button==SDL_BUTTON_MIDDLE)
            {
                m_mouseStates[MIDDLE]=false;
            }

            break;

        case SDL_MOUSEMOTION:
            m_mousePosition.x=event.motion.x;
            m_mousePosition.y=event.motion.y;
            break;

        case SDL_WINDOWEVENT:
            window_states s;
            bool state=false;
            switch(event.window.event)
            {
            case SDL_WINDOWEVENT_ENTER:
                s=KEYBOARD_FOCUS;
                state=true;
                break;

            case SDL_WINDOWEVENT_LEAVE:
                s=MOUSE_FOCUS;
                state=false;
                break;

            case SDL_WINDOWEVENT_FOCUS_GAINED:
                s=KEYBOARD_FOCUS;
                state=true;
                break;

            case SDL_WINDOWEVENT_FOCUS_LOST:
                s=KEYBOARD_FOCUS;
                state=false;
                break;

            case SDL_WINDOWEVENT_CLOSE:
                if(event.window.windowID==SDL_GetWindowID(pWindow->getWindow()))
                {
                    pWindow->quit();
                }
                break;
            }
            m_windowState[event.window.windowID].s[s]=state;
            break;
        }
    }
    if(!isMouseWhell){
        m_mouseWhellVelocity=0;
    }
}

bool InputManager::getMouseState(int pMouseState)
{
    return m_mouseStates[pMouseState];
}

SDL_Point InputManager::getMousePosition()
{
    return m_mousePosition;
}

bool InputManager::isKeyDown(SDL_Scancode key)
{
    if(m_keyState!=NULL)
    {
        if(m_keyState[key]==1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}


void InputManager::clean()
{

}

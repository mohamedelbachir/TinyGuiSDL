#include<iostream>
#include "Window.h"
#include "InputManager.h"

void Window::handleEvent()
{
    theInputManager::instance()->update(this);
}

bool Window::isRunning()
{
    return m_running;
}

void Window::quit()
{
    m_running=false;
}

Uint32 Window::getIDWindow(){
    return m_windowID;
}

SDL_Window *Window::getWindow(){
    return m_window;
}

SDL_Renderer *Window::getRenderer(){
    return m_renderer;
}

void Window::clean()
{
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
}

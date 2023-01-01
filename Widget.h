#ifndef WIDGET_H_INCLUDED
#define WIDGET_H_INCLUDED
#include<SDL.h>
#include<functional>
#include<iostream>
#include"Vector2D.h"
#include"InputManager.h"
#include"Timer.h"
enum type{
    FILL,
    BORDER
};

class Widget
{
protected :

    Timer t;
    int m_width;

    int m_height;

    bool m_display=true;

    std::string ID;

    Uint8 m_opacity=SDL_ALPHA_OPAQUE;

    Vector2D velocity=Vector2D(0,0);

    Vector2D acceleration=Vector2D(0,0);

    double m_angle=0.0f;

    SDL_RendererFlip m_flip=SDL_FLIP_NONE;

    Vector2D m_position;

    Vector2D *m_posMouseRef;

    SDL_Color fcolor[3]={SDL_Color{121,121,121,255},SDL_Color{255,255,255,255},SDL_Color{0,0,0,255}};

    SDL_Color bcolor[3]={SDL_Color{0,0,0,255},SDL_Color{0,0,0,255},SDL_Color{255,255,255,255}};

    int m_currentFrame=MOUSE_OUT;

    std::function<void()> m_callback;

    std::function<void()> m_callback_update;

    int timeToUpate=0;

    int state_update;

    bool isSetEventToUpdate=false;

    bool m_bRealease=true;

    bool hasParent=false;

    int m_rad=1;

    void checkEventToUpdate(){
        if(isSetEventToUpdate){
            if(t.attendre(timeToUpate)){
                if(m_currentFrame==state_update){
                    m_callback_update();
                }else{
                    if(state_update==3){
                        m_callback_update();
                    }
                }
            }
        }
    }
public:


    /**
         @brief SetDisplay
           function useful to display a widget
         @param enable: boolean to enable or disable the display
     */
    void setDisplay(bool pEnable)
    {
        m_display=pEnable;
    }

    /**
        @brief getDisplay
          function to get a current display of widget
        @return true if it visible , false otherwise
    */
    bool getDisplay()
    {
        return m_display;
    }

    /**
        @brief getWidth()
         function to get Width of Widget
        @return width
    */
    int getWidth()
    {
        return m_width;
    }

    /**
        @brief getHeight()
         function to get Height of Widget
        @return height
    */
    int getHeight()
    {
        return m_height;
    }

    /**
        @brief getVector()
         function to get Position()
        @return height
    */
    Vector2D* getVector()
    {
        return &m_position;
    }
    /**
        @brief Update
           function to update a specific widgets
    */
    virtual void update()
    {
        velocity+=acceleration;
        m_position+=velocity;

        checkEventToUpdate();

        Vector2D mousePosition=Vector2D(theInputManager::instance()->getMousePosition().x,theInputManager::instance()->getMousePosition().y);
        if(theInputManager::instance()->getMouseState(LEFT)&&m_currentFrame!=MOUSE_HOVER)
        {
            m_bRealease=false;
        }
        Vector2D position=Vector2D(0,0);
        if(m_posMouseRef!=NULL&&hasParent){
            position+=*m_posMouseRef;
        }
        position+=m_position;
        if(mousePosition.getX()<(position.getX()+m_width) &&mousePosition.getX()>position.getX()&&mousePosition.getY()<(position.getY()+m_height)&&mousePosition.getY()>position.getY())
        {

            if(theInputManager::instance()->getMouseState(LEFT)&&m_bRealease)
            {
                m_currentFrame=CLICKED;
                if(m_callback!=nullptr){
                    m_callback();
                }
                //resize(m_width+30,m_height+10);
                m_bRealease=false;
            }
            else if(!theInputManager::instance()->getMouseState(LEFT))
            {
                m_currentFrame=MOUSE_HOVER;
                m_bRealease=true;
            }
        }
        else
        {
            m_currentFrame=MOUSE_OUT;
        }
    }

    /**
        @brief ~Widget
           destructor of Widget

    */
    virtual ~Widget() { };

    /**
        @brief show
           function to draw a widgets
    */
    virtual void draw(SDL_Renderer *pRenderer)=0;

    /**
    */
    void setPositionMouseRelative(Vector2D *pos)
    {
        if(pos==NULL)
        {
            std::cout<<"val nulle"<<std::endl;
            throw "Invalid !!!";
        }
        m_posMouseRef=pos;
        hasParent=true;
    }

    /***/
    Vector2D* getPositionMouseRelative()
    {
        return m_posMouseRef;
    }

    void setTransparency(Uint8 lvl){
        m_opacity=lvl;
    }

    /**
        @brief resize
           function to resize a widgets
    */
    virtual void resize(int w,int h)
    {
        m_width=w;
        m_height=h;
    }

    /***/
    virtual void setColorState(Uint8 r,Uint8 g,Uint8 b,Uint8 a,button_state state,type t=FILL){

        switch(t){
            case FILL:
                fcolor[state].r=r;
                fcolor[state].g=g;
                fcolor[state].b=b;
                fcolor[state].a=a;
            break;

            case BORDER:
                bcolor[state].r=r;
                bcolor[state].g=g;
                bcolor[state].b=b;
                bcolor[state].a=a;
        }
    }
    int getCurrentState(){
        return m_currentFrame;
    }

    void setAllStateColor(Uint8 r,Uint8 g,Uint8 b,Uint8 a,type t=FILL){
        setColorState(r,g,b,a,MOUSE_HOVER,t);
        setColorState(r,g,b,a,MOUSE_OUT,t);
        setColorState(r,g,b,a,CLICKED,t);
    }

    void onClickAttachTo(std::function<void()>f){
        m_callback=f;
    }

    void onUpdate(std::function<void()>f,int time=0,int state=3){
        m_callback_update=f;
        timeToUpate=time;
        state_update=state;
        isSetEventToUpdate=true;
    }

    std::string getID(){
        return ID;
    }

    Vector2D* getVelocity(){
        return &velocity;
    }

    Vector2D getAcceleration(){
        return acceleration;
    }

    void setAcceleration(Vector2D a){
        acceleration=a;
    }

    /**
        @brief rotateFlip
        function that allow rotation of the specific Texture Widgets
        @param angle: angle of rotation
        @param flip: flip or not , by default not flip
    */
    void rotateFlip(double pAngle,SDL_RendererFlip pFlip=SDL_FLIP_NONE){
        this->m_angle=pAngle;
        this->m_flip=pFlip;
    }

    /**
        @brief clean
           function to clean a widgets
    */
    virtual void clean()
    {

    }

};
#endif // WIDGET_H_INCLUDED

#ifndef VECTOR2D_H_INCLUDED
#define VECTOR2D_H_INCLUDED
#include"Timer.h"
#include<cmath>
#include<iostream>
class Vector2D{
private:
    float m_x;
    float m_y;
    Timer tanim;
public:

    Vector2D(){
        m_x=0.0f;
        m_y=0.0f;
    }

    Vector2D(float x,float y){
        m_x=x;
        m_y=y;
    }

    int lenght(){
        return sqrt(m_x*m_x+m_y*m_y);
    }
    float getX(){
        return m_x;
    }
    float getY(){
        return m_y;
    }
    void setX(float x){
        m_x=x;
    }
    void setY(float y){
        m_y=y;
    }

    void setVector(float x,float y){
        m_x=x;
        m_y=y;
    }

    Vector2D operator +(Vector2D const &v){
        return Vector2D(m_x+v.m_x,m_y+v.m_y);
    }

    void operator +=(Vector2D const &v){
        this->m_x+=v.m_x;
        this->m_y+=v.m_y;
    }

    Vector2D operator -(Vector2D const &v){
        return Vector2D(m_x-v.m_x,m_y-v.m_y);
    }

    void operator -=(Vector2D const &v){
        this->m_x-=v.m_x;
        this->m_y-=v.m_y;
    }

    Vector2D operator /(int n){
        return Vector2D(m_x/n,m_y/n);
    }

    void operator /=(int n){
        this->m_x/=n;
        this->m_y/=n;
    }


    Vector2D operator *(int n){
        return Vector2D(m_x*n,m_y*n);
    }

    bool gotoPos(Vector2D pos,float vel,int delay){
        if(delay>0){
            double margeErreurX=remainder(pos.getX()-m_x,vel);
            double margeErreurY=remainder(pos.getY()-m_y,vel);
            std::cout<<"marge X : "<<margeErreurX<<std::endl;
            double velX,velY;
            if(margeErreurX<vel){
                velX=margeErreurX;
            }else{
                velX=vel;
            }
            if(margeErreurY<vel){
                velY=margeErreurY;
            }else{
                velY=vel;
            }
            if(m_x!=pos.getX()||m_y!=pos.getY()){
                if(tanim.attendre(delay)){
                    if(m_x<pos.getX()){
                        this->m_x+=velX;
                    }else{
                        if(m_x>pos.getX()){
                            this->m_x-=velX;
                        }
                    }
                    if(m_y<pos.getY()){
                        this->m_y+=velY;
                    }else{
                        if(m_y>pos.getY()){
                            this->m_y-=velY;
                        }
                    }
                }
            }else{
                return true;
            }
        }else{
            this->setX(pos.getX());
            this->setY(pos.getY());
            return true;
        }
        return false;
    }

    void operator *=(int n){
        this->m_x*=n;
        this->m_y*=n;
    }

};
#endif // VECTOR2D_H_INCLUDED

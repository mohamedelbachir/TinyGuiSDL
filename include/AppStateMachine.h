#ifndef APPSTATEMACHINE_H_INCLUDED
#define APPSTATEMACHINE_H_INCLUDED
#include<vector>
#include"AppState.h"
class AppStateMachine{
private:
    std::vector<AppState*>m_states;
public:
    AppStateMachine(){

    }

    void pushState(AppState* state){
        m_states.push_back(state);
        m_states.back()->onEnter();
    }

    void popState(){
        if(!m_states.empty()){
            if(m_states.back()->onExit()){
                std::vector<AppState*>::iterator it;
                it=m_states.end();
                delete m_states.back();
                m_states.erase(it);
                m_states.pop_back();
            }
        }
    }

    void changeState(AppState *state){
        if(!m_states.empty()){
            if(m_states.back()->getStateID()==state->getStateID()){
                return;
            }
            if(m_states.back()->onExit()){
                std::vector<AppState*>::iterator it;
                it=m_states.end();
                delete m_states.back();
                m_states.erase(it);
                m_states.pop_back();
            }
            m_states.push_back(state);
            m_states.back()->onEnter();
        }
    }

    void update(){
       if(!m_states.empty()){
          m_states.back()->update();
       }
    }

    void render(){
        if(!m_states.empty()){
            m_states.back()->render();
        }
    }

    void clear(){
        for(size_t i=0;i<m_states.size();i++){
            if(m_states[i]->onExit()){
                std::cout<<"exit state finish ..."<<std::endl;
                delete m_states[i];
            }
        }
        m_states.clear();
    }
};


#endif // APPSTATEMACHINE_H_INCLUDED

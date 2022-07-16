#ifndef GUI_SHAPE_H_INCLUDED
#define GUI_SHAPE_H_INCLUDED
class GUI_Shape:public Widget{
protected:

public:

    GUI_Shape(){
        this->ID=W_SHAPE;
    }

    GUI_Shape(int x,int y,int w,int h){
        this->ID=W_SHAPE;
        gRect.x=x;
        gRect.y=y;
        gRect.w=w;
        gRect.h=h;
        updateSizePosition();
        gTargetCursor.x+=1;
        gTargetCursor.y+=1;
        gTargetCursor.w-=2;
        gTargetCursor.h-=2;
    }

    ~GUI_Shape(){

    }

    void resizeShape(int w=-1,int h=-1)override{
        if(h>=0){
            gRect.h=h;
        }
        if(w>=0){
            gRect.w=w;
        }
    }
    void show(SDL_Renderer *rendu,SDL_Event &e,SDL_Texture *dtest=NULL)override{
        if(getDisplay()){
            if(IsCheckMouseEvent()){
                Widget::CheckEventMouse(e);
            }
            DrawRenderColor(rendu,gFillColor);
            SDL_RenderFillRect(rendu,&gRect);

            ///mis a jour de la texture
            Update(rendu,e);

            DrawRenderColor(rendu,gBorderColor);
            SDL_RenderDrawRect(rendu,&gRect);

            //affichage de couleur de deboggage
            if(ColorShape){

                //cas des couleur de Bordure
                DrawRenderColor(rendu,gColorShape);
                SDL_RenderDrawRect(rendu,&gRect);

                //cas de couleur de gestion Event
                DrawRenderColor(rendu,gColorEvent);
                SDL_RenderDrawRect(rendu,&gTargetCursor);

            }
        }

    }
};


#endif // GUI_SHAPE_H_INCLUDED

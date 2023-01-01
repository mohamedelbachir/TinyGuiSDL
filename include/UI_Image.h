#ifndef GAMEUI_IMAGE_H_INCLUDED
#define GAMEUI_IMAGE_H_INCLUDED
#include"Texture.h"

class UI_Image:public Texture{

public:
    static int instance;

    /*Uploading the image and display entrelly image*/
    UI_Image(std::string idImage,int x,int y);

    /*Uploading an image that can be visible in one part according to the source of visible element*/
    UI_Image(std::string idImage,int x,int y,int srcw,int srch);

    /*Uploading an image for particular frame or Tileset*/
    UI_Image(std::string idImage,int x,int y,int srcx,int srcy, int srcw,int srch);

    ~UI_Image();

    void update()override;

    void draw(SDL_Renderer *pRenderer)override;

    void setSourceDisplay(SDL_Rect src);

    void clean() override;

};


#endif // GAMEUI_IMAGE_H_INCLUDED

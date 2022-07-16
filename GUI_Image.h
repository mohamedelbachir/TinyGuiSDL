#ifndef GUI_IMAGE_H_INCLUDED
#define GUI_IMAGE_H_INCLUDED
#include"GUI_Texture.h"
class GUI_Image:public GUI_Texture{
protected:

public :

    /**
        @brief GUI_Image
        constructeur par defaut d'image

    */
    GUI_Image(){
        this->ID=W_IMAGE;
        gTexture=NULL;
    }

    /**
        @brief :   GUI_Image
            Constructeur d'image no1
        @param : - rendu :Rendu d'affichage
        @param :   path: Chemin d'acces du fichier
        @param : - (x,y) : Position de l'image
    */
    GUI_Image(SDL_Renderer *rendu,std::string path,int x,int y){

        this->ID=W_IMAGE;

        /*Chargement de l'image*/
        gTexture=SDL_CreateTextureFromSurface(rendu,IMG_Load(path.c_str()));

        /*Verification de l'image*/
        if(gTexture==nullptr){
            char text[255];
            sprintf(text,"%s :  %s",path.c_str(),IMG_GetError());
            std::cout<<text<<std::endl;
            delete []text;
            exit(EXIT_FAILURE);
        }

        /*positon de l'image et mis a jour de taille*/
            gRect.x=x;
            gRect.y=y;
            gRenderCpy=rendu;
            UpdateSizeTexture();
    }

    /**
        @brief :   GUI_Image
        Constructeur d'image no2
        @param : - rendu :Rendu d'affichage
        @param : - texture : texture image
        @param : - (x,y) : Position de l'image
    */
    GUI_Image(SDL_Renderer *rendu,SDL_Texture *texture,int x,int y){

        /*Chargement de l'image TEXTURE*/
        gTexture=texture;

        /*Verification de l'image*/

        if(gTexture==NULL){
            char text[255];
            sprintf(text,"ImPosible De Charger <L'image Par Texture>:  %s",IMG_GetError());
            std::cout<<text<<std::endl;
            delete []text;
            exit(EXIT_FAILURE);
        }

        /*positon de l'image*/
        gRect.x=x;
        gRect.y=y;
        gRenderCpy=rendu;
        UpdateSizeTexture();
    }

    /**
        @brief :   GUI_Image
        Destructeur d'image
    */
    ~GUI_Image(){
        //liberation de la memoire
    }


};


#endif // GUI_IMAGE_H_INCLUDED

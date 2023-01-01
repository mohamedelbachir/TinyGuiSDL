#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED
#include<map>
#include<SDL.h>
#include<SDL_image.h>

/*singleton class of texture Manager*/

class TextureManager{
private:

    //list of saving texture
    std::map<std::string,SDL_Texture *>m_textureMap;

    TextureManager();

    ~TextureManager();

    static TextureManager *s_pInstance;

public:

    static TextureManager* Instance(){
        if(s_pInstance==NULL){
            s_pInstance=new TextureManager();
        }
        return s_pInstance;
    }
    /**
        @brief cleanUp
        function to clean Saving texture on the map
    */
    void cleanUp();

    /**
        @brief load
        function that allow to load the picture in our scene
        @param filepath :
        @param id :
        @param pRenderer :
    */
    bool load(std::string filepath,std::string id,SDL_Renderer *pRenderer);

    /**
        @brief  draw
        @param id:
        @param x,y:
        @param width,height:
        @param flip:
    */
    void draw(std::string id,float x,float y,int width,int height,SDL_Rect src,double angle,SDL_Renderer *pRenderer,SDL_RendererFlip flip=SDL_FLIP_NONE);

    /**
        @brief  clearFromTextureMap
        function to delete specific texture on the map
        @param id: identifier of texture

    */
    void clearFromTextureMap(std::string id);

    /**
        @brief  getTextureMap
        function to get Texture associate to id
        @param Texture

    */
    SDL_Texture *getTextureMap(std::string id);

    /**
        @brief getTextureIDMap
        function to find the ID of Texture
    */
    std::string getTextureIDMap(SDL_Texture *pTexture);

    void setTexture(std::string id,SDL_Texture *newTexture);

   };
typedef TextureManager theTextureManager;

#endif // TEXTUREMANAGER_H_INCLUDED

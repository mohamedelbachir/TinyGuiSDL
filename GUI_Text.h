#ifndef GUI_TEXT_H_INCLUDED
#define GUI_TEXT_H_INCLUDED
#include "GUI_Image.h"
#include<vector>
class GUI_Texte:public GUI_Image
{
private:
    TTF_Font *ft;

    int sizeft;

    std::string texte;

    SDL_Color texteModColor={255,255,255,255};

    SDL_Color texteColor={0,0,0,255};

public:

    ///constructeur de Texte par defaut
    GUI_Texte(){
        this->ID=W_TEXTE;
        texte="Texte";
        ft=TTF_OpenFont("font.ttf",10);
        gRect.x=0;
        gRect.y=0;
    }

    /**
    @brief          Constructeur : Texte
    @param        : - texte : titre du Texte
                    - (x,y) : Position du Texte
                    - rendu : Renderer De affichage
                    - size  : taille du police ou Grosseur de Police
                    - style : Pour Permettre de mettre en italique|bold|Barre un texte ou nom
   */
    GUI_Texte(SDL_Renderer *rendu,std::string pathfont,int x,int y,std::string texte,int size,int style=TTF_STYLE_NORMAL,bool colorChange=false){

        this->ID=W_TEXTE;

        gRect.x=x;

        gRect.y=y;

        this->texte=texte;

        sizeft=size;

        if(!TTF_WasInit()){
            TTF_Init();
        }

        ft=TTF_OpenFont(pathfont.c_str(),size);

        if(ft==NULL){
            std::cout<<"Imposible de charger le font ........."<<std::endl;
            std::cout<<"erreur : "<<TTF_GetError();
            exit(EXIT_FAILURE);
        }
        TTF_SetFontStyle(ft,style);

        Uint32 wrap=wrapLength(texte)*TTF_FontHeight(ft);
        if(wrap!=0){
            gTexture=SDL_CreateTextureFromSurface(rendu,TTF_RenderText_Blended_Wrapped(ft,texte.c_str(),texteModColor,wrap));
        }else{
            gTexture=SDL_CreateTextureFromSurface(rendu,TTF_RenderText_Blended(ft,texte.c_str(),texteModColor));
        }

        setFillColorState(-1,texteColor);
        if(gTexture==nullptr){
            std::cout<<"\nError : "<<SDL_GetError();
            std::cout<<"\nTTF Error"<<TTF_GetError();
            exit(0);
        }
        gRenderCpy=rendu;

        UpdateSizeTexture();
    }

    /**
        @brief  Constructeur : Texte
        @param  - texte : titre du Texte
                - (x,y) : Position du Texte
                - font  : font a definir
   */
    GUI_Texte(SDL_Renderer *rendu,TTF_Font *font,int x,int y,std::string texte){

        this->ID=W_TEXTE;

        gRect.x=x;

        gRect.y=y;

        this->texte=texte;


        if(!TTF_WasInit()){
            TTF_Init();
        }

        ft=font;

        gTexture=SDL_CreateTextureFromSurface(rendu,TTF_RenderText_Blended(ft,texte.c_str(),texteModColor));

        setFillColorState(-1,texteColor);

        gRenderCpy=rendu;

        UpdateSizeTexture();
    }
   /**
        @brief  Constructeur : Texte
        @param  - texte : titre du Texte
                - (x,y) : Position du Texte
    */
    GUI_Texte(SDL_Renderer *rendu,SDL_Texture *text,int x,int y):GUI_Image(rendu,text,x,y){
        this->ID=W_TEXTE;
        this->texte="";
    }

    /**
        @brief ~GUI_Texte
        Destructeur de Texte
    */
    ~GUI_Texte(){

        TTF_CloseFont(ft);
        std::cout<<"Suppression GUI_Text!!!"<<std::endl;
    }

    /***/
    std::string getTexte(){
        return texte;
    }

    TTF_Font* getFont(){
        return this->ft;
    }

    Uint32 wrapLength(std::string str){
        std::vector<int> charLen;
        int k=0;
        for(int i=0;i<str.length();i++){
            if(str[i]!='\n'){
                k++;
            }else{
                charLen.push_back(k);
                k=0;
            }
        }
        int great=0;
        for(int i=0;i<charLen.size();i++){
            if(great<charLen[i]){
                great=charLen[i];
            }
        }
        charLen.clear();
        return great;
    }
};
#endif // GUI_TEXT_H_INCLUDED

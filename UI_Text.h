#ifndef GAMEUI_TEXT_H_INCLUDED
#define GAMEUI_TEXT_H_INCLUDED
#include"Texture.h"
#include<vector>
class UI_Text:public Texture
{
private:
    std::string fontID;
    std::string texte=" ";

    static int instance;

    int m_size=0;

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

public:


    UI_Text(SDL_Renderer *rendu,std::string texte,int x,int y,std::string fontId);

    ~UI_Text();

    void update()override;

    void draw(SDL_Renderer *pRenderer)override;

    void clean();

    void changeTexte(std::string texte);

    void changeTexte(int val);

    void setFontText(std::string fontPath);

    void changeTexteColor(int r,int g,int b,int a);
};

#endif // GAMEUI_TEXT_H_INCLUDED

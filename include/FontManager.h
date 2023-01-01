#ifndef FONTMANAGER_H_INCLUDED
#define FONTMANAGER_H_INCLUDED
/*singleton class of Font manager*/
#include<map>
#include<SDL_ttf.h>
class fontManager
{
private:

    //list of saving Font
    std::map<std::string,TTF_Font*>m_fontMap;

    fontManager();

    ~fontManager();

    static fontManager *s_pInstance;

public:

    static fontManager* Instance()
    {
        if(s_pInstance==NULL)
        {
            s_pInstance=new fontManager();
        }
        return s_pInstance;
    }
    /**
        @brief cleanUp
        function to clean Saving Font on the map
    */
    void cleanUp();

    /**
        @brief load
        function that allow to load font with size
        @param filepath : path to the resources
        @param id :identifier
    */
    bool load(std::string filepath,int t_size,std::string id)throw(std::string);

    /**
        @brief clearFromFontMap
        function that clean specific allocated font
        @param id :identifier
    */
    void clearFromFontMap(std::string id);

    /**
        @brief getFontMap
        function to get TTF_Font associate to id
        @param id :identifier
        @return TTF_Font*
    */
    TTF_Font *getFontMap(std::string id);

};
typedef fontManager thefontManager;
#endif // FONTMANAGER_H_INCLUDED

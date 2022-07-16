#ifndef WIDGET_H_INCLUDED
#define WIDGET_H_INCLUDED
#include<stdio.h>

#define ERROR INT_MAX

#define VELOCITY 5
#define SIZECHECKBOX 20
#define numberState 3

#include<sstream>
#include<fstream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include"Timer.h"
///enumerationIDWidgets
enum {W_IMAGE,W_TEXTE,W_SVG,W_SHAPE,W_BUTTON,W_RADIO,W_TEXTE_INPUT,W_INPUT_NUMBER,W_PANEL,W_BORDER_TEXTURE,W_SELECT_BOX};
enum {ERROR_IMG,ERROR_TTF,ERROR_SDL};

class Widget
{

protected:

    ///Variable Boolean definisant si oui/non la position reel est trouve
    bool isRealpositionSet=false;

    ///Variable permettant d'obtenir les coordonne de la souris
    SDL_Point mouseRect={0};


    ///Temps de Clicks de press de la souris
    Timer tclick;

    ///Temps de DoubleClicks pour la souris
    Timer tdbleclik;

    ///Capture d'evenement de la souris
    SDL_Event evt;

    ///vitesse de Deplacement
    int velocityTomove=2;

    ///Position Globale du Widgets
    SDL_Rect gRect= {0};

    ///Variable globale pour positioner le Widget selon une Direction
    SDL_Rect gRealRectIngRect= {0,0,0,0};

    ///Coordonne du Target dans un Texture Target
    SDL_Point gCoordTarget= {0,0};

    ///Variable de champs pour obtenir les infos sur le etat du Widget
    SDL_Rect gTargetCursor= {0};

    ///Coordonne ancien du position Globale
    SDL_Point gOldRect= {0};

    ///Identifiant d'un Widgets
    int ID;

    ///Temps de determination du dbleClick
    int t=-1;

    //==== Couleur de Remplissage Intermediare pour les Etats      ===
    SDL_Color gFillColor = {255,255,255,255};

    SDL_Color gBorderColor = {255,0,255,255};

    //==== Couleur de Rempplissage/Bordure pour le cas par defaut  ===

    SDL_Color gDefaultBorderColor= {255,255,255,255};

    SDL_Color gDefaultFillColor = {255,0,255,255};

    //===== Couleur de Remplissage/Bordure pour le cas du Hover    ===

    SDL_Color gHoverFillColor = {255,255,255,255};

    SDL_Color gHoverBorderColor = {255,255,255,255};

    //===== Couleur de Remplissage/Bordure lors des Clicks ===

    SDL_Color gClicksFillColor = {255,255,255,255};

    SDL_Color gClicksBorderColor = {255,255,255,255};

    //======= Couleur de deboggage =======
    bool ColorShape=false;                //Variable de Debugage des rect par defaut
    SDL_Color gColorShape= {0,0,255,255}; //Couleur de grect
    SDL_Color gColorEvent= {255,0,0,255}; //Couleur du TargetCursor

    bool display=true;

    bool checkMouseEvent=true;

    //====== Variable de Copy du Rendu =======
    SDL_Renderer *gRenderCpy;

    SDL_Renderer *pRenderCpy;

    //====== Direction Affichage =========
    int directionRender=Widget::LEFT;

    //======== Etat du Button =========
    int state=Widget::BTN_STAT_NONE;

    //========= Changement ==========
    bool stateSet=false;

    //======== Temps de Clicks ========
    int timeClick=300;

    bool mouseInWindow=false;

    bool ischeck=false;

    bool checkVisibility=false;
private:

    /**
        @brief setBorderColor
        fonction Changent la couleur de Bordure
        @param -col couleur de Bordure
    */
    void setBorderColor(SDL_Color col){
        gBorderColor=col;
    }

    /**
        @brief setFillColor
        fonction Changent la couleur de Remplisage
        @param -col couleur de Remplissage
    */
    void setFillColor(SDL_Color col){
        gFillColor=col;
    }

    /**
        @brief HandingError
        fonction capture d'erreure
        @param -id : error ID
    */
    /*void HandingError(int idError){
        switch(idError){
            case ERROR_IMG:
                fprintf(fileLog,"\nimage Error :%s ",IMG_GetError());
            break;

            case ERROR_TTF:
                fprintf(fileLog,"\TTF Error :%s ",TTF_GetError());
            break;

            case ERROR_SDL:
                fprintf(fileLog,"\SDL Error :%s ",SDL_GetError());
            break;
        }
    }*/

public:

    /**Direction du Texte*/
    enum {LEFT,RIGHT,UP,DOWN,CENTER};

    /**Etat button*/
    enum {BTN_STAT_NONE,BTN_STAT_HOVER,BTN_STAT_CLICKS,BTN_STAT_DESACTIVATE};

    /**
        @brief setBorderColorState
        fonction permettant de Changer la Couleur de Bordure selon etat
        @param -state {BTN_SAT_NONE,BTN_STAT_HOVER,....}
        @param -col couleur de l'etat (-1 pour mettre tous les etats la meme Couleur )
    */
    virtual void setBorderColorState(int state,SDL_Color col)
    {
        switch(state)
        {
        case Widget::BTN_STAT_NONE:
            gDefaultBorderColor=col;
            break;
        case Widget::BTN_STAT_HOVER:
            gHoverBorderColor=col;
            break;
        case Widget::BTN_STAT_CLICKS:
            gClicksBorderColor=col;
            break;
        case -1:
            gDefaultBorderColor=col;
            gHoverBorderColor=col;
            gClicksBorderColor=col;
            break;
        }
    }

    /**
        @brief getID
        fonction permettant obtenir l'ID du Widget
        @return ID
    */
    int getID(){
        return ID;
    }

    /**
        @brief SetDisplay
          Fonction Permettant d'afficher/cacher une Texture
        @param enable: booleen d'affichage
    */
    void SetDisplay(bool enable){
        display=enable;
    }

    /**
        @brief SetCheckMouseEvent
        Fonction Permettant de capture alluner la capture d'evenement
        @param enable: booleen de capture d'event
    */
    void SetCheckMouseEvent(bool enable){
        checkMouseEvent=enable;
    }

    /**
        @brief IsCheckMouseEvent
          Fonction Permettant de connaitre si le capture d'event est auttorze
        @return true,false pour different cas
    */
    bool IsCheckMouseEvent(){
        if(!checkMouseEvent){
            state=Widget::BTN_STAT_NONE;
        }
        return checkMouseEvent;
    }

    /**
        @brief getDisplay
          Fonction Permettant de connaitre si afficher/cacher
        @return vrai ou faux
    */
    bool getDisplay(){
        return display;
    }

    /**
    */
    SDL_Rect *getRefRect(){
        return &gRect;
    }

    SDL_Point getRealRect(){
        SDL_Point p;
        p.x=gCoordTarget.x+gRect.x;
        p.y=gCoordTarget.y+gRect.y;
        return p;
    }
    /**
        @brief setFillColorState
        fonction permettant de Changer la Couleur de Remplissage selon etat
        @param -state {BTN_SAT_NONE,BTN_STAT_HOVER,....}
        @param -col couleur de l'etat (-1 pour mettre tous les etats la meme Couleur )
    */
    virtual void setFillColorState(int state,SDL_Color col)
    {
        switch(state)
        {
        case Widget::BTN_STAT_NONE:
            gDefaultFillColor=col;
            break;
        case Widget::BTN_STAT_HOVER:
            gHoverFillColor=col;
            break;
        case Widget::BTN_STAT_CLICKS:
            gClicksFillColor=col;
            break;
        case -1:
            gDefaultFillColor=col;
            gHoverFillColor=col;
            gClicksFillColor=col;
            break;
        }
    }

    /**
        @brief UpdateDirectionInRender
        fonction permettant de Changer la position d'un Wigets
        selon une direction {LEFT,UP,...}

    */
    void UpdateDirectionInRender()
    {
        switch(this->directionRender)
        {
            case LEFT:
                gRect.x=gOldRect.x+gRealRectIngRect.x+10;
                gRect.y=gOldRect.y+gRealRectIngRect.h/2-gRect.h/2;
                break;
            case CENTER:
                gRect.x=gOldRect.x+gRealRectIngRect.w/2-gRect.w/2;
                gRect.y=gOldRect.y+gRealRectIngRect.h/2-gRect.h/2;
                break;
            case RIGHT:
                gRect.x=gOldRect.x+gRealRectIngRect.w-gRect.w-10;
                break;
        }
    }

    /**
        @brief getRect
            fonction permettant d'obtenir la position globale Du Widget (gRect)
        @return gRect
    */
    SDL_Rect getRect()
    {
        return gRect;
    }

    /**
        @brief setTargetPosition
            fonction permettant de changer la position Du Widget dans une TargetTexture
        @param (x,y) : position du TargetTexture

    */
    virtual void setTargetPosition(int x,int y)
    {
        gCoordTarget.x=x;
        gCoordTarget.y=y;
    }

    SDL_Point getGlobalTargetPosition()const{
        return gCoordTarget;
    }
    virtual void resizeShape(int w=-1,int h=-1){
        if(h>=0){
            gRect.w=w;
        }
        if(w>=0){
            gRect.h=h;
        }
        updateSizePosition();
    }

    /**
        @brief getBorderColor
           fonction renvoyant la couleur de Bordure
        @return : la couleur

    */
    SDL_Color getBorderColor(int state){
        switch(state){
        case BTN_STAT_NONE:
            return gDefaultBorderColor;
        case BTN_STAT_HOVER:
            return gHoverBorderColor;
        case BTN_STAT_CLICKS:
            return gClicksBorderColor;
        }
    }
    /**
        @brief setState
        definir un etat du widget
    */
    void setState(int state){
         this->state=state;
    }
    /**
        @brief getfillColor
           fonction renvoyant la couleur de Bordure
        @return : la couleur

    */
    SDL_Color getFillColor(int state){
        switch(state){
        case BTN_STAT_NONE:
            return gDefaultFillColor;
        case BTN_STAT_HOVER:
            return gHoverFillColor;
        case BTN_STAT_CLICKS:
            return gClicksFillColor;
        }
    }

     /**
        @brief OnMouseHover
           fonction permettant de Capture le cas de Survole de la souris sur la gRect
        @return : vrai si Survaule et faux sinon

    */
    bool OnMouseHover(SDL_Event &e)
    {
        //SDL_Event e;
        /*switch(e.type){
            case SDL_WINDOWEVENT:
                if(e.window.event==SDL_WINDOWEVENT_LEAVE){
                    mouseInWindow=false;
                }else{
                    mouseInWindow=true;
                }
            break;
        }*/
        SDL_GetMouseState(&mouseRect.x,&mouseRect.y);

        SDL_Rect tmp;

        gTargetCursor.x=gRect.x+gCoordTarget.x+1;

        gTargetCursor.y=gRect.y+gCoordTarget.y+1;

        gTargetCursor.w=gRect.w-2;

        gTargetCursor.h=gRect.h-2;

        if(SDL_PointInRect(&mouseRect,&gTargetCursor)/*&&mouseInWindow*/)
        {
            return true;

        }
        else
        {

            return false;
        }
    }

    /**
        @brief OnMouseClicks
           fonction permettant de Capture le cas de CLICKS de la souris sur la gRect
        @param e:Variable d'evenement
        @return vrai si oui et faux sinon

    */
    bool OnMouseClicks(SDL_Event &e)
    {
        this->evt=e;
        if(OnMouseHover(e))
        {
            if(e.type==SDL_MOUSEBUTTONDOWN&&e.button.button==SDL_BUTTON_LEFT&&tclick.attendre(timeClick))
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }


    void setCheckIt(bool enable){
        ischeck=enable;
    }

    void setCheckVisibiliy(bool enable){
        checkVisibility=enable;
    }

    bool getCheckVisibiliy(){
        return checkVisibility;
    }

    bool isCheckIt(){
        return ischeck;
    }

    /**
        @brief setTimeToClicks
        fonction Changeant le temps de Clicks du Clicks Event du Widgets
        @param ms: le Temps en (ms)
    **/
    void setTimeToClicks(Uint32 ms){
        timeClick=ms;
    }

    /**
        @brief OnGlobalMouseClicks
        fonction permettant de Capture un Clicks de la souris dans une zone autre que le widgets
        @param -e:Evenement

    */
    bool OnGlobalMouseClicks(SDL_Event &e)
    {
        if(e.type==SDL_MOUSEBUTTONDOWN&&e.button.button==SDL_BUTTON_LEFT)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
        @brief getCurrentState
        fonction permettant de recuperer l'etat du Button
        @return -state:{BTN_STAT_HOVER,BTN_STAT_NONE,...}

    */
    int getCurrentState()
    {
        return state;
    }

    /**
        @brief updateSizePosition
        fonction permettant la mise a jour du rect/targetCursor
    */
    void updateSizePosition()
    {
        gOldRect.x=gRect.x;
        gOldRect.y=gRect.y;
        gTargetCursor=gRect;
    }

    /**
        @brief CheckEventMouse
        fonction permettant de capturer les differant etat de la souris sur le Widget
    */
    void CheckEventMouse(SDL_Event &e)
    {
        if(OnMouseClicks(e))
        {
            setBorderColor(gClicksBorderColor);
            setFillColor(gClicksFillColor);
            this->state=Widget::BTN_STAT_CLICKS;
        }
        else
        {
            if(OnMouseHover(e))
            {
                setBorderColor(gHoverBorderColor);
                setFillColor(gHoverFillColor);
                this->state=Widget::BTN_STAT_HOVER;
            }
            else
            {
                setBorderColor(gDefaultBorderColor);
                setFillColor(gDefaultFillColor);
                this->state=Widget::BTN_STAT_NONE;
            }
        }
    }

    /**
        @brief OndbleClick
           fonction permettant de Capture le cas de DOUBLECLIKS de la souris sur la gRect
        @param e:Variable d'evenement
        @return vrai si oui et faux sinon

    */
    bool OndbleClick(SDL_Event &e)
    {


    }
    /***/
    SDL_Rect getGlobalTargetPositionToRect(){
        return gTargetCursor;
    }

    /**
        @brief setPosition
           fonction permettant de changer la position globale du Widget(gRect)
        @param (x,y):position de destination de destination

    */
    virtual void setPosition(int x,int y,int time=0,int vel=2)
    {
        if(time>0){
            animPosition(&gRect.x,&gRect.y,x,y,time,vel);
        }else{
            gRect.x=x;
            gRect.y=y;
        }
        updateSizePosition();
    }
    bool animPosition(int* xsource, int* ysource, int xdest, int ydest, int time, int velocity){
        int margeErreurX=(xdest-*xsource)%velocity;
        int margeErreurY=(ydest-*ysource)%velocity;
        int velocityX,velocityY;
        Timer tanim;
        if(margeErreurX!=0){
            velocityX=1;
        }else{
            velocityX=velocity;
        }
        if(margeErreurY!=0){
            velocityY=1;
        }else{
            velocityY=velocity;
        }
        if(*xsource!=xdest||*ysource!=ydest){
            if(tanim.attendre(time)){
                if(*xsource<xdest){
                    *xsource+=velocityX;
                }else{
                    if(*xsource>xdest){
                        *xsource-=velocityX;
                    }
                }
                if(*ysource<ydest){
                    *ysource+=velocityY;
                }else{
                    if(*ysource>ydest){
                        *ysource-=velocityY;
                    }
                }
            }
        }else{
            return true;
        }
        return false;
    }
    /**
        @brief setWithHeightRender
           fonction permettant de positioner le Widget dans une zone
        @param (w,h):Taille de la zone
        @param directionToRender : Direction d'affichage du Widgets Par defaut {LEFT}

    */
    virtual void setWithHeightRender(int w=0,int h=0,int directionToRender=Widget::LEFT)
    {

        gRealRectIngRect.w=w;

        gRealRectIngRect.h=h;

        directionRender=directionToRender;

        UpdateDirectionInRender();
    }

    /**
       @brief DrawRenderColor
          fonction permettant de desinner une Couleur selon le Renderer
       @param rendu: Rendu du Dessin
       @param col:Couleur de Dessin

    */
    void DrawRenderColor(SDL_Renderer *rendu,SDL_Color col)
    {
        SDL_SetRenderDrawColor(rendu,col.r,col.g,col.b,col.a);
    }

    /**
        @brief getRenderCopy
        fonction permettant d'obtenir une copie du renderer
        @return -rendu : rendu Copier
    */
    SDL_Renderer *getRenderCopy(){
        return gRenderCpy;
    }

    void setParentRender(SDL_Renderer *pRendu){
        pRenderCpy=pRendu;
    }

    SDL_Renderer *getParentRender(){
        return pRenderCpy;
    }

    /**
        @brief HandleInput
           fonction permettant de Recuper les Entrer du Clavier
        @param e:l'event a capturer

    */
    virtual void HandleInput(SDL_Event &e) { };

    /**
        @brief Update
           fonction permettant de la mis a jour du Widgets
        @param e:l'event a capturer
    */
    virtual void Update(SDL_Renderer *rendu,SDL_Event &e) {};

    /**
        @brief ~Widget
           Destructeur du Widget

    */
    virtual ~Widget() { };

    /**
        @brief show
           Fonction d'affichage du Widget sur le rendu
        @param rendu : le Rendu d'affichage
        @param e : les Evenements du Window

    */
    virtual void show(SDL_Renderer *rendu,SDL_Event &e,SDL_Texture *dtest=NULL)=0;

    /**
        @brief convert_int_to_string
           fonction permettant de convertir un entier en string
        @param n:l'entier
        @return - string
    */
    std::string convert_int_to_string(int n)
    {
        std::string tmp="";
        char tc[255];
        sprintf(tc,"%d",n);
        tmp+=tc;
        delete []tc;
        return tmp;
    }

    /**
        @brief convert_int_to_string
           fonction permettant de convertir un string en entier
        @param c:le string
        @return - entier (ERROR en cas de mauvaise Chaine)
    */
    int convert_string_to_int(std::string c,bool *isError)
    {

        int x=0;
        std::string str="";

        std::stringstream conv(c);
        conv>>x;

        char lt[c.length()];
        sprintf(lt,"%d",x);

        str+=lt;//on obtient le nombre

        if(c.compare(str)!=0)
        {
            //cas de mauvaise entrer
            x=0;
            *isError=true;

        }else{

            *isError=false;
        }
        return x;

    }

    /**
        @brief NbreToHex
           fonction permettant de convertir un Nombre en Hexadecimale
        @param n:le nombre(entier)
        @return - al valeur en Hexadecimale
    */
    std::string NbreToHex(int n)
    {
        std::string colHex="";
        int r=0;
        char tmp[255];
        do
        {
            r=n%16;
            if(r>=10&&r<16)
            {
                switch(r)
                {
                case 10:
                    colHex+="A";
                    break;
                case 11:
                    colHex+="B";
                    break;
                case 12:
                    colHex+="C";
                    break;
                case 13:
                    colHex+="D";
                    break;
                case 14:
                    colHex+="E";
                    break;
                case 15:
                    colHex+="F";
                    break;
                }
            }
            else
            {
                sprintf(tmp,"%d",r);
                colHex+=tmp;
            }
            n/=16;
        }
        while(n>0);
        if(colHex.length()<2)
        {
            colHex+=colHex;
        }
        delete []tmp;
        return colHex;
    }

    /**
        @brief reverseString
           fonction permettant de renverser une chaine de caractere
        @param s:la chaine
        @return - la chaine renverser
    */
    std::string reverseString(std::string s)
    {
        std::string t="";
        for(int i=s.length()-1; i>=0; i--)
        {
            t.push_back(s[i]);
        }
        return t;
    }

    /**
        @brief convert_color_to_Hex
           fonction permettant de convertir une couleur en Hexadecimale
        @param col:la couleur d'entrer
        @return - la couleur en Hexadecimale
    */
    std::string convert_color_to_Hex(SDL_Color col)
    {
        std::string colHexOuput="";
        colHexOuput+=NbreToHex(col.b);
        colHexOuput+=NbreToHex(col.g);
        colHexOuput+=NbreToHex(col.r);
        colHexOuput=reverseString(colHexOuput);
        colHexOuput.insert(0,"#");
        return colHexOuput;
    }
};

#endif // WIDGET_H_INCLUDED

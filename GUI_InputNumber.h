#ifndef GUI_INPUTNUMBER_H_INCLUDED
#define GUI_INPUTNUMBER_H_INCLUDED
#define WIDTHINPUT 100
#define HEIGHTINPUT 42
class GUI_InputNumber:public GUI_TextInput
{
private:

    ///button de haut
    GUI_button *btn_up;

    ///button bas
    GUI_button *btn_down;

    ///valeur min
    int minValue=0;

    ///valeur max
    int maxValue=INT_MAX;


    bool isStringError=false;

    ///valeur du textinput
    int value=0;

    SDL_Color white={255,255,255,255};

    GUI_svg *arrow;

public:

    /** @brief : GUI_InputNumber
      *
      * Constructeur du Input Number
      * @param : (x,y)=> Position du Input Number
      * @param : direction=> Position du Texte dans le InputTexte
      * @param : style style du inputNumer
      * @param : w,h:par defaut Null (Taille du InPut Button
      * @param : defaultValue : Valeur par defaut saisi par defaut (9)
      */
    GUI_InputNumber(SDL_Renderer *rendu,std::string pathfont,int taille,int x,int y,int direction=Widget::LEFT,int style=TTF_STYLE_NORMAL,int w=200,int h=40):GUI_TextInput(rendu,pathfont,taille,x,y,direction,style,w,h)
    {
        this->ID=W_INPUT_NUMBER;

        arrow=new GUI_svg(rendu,0,0);

        arrow->DrawTriangle(10,10,1,"#fff",true,"#fff");

        btn_up=new GUI_button(rendu,"u",pathfont,10,w-30,0,CENTER,TTF_STYLE_NORMAL,30,h/2);
        btn_up->getTextButton()->setTexture(arrow->getTexture());
        btn_up->getTextButton()->setPosition(btn_up->getRect().x,btn_up->getRect().y);
        btn_up->getTextButton()->setWithHeightRender(btn_up->getRect().w,btn_up->getRect().h,Widget::CENTER);

        btn_up->setTargetPosition(gRect.x,gRect.y);

        btn_down=new GUI_button(rendu,"d",pathfont,10,w-30,btn_up->getRect().y+btn_up->getRect().h,CENTER,TTF_STYLE_NORMAL,30,h/2);
        btn_down->getTextButton()->setTexture(arrow->getTexture());
        btn_down->getTextButton()->setPosition(btn_down->getRect().x,btn_down->getRect().y);
        btn_down->getTextButton()->rotateFlip(180);
        btn_down->getTextButton()->setWithHeightRender(btn_down->getRect().w,btn_down->getRect().h,Widget::CENTER);

        btn_down->setTargetPosition(gRect.x,gRect.y);

        SetPaddingX(btn_up->getRect().w);

        setFillColorState(-1,white);
    }

    /**
        @brief :InputNumber
        Destructeur de Input Number en Liberant de l'espace
    */
    ~GUI_InputNumber()
    {
        delete arrow;
        delete btn_up;
        delete btn_down;
    }

    void setFillColorState(int state, SDL_Color col)override{
        btn_up->setFillColorState(state,col);
        btn_down->setFillColorState(state,col);
    }

    void setBorderColorState(int state, SDL_Color col)override{
        arrow->setColor(col);
        Widget::setBorderColorState(-1,col);
        btn_up->setBorderColorState(state,col);
        btn_down->setBorderColorState(state,col);
    }
    /**
        @brief checkInputNumber
      * Verification de la validiter des entier saisi
      * @param : value: la valeur du input
      * @return :booleen de retour de validiter
    */
    bool checkInputNumber(int &value){

        value=convert_string_to_int(GetTextInput(),&isStringError);
        bool verif=true;
        if(value==0&&isStringError){
            verif=false;
        }
        return verif;
    }

    /**
        @brief VerifyTypeText
      * Verification de la validiter des texte
      * @param : event l'evenement
    */
    void VerifyTypeText(SDL_Event &event)
    {
        if(!CheckWrite(event))
        {

            if(!checkInputNumber(this->value))
            {
                PutTextWithClear(convert_int_to_string(minValue));

            }else{
                if(this->value<minValue)
                {
                    PutTextWithClear(convert_int_to_string(minValue));
                }
                if(this->value>maxValue)
                {
                    PutTextWithClear(convert_int_to_string(maxValue));
                }
            }
        }
    }

    void Update(SDL_Renderer *rendu,SDL_Event &e)override
    {

        GUI_TextInput::HandleInput(e);

        VerifyTypeText(e);

        GUI_TextInput::StartToShow(rendu,e);

        if(btn_up->getCurrentState()==Widget::BTN_STAT_CLICKS)
        {

            checkInputNumber(value);
            if(value<maxValue)
            {
                PutTextWithClear(convert_int_to_string(value+1));
            }
        }
        if(btn_down->getCurrentState()==Widget::BTN_STAT_CLICKS)
        {

            checkInputNumber(value);
            if(value>minValue)
            {
                PutTextWithClear(convert_int_to_string(value-1));
            }
        }
        //arrow->setPosition(btn_up->getRect().x,btn_up->getRect().y);
        btn_up->show(rendu,e);

        btn_down->show(rendu,e);
        GUI_TextInput::EndToShow(rendu);
    }

    /**
        @brief SetMinValue
      * definition de la valeur minimale
      * @param : val la valeur
    */
    void SetMinValue(unsigned int val)
    {
        minValue=val;
    }
    void setPosition(int x, int y, int time=0,int vel=2)override{
        Widget::setPosition(x,y,time,vel);
        btn_up->setTargetPosition(gRect.x,gRect.y);
        btn_down->setTargetPosition(gRect.x,gRect.y);

    }
    void setWithHeightRender(int w, int h, int directionToRender=Widget::LEFT)override{
        Widget::setWithHeightRender(w,h,directionToRender);
        btn_up->setTargetPosition(gRect.x,gRect.y);
        btn_down->setTargetPosition(gRect.x,gRect.y);
    }
    /**
        @brief SetMaxValue
      * definition de la valeur maximal
      * @param : val la valeur
    */
    void SetMaxValue(unsigned int val)
    {
        maxValue=val;
    }

    /**
        @brief GetValue
      * recuperation des donne saisi
      * @return : la valeur
    */
    int GetValue()
    {
        return value;
    }
    void resizeShape(int w=-1, int h=-1)override{
        GUI_TextInput::resizeShape(w,h);
        btn_up->setPosition(getRect().w-btn_up->getRect().w,0);
        btn_down->setPosition(getRect().w-btn_up->getRect().w,btn_up->getRect().y+btn_up->getRect().h);
        SetPaddingX(btn_up->getRect().w);

    }
    void setTargetPosition(int x,int y)override
    {
        Widget::setTargetPosition(x,y);
        btn_up->setTargetPosition(x+getRect().x,y+getRect().y);
        btn_down->setTargetPosition(x+getRect().x,y+getRect().y);
    }
};

#endif // GUI_INPUTNUMBER_H_INCLUDED
